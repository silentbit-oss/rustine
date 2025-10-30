use ::libc;
extern "C" {
    pub type url_key_value;
    fn free(_: *mut libc::c_void);
    fn url_parse(url: *const libc::c_char) -> *mut url_data_t;
    fn url_get_scheme(url: *const libc::c_char) -> *mut libc::c_char;
    fn url_get_userinfo(url: *const libc::c_char) -> *mut libc::c_char;
    fn url_get_hostname(url: *const libc::c_char) -> *mut libc::c_char;
    fn url_get_path(url: *const libc::c_char) -> *mut libc::c_char;
    fn url_get_query_value(
        url: *const url_data_t,
        key: *const libc::c_char,
    ) -> *const libc::c_char;
    fn url_get_fragment(url: *const libc::c_char) -> *mut libc::c_char;
    fn url_get_port(url: *const libc::c_char) -> *mut libc::c_char;
    fn url_free(data: *mut url_data_t);
    fn url_is_protocol(str: *const libc::c_char) -> bool;
    fn url_data_inspect(data: *const url_data_t);
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct url_data {
    pub whole_url: *mut libc::c_char,
    pub protocol: *const libc::c_char,
    pub userinfo: *const libc::c_char,
    pub host: *const libc::c_char,
    pub port: *const libc::c_char,
    pub path: *const libc::c_char,
    pub query: *const url_key_value,
    pub fragment: *const libc::c_char,
}
pub type url_data_t = url_data;
#[inline]
unsafe extern "C" fn url_get_protocol(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    return url_get_scheme(url);
}
unsafe fn main_0() -> libc::c_int {
    let mut gh_url: *mut libc::c_char = b"git://git@github.com:jwerle/url.h.git\0"
        as *const u8 as *const libc::c_char as *mut libc::c_char;
    let mut url: *mut libc::c_char = b"http://user:pass@subdomain.host.com:8080/p/%C3%A5/t/h?qu%C3%ABry=strin%C4%9F&foo=bar=yuk&key%23%26%3D=%25&lol#h%C3%a6sh\0"
        as *const u8 as *const libc::c_char as *mut libc::c_char;
    let mut parsed: *mut url_data_t = url_parse(url);
    let mut gh_parsed: *mut url_data_t = url_parse(gh_url);
    if !parsed.is_null() {} else {
        __assert_fail(
            b"parsed\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            25 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !gh_parsed.is_null() {} else {
        __assert_fail(
            b"gh_parsed\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            26 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    url_data_inspect(parsed);
    url_data_inspect(gh_parsed);
    if !((*parsed).whole_url).is_null() {} else {
        __assert_fail(
            b"parsed->whole_url\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            31 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).protocol).is_null() {} else {
        __assert_fail(
            b"parsed->protocol\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            32 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).userinfo).is_null() {} else {
        __assert_fail(
            b"parsed->userinfo\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            33 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).host).is_null() {} else {
        __assert_fail(
            b"parsed->host\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            34 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).port).is_null() {} else {
        __assert_fail(
            b"parsed->port\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            35 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).path).is_null() {} else {
        __assert_fail(
            b"parsed->path\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            36 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).query).is_null() {} else {
        __assert_fail(
            b"parsed->query\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            37 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*parsed).fragment).is_null() {} else {
        __assert_fail(
            b"parsed->fragment\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            38 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*gh_parsed).whole_url).is_null() {} else {
        __assert_fail(
            b"gh_parsed->whole_url\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            40 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*gh_parsed).protocol).is_null() {} else {
        __assert_fail(
            b"gh_parsed->protocol\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            41 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*gh_parsed).userinfo).is_null() {} else {
        __assert_fail(
            b"gh_parsed->userinfo\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            42 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*gh_parsed).host).is_null() {} else {
        __assert_fail(
            b"gh_parsed->host\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            43 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if !((*gh_parsed).path).is_null() {} else {
        __assert_fail(
            b"gh_parsed->path\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            44 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"http\0" as *const u8 as *const libc::c_char) as libc::c_int != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"http\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            46 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"https\0" as *const u8 as *const libc::c_char) as libc::c_int
        != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"https\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            47 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"git\0" as *const u8 as *const libc::c_char) as libc::c_int != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"git\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            48 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"ssh\0" as *const u8 as *const libc::c_char) as libc::c_int != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"ssh\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            49 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"sftp\0" as *const u8 as *const libc::c_char) as libc::c_int != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"sftp\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            50 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"ftp\0" as *const u8 as *const libc::c_char) as libc::c_int != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"ftp\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            51 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if url_is_protocol(b"javascript\0" as *const u8 as *const libc::c_char)
        as libc::c_int != 0
    {} else {
        __assert_fail(
            b"url_is_protocol(\"javascript\")\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            52 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    let mut s: *mut libc::c_char = url_get_protocol(url);
    if !s.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            54 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"http\0" as *const u8 as *const libc::c_char, s) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"http\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            54 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s as *mut libc::c_void);
    let mut s_0: *mut libc::c_char = url_get_userinfo(url);
    if !s_0.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            55 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"user:pass\0" as *const u8 as *const libc::c_char, s_0)
        == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"user:pass\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            55 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_0 as *mut libc::c_void);
    let mut s_1: *mut libc::c_char = url_get_hostname(url);
    if !s_1.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            56 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"subdomain.host.com\0" as *const u8 as *const libc::c_char, s_1)
        == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"subdomain.host.com\", s) == 0\0" as *const u8
                as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            56 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_1 as *mut libc::c_void);
    let mut s_2: *mut libc::c_char = url_get_path(url);
    if !s_2.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            57 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"/p/\xC3\xA5/t/h\0" as *const u8 as *const libc::c_char, s_2)
        == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"/p/\\xc3\\xa5/t/h\", s) == 0\0" as *const u8
                as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            57 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_2 as *mut libc::c_void);
    if strcmp(
        b"strin\xC4\x9F\0" as *const u8 as *const libc::c_char,
        url_get_query_value(
            parsed,
            b"qu\xC3\xABry\0" as *const u8 as *const libc::c_char,
        ),
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"strin\\xc4\\x9f\", url_get_query_value (parsed, \"qu\\xc3\\xabry\"))==0\0"
                as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            58 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(
        b"bar=yuk\0" as *const u8 as *const libc::c_char,
        url_get_query_value(parsed, b"foo\0" as *const u8 as *const libc::c_char),
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"bar=yuk\", url_get_query_value (parsed, \"foo\"))==0\0"
                as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            59 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(
        b"%\0" as *const u8 as *const libc::c_char,
        url_get_query_value(parsed, b"key#&=\0" as *const u8 as *const libc::c_char),
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"%\", url_get_query_value (parsed, \"key#&=\"))==0\0" as *const u8
                as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            60 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(
        b"\0" as *const u8 as *const libc::c_char,
        url_get_query_value(parsed, b"lol\0" as *const u8 as *const libc::c_char),
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"\", url_get_query_value (parsed, \"lol\"))==0\0" as *const u8
                as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            61 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    let mut s_3: *mut libc::c_char = url_get_fragment(url);
    if !s_3.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            62 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"h\xC3\xA6sh\0" as *const u8 as *const libc::c_char, s_3)
        == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"h\xC3\xA6sh\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            62 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_3 as *mut libc::c_void);
    let mut s_4: *mut libc::c_char = url_get_port(url);
    if !s_4.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            63 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"8080\0" as *const u8 as *const libc::c_char, s_4) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"8080\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            63 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_4 as *mut libc::c_void);
    let mut s_5: *mut libc::c_char = url_get_protocol(gh_url);
    if !s_5.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            65 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"git\0" as *const u8 as *const libc::c_char, s_5) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"git\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            65 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_5 as *mut libc::c_void);
    let mut s_6: *mut libc::c_char = url_get_hostname(gh_url);
    if !s_6.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            66 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"github.com\0" as *const u8 as *const libc::c_char, s_6)
        == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"github.com\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            66 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_6 as *mut libc::c_void);
    let mut s_7: *mut libc::c_char = url_get_userinfo(gh_url);
    if !s_7.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            67 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"git\0" as *const u8 as *const libc::c_char, s_7) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"git\", s) == 0\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            67 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_7 as *mut libc::c_void);
    let mut s_8: *mut libc::c_char = url_get_path(gh_url);
    if !s_8.is_null() {} else {
        __assert_fail(
            b"s\0" as *const u8 as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            68 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    if strcmp(b"jwerle/url.h.git\0" as *const u8 as *const libc::c_char, s_8)
        == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(\"jwerle/url.h.git\", s) == 0\0" as *const u8
                as *const libc::c_char,
            b"test.c\0" as *const u8 as *const libc::c_char,
            68 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 15],
                &[libc::c_char; 15],
            >(b"int main(void)\0"))
                .as_ptr(),
        );
    };
    free(s_8 as *mut libc::c_void);
    url_free(parsed);
    url_free(gh_parsed);
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
