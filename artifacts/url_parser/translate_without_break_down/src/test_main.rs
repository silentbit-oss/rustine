use translate_without_break_down::*;
use std::env;
use std::ffi::CStr;

pub fn main() {
    let gh_url = "git://git@github.com:jwerle/url.h.git";
    let url = "http://user:pass@subdomain.host.com:8080/p/%C3%A5/t/h?qu%C3%ABry=strin%C4%9F&foo=bar=yuk&key%23%26%3D=%25&lol#h%C3%a6sh";
    
    let parsed = url_parse(Some(url));
    let gh_parsed = url_parse(Some(gh_url));
    assert!(parsed.is_some());
    assert!(gh_parsed.is_some());
    
    url_data_inspect(parsed.as_ref().unwrap());
    url_data_inspect(gh_parsed.as_ref().unwrap());
    
    let parsed_ref = parsed.as_ref().unwrap();
    assert!(parsed_ref.whole_url.is_some());
    assert!(parsed_ref.protocol.is_some());
    assert!(parsed_ref.userinfo.is_some());
    assert!(parsed_ref.host.is_some());
    assert!(parsed_ref.port.is_some());
    assert!(parsed_ref.path.is_some());
    assert!(parsed_ref.query.is_some());
    assert!(parsed_ref.fragment.is_some());
    
    let gh_parsed_ref = gh_parsed.as_ref().unwrap();
    assert!(gh_parsed_ref.whole_url.is_some());
    assert!(gh_parsed_ref.protocol.is_some());
    assert!(gh_parsed_ref.userinfo.is_some());
    assert!(gh_parsed_ref.host.is_some());
    assert!(gh_parsed_ref.path.is_some());
    
    assert!(url_is_protocol(Some("http")));
    assert!(url_is_protocol(Some("https")));
    assert!(url_is_protocol(Some("git")));
    assert!(url_is_protocol(Some("ssh")));
    assert!(url_is_protocol(Some("sftp")));
    assert!(url_is_protocol(Some("ftp")));
    assert!(url_is_protocol(Some("javascript")));
    
    {
        let s = url_get_protocol(Some(url));
        assert!(s.is_some());
        assert_eq!("http", s.unwrap());
    }
    
    {
        let s = url_get_userinfo(Some(url));
        assert!(s.is_some());
        assert_eq!("user:pass", s.unwrap());
    }
    
    {
        let s = url_get_hostname(Some(url));
        assert!(s.is_some());
        assert_eq!("subdomain.host.com", s.unwrap());
    }
    
    {
        let s = url_get_path(Some(url));
        assert!(s.is_some());
        assert_eq!("/p/å/t/h", s.unwrap());
    }
    
    assert_eq!("strinğ", url_get_query_value(parsed_ref, Some("quêry")).unwrap());
    assert_eq!("bar=yuk", url_get_query_value(parsed_ref, Some("foo")).unwrap());
    assert_eq!("%", url_get_query_value(parsed_ref, Some("key#&=")).unwrap());
    assert_eq!("", url_get_query_value(parsed_ref, Some("lol")).unwrap());
    
    {
        let s = url_get_fragment(Some(url));
        assert!(s.is_some());
        assert_eq!("hæsh", s.unwrap());
    }
    
    {
        let s = url_get_port(Some(url));
        assert!(s.is_some());
        assert_eq!("8080", s.unwrap());
    }
    
    {
        let s = url_get_protocol(Some(gh_url));
        assert!(s.is_some());
        assert_eq!("git", s.unwrap());
    }
    
    {
        let s = url_get_hostname(Some(gh_url));
        assert!(s.is_some());
        assert_eq!("github.com", s.unwrap());
    }
    
    {
        let s = url_get_userinfo(Some(gh_url));
        assert!(s.is_some());
        assert_eq!("git", s.unwrap());
    }
    
    {
        let s = url_get_path(Some(gh_url));
        assert!(s.is_some());
        assert_eq!("jwerle/url.h.git", s.unwrap());
    }
    
    url_free(parsed);
    url_free(gh_parsed);
}
