use std::error::Error;
use std::io::{self, Write};
use std::fmt;

const TAB: u8 = b'\t';
const SPACE: u8 = b' ';
const CR: u8 = b'\r';
const LF: u8 = b'\n';

/// Parser states. Mirrors the four `#define`d states in the C version.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum State {
    /// No fields encountered yet for this row.
    RowNotBegun,
    /// We have seen fields on this row, but are not inside one right now.
    FieldNotBegun,
    /// We are inside a field.
    FieldBegun,
    /// Saw a quote inside a quoted field: the field may have ended, or the
    /// quote may be the first half of an escaped (doubled) quote.
    FieldMightHaveEnded,
}

/// Events emitted while parsing.
#[derive(Debug)]
pub enum Event<'a> {
    /// A completed field. The slice borrows the parser's internal buffer and
    /// is only valid for the duration of the callback.
    Field(&'a [u8]),
    /// The current record (row) is complete. Carries the terminating byte
    /// (`Some(b'\n')` / `Some(b'\r')`), or `None` when the record was flushed
    /// by [`Parser::finish`] rather than by a newline (the C code's `-1`).
    EndOfRecord(Option<u8>),
}

/// Error returned, in strict mode, when malformed quoting is encountered.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ParseError;

impl fmt::Display for ParseError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str("malformed CSV input")
    }
}
impl Error for ParseError {}

pub struct Parser {
    state: State,
    quoted: bool,
    /// Trailing spaces accumulated in an unquoted field, or spaces seen after a
    /// closing quote. Used to strip insignificant whitespace on submit.
    spaces: usize,
    /// The current field's bytes. `Vec` growth replaces the C realloc dance;
    /// its length plays the role of `entry_pos`.
    entry: Vec<u8>,
    delim: u8,
    quote: u8,
    strict: bool,
    strict_fini: bool,
}

impl Default for Parser {
    fn default() -> Self {
        Self::new()
    }
}

impl Parser {
    pub fn new() -> Self {
        Parser {
            state: State::RowNotBegun,
            quoted: false,
            spaces: 0,
            entry: Vec::new(),
            delim: b',',
            quote: b'"',
            strict: false,
            strict_fini: false,
        }
    }

    pub fn with_delimiter(mut self, delim: u8) -> Self {
        self.delim = delim;
        self
    }

    pub fn with_quote(mut self, quote: u8) -> Self {
        self.quote = quote;
        self
    }

    /// In strict mode, malformed quoting *during parsing* (a bare quote in an
    /// unquoted field, a quote after spaces following a closing quote, or junk
    /// after a closing quote) is reported as an error instead of being parsed
    /// leniently. Corresponds to `CSV_STRICT`.
    pub fn strict(mut self, strict: bool) -> Self {
        self.strict = strict;
        self
    }

    /// When both this and [`strict`](Self::strict) are set, an unterminated
    /// quoted field at [`finish`](Self::finish) is an error. Corresponds to
    /// `CSV_STRICT_FINI`.
    pub fn strict_fini(mut self, strict_fini: bool) -> Self {
        self.strict_fini = strict_fini;
        self
    }

    fn is_space(b: u8) -> bool {
        b == SPACE || b == TAB
    }

    fn is_term(b: u8) -> bool {
        b == CR || b == LF
    }

    /// Feed a chunk of input. May be called repeatedly with successive chunks.
    pub fn parse<F: FnMut(Event)>(
        &mut self,
        data: &[u8],
        mut on_event: F,
    ) -> Result<(), ParseError> {
        let delim = self.delim;
        let quote = self.quote;
        let strict = self.strict;

        let mut state = self.state;
        let mut quoted = self.quoted;
        let mut spaces = self.spaces;
        let entry = &mut self.entry;

        let mut errored = false;
        let mut pos = 0;

        while pos < data.len() {
            let c = data[pos];
            pos += 1;

            match state {
                State::RowNotBegun | State::FieldNotBegun => {
                    if Self::is_space(c) && c != delim {
                        // Skip leading whitespace before a field.
                    } else if Self::is_term(c) {
                        if state == State::FieldNotBegun {
                            // A field boundary preceded the newline (e.g. "a,\n"):
                            // submit the trailing (possibly empty) field, end row.
                            submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                            submit_row(entry, &mut state, &mut quoted, &mut spaces, Some(c), &mut on_event);
                        }
                        // RowNotBegun + terminator => empty line; ignored.
                    } else if c == delim {
                        // Empty field (e.g. leading ",a" or the ",," in "a,,b").
                        submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                    } else if c == quote {
                        state = State::FieldBegun;
                        quoted = true;
                    } else {
                        state = State::FieldBegun;
                        quoted = false;
                        entry.push(c);
                    }
                }

                State::FieldBegun => {
                    if c == quote {
                        if quoted {
                            // Tentative closing quote: keep it for now, decide later.
                            entry.push(c);
                            state = State::FieldMightHaveEnded;
                        } else if strict {
                            errored = true;
                            break;
                        } else {
                            entry.push(c);
                            spaces = 0;
                        }
                    } else if c == delim {
                        if quoted {
                            entry.push(c); // literal delimiter inside quotes
                        } else {
                            submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                        }
                    } else if Self::is_term(c) {
                        if quoted {
                            entry.push(c); // literal newline inside quotes
                        } else {
                            submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                            submit_row(entry, &mut state, &mut quoted, &mut spaces, Some(c), &mut on_event);
                        }
                    } else if !quoted && Self::is_space(c) {
                        // Track trailing whitespace so we can strip it on submit.
                        entry.push(c);
                        spaces += 1;
                    } else {
                        entry.push(c);
                        spaces = 0;
                    }
                }

                State::FieldMightHaveEnded => {
                    if c == delim {
                        // Drop the spaces seen after the close quote plus the
                        // close quote itself, then submit.
                        let n = entry.len().saturating_sub(spaces + 1);
                        entry.truncate(n);
                        submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                    } else if Self::is_term(c) {
                        let n = entry.len().saturating_sub(spaces + 1);
                        entry.truncate(n);
                        submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                        submit_row(entry, &mut state, &mut quoted, &mut spaces, Some(c), &mut on_event);
                    } else if Self::is_space(c) {
                        entry.push(c);
                        spaces += 1;
                    } else if c == quote {
                        if spaces > 0 {
                            // A quote after some spaces is malformed.
                            if strict {
                                errored = true;
                                break;
                            }
                            spaces = 0;
                            entry.push(c);
                        } else {
                            // Two quotes in a row: the first one we kept stays as
                            // a literal quote; resume the field.
                            state = State::FieldBegun;
                        }
                    } else {
                        // Junk after a closing quote.
                        if strict {
                            errored = true;
                            break;
                        }
                        state = State::FieldBegun;
                        spaces = 0;
                        entry.push(c);
                    }
                }
            }
        }

        self.state = state;
        self.quoted = quoted;
        self.spaces = spaces;

        if errored {
            Err(ParseError)
        } else {
            Ok(())
        }
    }

    /// Flush any field/record left dangling because the input did not end in a
    /// terminator. Resets the parser so it can be reused afterwards.
    pub fn finish<F: FnMut(Event)>(&mut self, mut on_event: F) -> Result<(), ParseError> {
        let strict = self.strict;
        let strict_fini = self.strict_fini;
        let mut state = self.state;
        let mut quoted = self.quoted;
        let mut spaces = self.spaces;
        let entry = &mut self.entry;

        if strict && strict_fini && state == State::FieldBegun && quoted {
            // Unterminated quoted field.
            entry.clear();
            self.state = State::RowNotBegun;
            self.quoted = false;
            self.spaces = 0;
            return Err(ParseError);
        }

        match state {
            State::FieldMightHaveEnded => {
                let n = entry.len().saturating_sub(spaces + 1);
                entry.truncate(n);
                submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                submit_row(entry, &mut state, &mut quoted, &mut spaces, None, &mut on_event);
            }
            State::FieldNotBegun | State::FieldBegun => {
                submit_field(entry, &mut state, &mut quoted, &mut spaces, &mut on_event);
                submit_row(entry, &mut state, &mut quoted, &mut spaces, None, &mut on_event);
            }
            State::RowNotBegun => {
                // Already ended properly; nothing to flush.
            }
        }

        self.state = State::RowNotBegun;
        self.quoted = false;
        self.spaces = 0;
        self.entry.clear();
        Ok(())
    }
}

/// Equivalent of the C `SUBMIT_FIELD` macro: strip trailing spaces from an
/// unquoted field, hand the bytes to the callback, then reset field state.
fn submit_field<F: FnMut(Event)>(
    entry: &mut Vec<u8>,
    state: &mut State,
    quoted: &mut bool,
    spaces: &mut usize,
    on_event: &mut F,
) {
    if !*quoted {
        let n = entry.len().saturating_sub(*spaces);
        entry.truncate(n);
    }
    on_event(Event::Field(&entry[..]));
    *state = State::FieldNotBegun;
    entry.clear();
    *quoted = false;
    *spaces = 0;
}

/// Equivalent of the C `SUBMIT_ROW` macro.
fn submit_row<F: FnMut(Event)>(
    entry: &mut Vec<u8>,
    state: &mut State,
    quoted: &mut bool,
    spaces: &mut usize,
    terminator: Option<u8>,
    on_event: &mut F,
) {
    on_event(Event::EndOfRecord(terminator));
    *state = State::RowNotBegun;
    entry.clear();
    *quoted = false;
    *spaces = 0;
}

/// Convenience wrapper: parse a whole buffer into records of UTF-8 strings.
pub fn parse_records(data: &[u8]) -> Result<Vec<Vec<String>>, ParseError> {
    let mut parser = Parser::new();
    let mut records: Vec<Vec<String>> = Vec::new();
    let mut current: Vec<String> = Vec::new();

    let mut handle = |ev: Event| match ev {
        Event::Field(bytes) => current.push(String::from_utf8_lossy(bytes).into_owned()),
        Event::EndOfRecord(_) => records.push(std::mem::take(&mut current)),
    };

    parser.parse(data, &mut handle)?;
    parser.finish(&mut handle)?;
    Ok(records)
}

pub fn csv_write2(
    dest: Option<&mut [u8]>, 
    src: &[u8], 
    quote: u8
) -> usize {
    // If dest is None, we treat it as an empty/dummy writer that just discards data
    // but allows us to keep track of bytes written.
    let mut writer = dest.unwrap_or(&mut []);
    let mut chars: usize = 0;

    // Helper macro to handle buffer boundary checks and tracking character counts safely
    macro_rules! write_byte {
        ($byte:expr) => {
            if !writer.is_empty() {
                // write_all on a slice advances the slice pointer internally if we split it,
                // or we can just manipulate the slice manually:
                let (head, tail) = writer.split_at_mut(1);
                head[0] = $byte;
                writer = tail;
            }
            chars = chars.saturating_add(1);
        };
    }

    // Write the opening quote
    write_byte!(quote);

    // Process the source slice
    for &byte in src {
        if byte == quote {
            write_byte!(quote);
        }
        write_byte!(byte);
    }

    // Write the closing quote
    write_byte!(quote);

    chars
}

pub fn csv_fwrite2<W: Write>(
    mut writer: W, 
    src: &[u8], 
    quote: u8
) -> io::Result<()> {
    // Write opening quote
    writer.write_all(&[quote])?;

    // Process source bytes
    for &byte in src {
        if byte == quote {
            writer.write_all(&[quote])?;
        }
        writer.write_all(&[byte])?;
    }

    // Write closing quote
    writer.write_all(&[quote])?;

    Ok(())
}


fn test_writer2(input: &[u8], expected: &[u8], quote: u8) {
    let buf_size = input.len() * 2 + 2;
    let mut temp = vec![0u8; buf_size];

    let actual_len = csv_write2(Some(&mut temp), input, quote);

    assert_eq!(
        actual_len, 
        expected.len(), 
        "Actual length ({actual_len}) doesn't match expected length ({})", expected.len()
    );
    
    assert_eq!(
        &temp[..actual_len], 
        expected, 
        "Actual data doesn't match expected data"
    );
}

fn main() {
    // Demonstrate streaming: the same input is fed in two arbitrary chunks.
    let mut parser = Parser::new();
    let chunk_a = b"name,age,city\r\nAda,36,\"Lon";
    let chunk_b = b"don, UK\"\nGrace , 41 , NYC\n";

    let mut row: Vec<String> = Vec::new();
    let mut emit = |ev: Event| match ev {
        Event::Field(b) => row.push(String::from_utf8_lossy(b).into_owned()),
        Event::EndOfRecord(_) => {
            println!("{:?}", row);
            row.clear();
        }
    };

    parser.parse(chunk_a, &mut emit).unwrap();
    parser.parse(chunk_b, &mut emit).unwrap();
    parser.finish(&mut emit).unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    /// An observed parse event, used to compare against expectations.
    #[derive(Debug, Clone, PartialEq, Eq)]
    enum Ev {
        Col(Vec<u8>),
        Row(Option<u8>),
    }

    fn col(s: &[u8]) -> Ev {
        Ev::Col(s.to_vec())
    }
    fn row(t: Option<u8>) -> Ev {
        Ev::Row(t)
    }

    /// The heart of the C test harness: parse `input` at *every* chunk size
    /// from 1..=len, and assert that each run produces exactly `expected`
    /// (and that an error is/ isn't raised, matching `expect_err`). This is what
    /// stresses the incremental parser across every possible buffer boundary.
    fn assert_parses(
        input: &[u8],
        delim: u8,
        quote: u8,
        strict: bool,
        strict_fini: bool,
        expected: &[Ev],
        expect_err: bool,
    ) {
        let len = input.len();
        let max = len.max(1); // run at least once, even for empty input
        for size in 1..=max {
            let mut parser = Parser::new()
                .with_delimiter(delim)
                .with_quote(quote)
                .strict(strict)
                .strict_fini(strict_fini);

            let mut actual: Vec<Ev> = Vec::new();
            let mut errored = false;
            {
                let mut handle = |ev: Event| match ev {
                    Event::Field(b) => actual.push(Ev::Col(b.to_vec())),
                    Event::EndOfRecord(t) => actual.push(Ev::Row(t)),
                };

                let mut off = 0;
                while off < len {
                    let end = (off + size).min(len);
                    if parser.parse(&input[off..end], &mut handle).is_err() {
                        errored = true;
                        break;
                    }
                    off = end;
                }
                if !errored && parser.finish(&mut handle).is_err() {
                    errored = true;
                }
            }

            assert_eq!(
                errored, expect_err,
                "error-flag mismatch at chunk size {size} for input {input:?}"
            );
            assert_eq!(
                actual, expected,
                "event mismatch at chunk size {size} for input {input:?}"
            );
        }
    }

    const C: u8 = b',';
    const Q: u8 = b'"';

    #[test]
    fn test01() {
        let input = b" 1,2 ,  3         ,4,5\x0d\x0a";
        let expected = [
            col(b"1"), col(b"2"), col(b"3"), col(b"4"), col(b"5"),
            row(Some(b'\r')),
        ];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false); // CSV_STRICT
    }

    #[test]
    fn test02() {
        let input = b",,,,,\x0a";
        let expected = [
            col(b""), col(b""), col(b""), col(b""), col(b""), col(b""),
            row(Some(b'\n')),
        ];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn test03() {
        let input = b"\",\",\",\",\"\"";
        let expected = [col(b","), col(b","), col(b""), row(None)];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn test04() {
        let input = b"\"I call our world Flatland,\nnot because we call it so,\nbut to make its nature clearer\nto you, my happy readers,\nwho are privileged to live in Space.\"";
        let content = b"I call our world Flatland,\nnot because we call it so,\nbut to make its nature clearer\nto you, my happy readers,\nwho are privileged to live in Space.";
        let expected = [col(content), row(None)];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn test05() {
        let input = b"\"\"\"a,b\"\"\",,\" \"\"\"\" \",\"\"\"\"\" \",\" \"\"\"\"\",\"\"\"\"\"\"";
        let expected = [
            col(b"\"a,b\""),
            col(b""),
            col(b" \"\" "),
            col(b"\"\" "),
            col(b" \"\""),
            col(b"\"\""),
            row(None),
        ];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false); // CSV_STRICT
        assert_parses(input, C, Q, true, true, &expected, false);  // CSV_STRICT | CSV_STRICT_FINI
    }

    #[test]
    fn test06() {
        let input = b"\" a, b ,c \", a b  c,";
        let expected = [col(b" a, b ,c "), col(b"a b  c"), col(b""), row(None)];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn test07() {
        let input = b"\" \"\" \" \" \"\" \"";
        let expected = [col(b" \" \" \" \" "), row(None)];
        assert_parses(input, C, Q, false, false, &expected, false);
    }

    #[test]
    fn test07b() {
        // Same data, but CSV_STRICT turns the quote-after-spaces into an error.
        let input = b"\" \"\" \" \" \"\" \"";
        assert_parses(input, C, Q, true, false, &[], true);
    }

    #[test]
    fn test08() {
        // A quote embedded in a quoted field, followed by a very long run of
        // spaces (forcing many buffer growths), then a closing quote + comma.
        let pad = 458usize;
        let mut input = vec![b'"'];
        input.extend_from_slice(b" abc\"");
        input.extend(std::iter::repeat(b' ').take(pad));
        input.extend_from_slice(b"\", \"123\"");

        let mut field1 = Vec::new();
        field1.extend_from_slice(b" abc\"");
        field1.extend(std::iter::repeat(b' ').take(pad));
        assert_eq!(field1.len(), 463);

        let expected = [Ev::Col(field1), col(b"123"), row(None)];
        assert_parses(&input, C, Q, false, false, &expected, false);
    }

    #[test]
    fn test09() {
        // Empty input: no events at all.
        assert_parses(b"", C, Q, false, false, &[], false);
    }

    #[test]
    fn test10() {
        assert_parses(b"a\x0a", C, Q, false, false, &[col(b"a"), row(Some(b'\n'))], false);
    }

    #[test]
    fn test11() {
        let expected = [col(b"1"), col(b"2"), col(b"3"), col(b"4"), row(Some(b'\n'))];
        assert_parses(b"1,2 ,3,4\x0a", C, Q, false, false, &expected, false);
    }

    #[test]
    fn test12() {
        // Blank lines produce no rows by default.
        assert_parses(b"\x0a\x0a\x0a\x0a", C, Q, false, false, &[], false);
    }

    #[test]
    fn test13() {
        assert_parses(b"\"abc\"", C, Q, false, false, &[col(b"abc"), row(None)], false);
    }

    #[test]
    fn test14() {
        let input = b"1, 2, 3,\x0a\x0d\x0a  \"4\", \x0d,";
        let expected = [
            col(b"1"), col(b"2"), col(b"3"), col(b""), row(Some(b'\n')),
            col(b"4"), col(b""), row(Some(b'\r')),
            col(b""), col(b""), row(None),
        ];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn test15() {
        let input = b"1, 2, 3,\x0a\x0d\x0a  \"4\", \x0d\"\"";
        let expected = [
            col(b"1"), col(b"2"), col(b"3"), col(b""), row(Some(b'\n')),
            col(b"4"), col(b""), row(Some(b'\r')),
            col(b""), row(None),
        ];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn test16() {
        // Unterminated quoted field. Lenient and plain CSV_STRICT both accept it.
        let input = b"\"1\",\"2\",\" 3 ";
        let expected = [col(b"1"), col(b"2"), col(b" 3 "), row(None)];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false); // CSV_STRICT (no FINI)
    }

    #[test]
    fn test16b() {
        // CSV_STRICT | CSV_STRICT_FINI rejects the unterminated quoted field.
        let input = b"\"1\",\"2\",\" 3 ";
        let expected = [col(b"1"), col(b"2")];
        assert_parses(input, C, Q, true, true, &expected, true);
    }

    #[test]
    fn test17() {
        // Embedded NUL bytes are ordinary data.
        let input = b" a\x00b\x00c ";
        let expected = [col(b"a\x00b\x00c"), row(None)];
        assert_parses(input, C, Q, false, false, &expected, false);
        assert_parses(input, C, Q, true, false, &expected, false);
    }

    #[test]
    fn custom01() {
        // Same shape as test05 but with ';' as delimiter and '\'' as quote.
        let input = b"'''a;b''';;' '''' ';''''' ';' ''''';''''''";
        let expected = [
            col(b"'a;b'"),
            col(b""),
            col(b" '' "),
            col(b"'' "),
            col(b" ''"),
            col(b"''"),
            row(None),
        ];
        assert_parses(input, b';', b'\'', false, false, &expected, false);
    }

    #[test]
    fn test_case_1_standard_quote() {
        // test_writer("1", "abc", 3, "\"abc\"", 5);
        // Using standard double quote (ASCII 34)
        test_writer2(b"abc", b"\"abc\"", b'"');
    }

    #[test]
    fn test_case_2_standard_quote_heavy() {
        // test_writer("2", "\"\"\"\"\"\"\"\"", 8, "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"", 18);
        // br#"..."# is a raw byte string. It ignores quotes inside it!
        let input = br#""""""""#; 
        let expected = br#""""""""""""""""#;
        
        test_writer2(input, expected, b'"');
    }

    #[test]
    fn test_case_1_custom_quote() {
        // test_writer2("1", "abc", 3, "'abc'", 5, '\'');
        test_writer2(b"abc", b"'abc'", b'\'');
    }

    #[test]
    fn test_case_2_custom_quote_heavy() {
        // test_writer2("2", "''''''''", 8, "''''''''''''''''''", 18, '\'');
        test_writer2(b"''''''''", b"''''''''''''''''''", b'\'');
    }
}
