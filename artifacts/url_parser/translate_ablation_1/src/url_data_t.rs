use crate::*;

#[derive(Clone)]
pub struct UrlData {
    pub whole_url: Option<String>,
    pub protocol: Option<String>,
    pub userinfo: Option<String>,
    pub host: Option<String>,
    pub port: Option<String>,
    pub path: Option<String>,
    pub query: Option<Vec<UrlKeyValue>>,
    pub fragment: Option<String>,
}

