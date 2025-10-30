use crate::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LfsOpenFlags {
    Rdonly = 1,
    Wronly = 2,
    Rdwr = 3,
}

pub struct LfsFlags;
impl LfsFlags {
    pub const O_CREAT: i32 = 0x0100;
    pub const O_EXCL: i32 = 0x0200;
    pub const O_TRUNC: i32 = 0x0400;
    pub const O_APPEND: i32 = 0x0800;
    pub const F_DIRTY: i32 = 0x010000;
    pub const F_WRITING: i32 = 0x020000;
    pub const F_READING: i32 = 0x040000;
    pub const F_ERRED: i32 = 0x080000;
    pub const F_INLINE: i32 = 0x100000;
}

