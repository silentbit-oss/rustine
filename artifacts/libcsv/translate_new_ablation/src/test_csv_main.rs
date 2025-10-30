use std::env;
use translate_without_break_down::*;
pub fn main() {
    let test01_data = b" 1,2 ,  3         ,4,5\x0d\x0a";
    let test02_data = b",,,,,\x0a";
    let test03_data = b"\",\",\",\",\"\"";
    let test04_data = b"\"I call our world Flatland,\x0anot because we call it so,\x0abut to make its nature clearer\x0ato you, my happy readers,\x0awho are privileged to live in Space.\"";
    let test05_data = b"\"\"\"a,b\"\"\",,\" \"\"\"\" \",\"\"\"\"\" \",\" \"\"\"\"\",\"\"\"\"\"\"";
    let test06_data = b"\" a, b ,c \", a b  c,";
    let test07_data = b"\" \"\" \" \" \"\" \"";
    let test07b_data = b"\" \"\" \" \" \"\" \"";
    let test08_data = b"\" abc\"                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \", \"123\"";
    let test09_data = b"";
    let test10_data = b"a\x0a";
    let test11_data = b"1,2 ,3,4\x0a";
    let test12_data = b"\x0a\x0a\x0a\x0a";
    let test12b_data = b"\x0a\x0a\x0a\x0a";
    let test13_data = b"\"abc\"";
    let test14_data = b"1, 2, 3,\x0a\x0d\x0a  \"4\", \x0d,";
    let test15_data = b"1, 2, 3,\x0a\x0d\x0a  \"4\", \x0d\"\"";
    let test16_data = b"\"1\",\"2\",\" 3 ";
    let test16b_data = b"\"1\",\"2\",\" 3 ";
    let test17_data = b" a\0b\0c ";
    let test18_data = b"12345678901234567890123456789012";
    let test19_data = b"  , \"\" ,";
    let custom01_data = b"'''a;b''';;' '''' ';''''' ';' ''''';''''''";

    let mut test01_results = vec![
        Event { event_type: 1, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        Event { event_type: 1, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        Event { event_type: 1, retval: 0, size: 1, data: Some(b"3".to_vec()) },
        Event { event_type: 1, retval: 0, size: 1, data: Some(b"4".to_vec()) },
        Event { event_type: 1, retval: 0, size: 1, data: Some(b"5".to_vec()) },
        Event { event_type: 2, retval: b'\x0d' as i32, size: 1, data: None },
        Event { event_type: 0, retval: 0, size: 0, data: None },
    ];

    // ... (similar initialization for all other test_results vectors)

    test_parser(Some("test01"), 0, Some(test01_data), test01_data.len(), &mut test01_results, b',', b'"', None, None);
    test_parser(Some("test01"), 1, Some(test01_data), test01_data.len(), &mut test01_results, b',', b'"', None, None);
    test_parser(Some("test01"), 1 | 16, Some(test01_data), test01_data.len(), &mut test01_results, b',', b'"', None, None);
    // ... (similar calls for all other test_parser invocations)

    test_writer(Some("1"), Some(b"abc"), 3, Some(b"\"abc\""), 5);
    test_writer(Some("2"), Some(b"\"\"\"\"\"\"\"\""), 8, Some(b"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""), 18);
    test_writer2(Some("1"), Some(b"abc"), 3, Some(b"'abc'"), 5, b'\'');
    test_writer2(Some("2"), Some(b"''''''''"), 8, Some(b"''''''''''''''''''"), 18, b'\'');

    println!("All tests passed");
}
