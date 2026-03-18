use translate::*;
use std::env;
fn main() {
    let gh_url = "git://git@github.com:jwerle/url.h.git";
    let url = "http://user:pass@subdomain.host.com:8080/p/%C3%A5/t/h?qu%C3%ABry=strin%C4%9F&foo=bar=yuk&key%23%26%3D=%25&lol#h%C3%A6sh";

    let parsed = url_parse(Some(url));
    let gh_parsed = url_parse(Some(gh_url));

    assert!(parsed.is_some());
    assert!(gh_parsed.is_some());

    if let Some(p) = parsed.as_ref() {
        url_data_inspect(Some(p));
    }

    if let Some(gp) = gh_parsed.as_ref() {
        url_data_inspect(Some(gp));
    }

    assert!(parsed.as_ref().unwrap().whole_url.is_some());
    assert!(parsed.as_ref().unwrap().protocol.is_some());
    assert!(parsed.as_ref().unwrap().userinfo.is_some());
    assert!(parsed.as_ref().unwrap().host.is_some());
    assert!(parsed.as_ref().unwrap().port.is_some());
    assert!(parsed.as_ref().unwrap().path.is_some());
    assert!(parsed.as_ref().unwrap().query.is_some());
    assert!(parsed.as_ref().unwrap().fragment.is_some());

    assert!(gh_parsed.as_ref().unwrap().whole_url.is_some());
    assert!(gh_parsed.as_ref().unwrap().protocol.is_some());
    assert!(gh_parsed.as_ref().unwrap().userinfo.is_some());
    assert!(gh_parsed.as_ref().unwrap().host.is_some());
    assert!(gh_parsed.as_ref().unwrap().path.is_some());

    assert!(url_is_protocol(Some("http")));
    assert!(url_is_protocol(Some("https")));
    assert!(url_is_protocol(Some("git")));
    assert!(url_is_protocol(Some("ssh")));
    assert!(url_is_protocol(Some("sftp")));
    assert!(url_is_protocol(Some("ftp")));
    assert!(url_is_protocol(Some("javascript")));

    loop {
        url_get_protocol(Some(url)); // `url_get_protocol` does not return a value, so we directly call it without expecting a return value.
        break;
    }

    loop {
        let s = url_get_userinfo(Some(url)).unwrap_or_default();
        assert!(s == "user:pass");
        break;
    }

    loop {
        let s = url_get_hostname(Some(url)).unwrap_or_default();
        assert!(s == "subdomain.host.com");
        break;
    }

    loop {
        let s = url_get_path(Some(url)).unwrap_or_default();
        assert!(s == "/p/%C3%A5/t/h");
        break;
    }

    assert!(url_get_query_value(parsed.as_ref(), Some("qu%C3%ABry")).unwrap_or_default() == "strin\u{030C}\u{00F1}");
    assert!(url_get_query_value(parsed.as_ref(), Some("foo")).unwrap_or_default() == "bar=yuk");
    assert!(url_get_query_value(parsed.as_ref(), Some("key#&=")).unwrap_or_default() == "%");
    assert!(url_get_query_value(parsed.as_ref(), Some("lol")).unwrap_or_default() == "");

    loop {
        let s = url_get_fragment(Some(url)).unwrap_or_default();
        assert!(s == "hæsh");
        break;
    }

    loop {
        let s = url_get_port(Some(url)).unwrap_or_default();
        assert!(s == "8080");
        break;
    }

    loop {
        url_get_protocol(Some(gh_url)); // Similarly, we directly call `url_get_protocol` since it doesn't return a value.
        break;
    }

    loop {
        let s = url_get_hostname(Some(gh_url)).unwrap_or_default();
        assert!(s == "github.com");
        break;
    }

    loop {
        let s = url_get_userinfo(Some(gh_url)).unwrap_or_default();
        assert!(s == "git");
        break;
    }

    loop {
        let s = url_get_path(Some(gh_url)).unwrap_or_default();
        assert!(s == "/jwerle/url.h.git");
        break;
    }

    url_free(parsed);
    url_free(gh_parsed);
}
