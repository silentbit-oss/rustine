use crate::*;

pub type AllocFunc = fn(opaque: voidpf, items: uInt, size: uInt) -> voidpf;

