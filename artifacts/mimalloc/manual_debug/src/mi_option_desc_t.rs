use crate::*;
use crate::MiInitT;


#[derive(Clone)]
pub struct MiOptionDescS {
    pub value: i64,
    pub init: MiInitT,
    pub option: MiOptionT,
    pub name: Option<String>,
    pub legacy_name: Option<String>,
}

pub type MiOptionDescT = MiOptionDescS;

