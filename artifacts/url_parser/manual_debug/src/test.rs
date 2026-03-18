use crate::*;

pub fn url_get_protocol(url: Option<&str>) -> Option<String> {
	println!("* url_get_protocol");
    url_get_scheme(url)
}
pub fn url_get_hash(url: Option<&str>) -> Option<String> {
	println!("* url_get_hash");
    url_get_fragment(url)
}
