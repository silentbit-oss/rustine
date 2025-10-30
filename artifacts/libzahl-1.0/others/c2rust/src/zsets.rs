use ::libc;
extern "C" {
    fn zset(_: *mut C2RustUnnamed, _: *mut C2RustUnnamed);
    fn zadd(_: *mut C2RustUnnamed, _: *mut C2RustUnnamed, _: *mut C2RustUnnamed);
    fn zmul(_: *mut C2RustUnnamed, _: *mut C2RustUnnamed, _: *mut C2RustUnnamed);
    fn __errno_location() -> *mut libc::c_int;
    static mut libzahl_tmp_str_num: z_t;
    static mut libzahl_const_1e19: z_t;
    fn __ctype_b_loc() -> *mut *const libc::c_ushort;
}
pub type size_t = libc::c_ulong;
pub type __uint32_t = libc::c_uint;
pub type uint32_t = __uint32_t;
pub type zahl_char_t = uint32_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed {
    pub sign: libc::c_int,
    pub used: size_t,
    pub alloced: size_t,
    pub chars: *mut zahl_char_t,
}
pub type z_t = [C2RustUnnamed; 1];
pub const _ISdigit: C2RustUnnamed_0 = 2048;
pub type C2RustUnnamed_0 = libc::c_uint;
pub const _ISalnum: C2RustUnnamed_0 = 8;
pub const _ISpunct: C2RustUnnamed_0 = 4;
pub const _IScntrl: C2RustUnnamed_0 = 2;
pub const _ISblank: C2RustUnnamed_0 = 1;
pub const _ISgraph: C2RustUnnamed_0 = 32768;
pub const _ISprint: C2RustUnnamed_0 = 16384;
pub const _ISspace: C2RustUnnamed_0 = 8192;
pub const _ISxdigit: C2RustUnnamed_0 = 4096;
pub const _ISalpha: C2RustUnnamed_0 = 1024;
pub const _ISlower: C2RustUnnamed_0 = 512;
pub const _ISupper: C2RustUnnamed_0 = 256;
#[inline]
unsafe extern "C" fn zsignum(mut a: *mut C2RustUnnamed) -> libc::c_int {
    return (*a).sign;
}
#[no_mangle]
pub unsafe extern "C" fn zsets(
    mut a: *mut C2RustUnnamed,
    mut str: *const libc::c_char,
) -> libc::c_int {
    let mut temp: libc::c_ulonglong = 0 as libc::c_int as libc::c_ulonglong;
    let mut neg: libc::c_int = (*str as libc::c_int == '-' as i32) as libc::c_int;
    let mut str_end: *const libc::c_char = 0 as *const libc::c_char;
    str = str
        .offset((neg != 0 || *str as libc::c_int == '+' as i32) as libc::c_int as isize);
    if *str == 0 {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    str_end = str;
    while *str_end != 0 {
        if *(*__ctype_b_loc()).offset(*str_end as libc::c_int as isize) as libc::c_int
            & _ISdigit as libc::c_int as libc::c_ushort as libc::c_int == 0
        {
            *__errno_location() = 22 as libc::c_int;
            return -(1 as libc::c_int);
        }
        str_end = str_end.offset(1);
        str_end;
    }
    (*a).sign = 0 as libc::c_int;
    zset(libzahl_tmp_str_num.as_mut_ptr(), libzahl_const_1e19.as_mut_ptr());
    's_192: {
        let mut current_block_39: u64;
        match str_end.offset_from(str) as libc::c_long
            % 19 as libc::c_int as libc::c_long
        {
            0 => {
                current_block_39 = 1146658625155211681;
            }
            18 => {
                current_block_39 = 7655998149493490107;
            }
            17 => {
                current_block_39 = 11610033353793802299;
            }
            16 => {
                current_block_39 = 5222203566858599185;
            }
            15 => {
                current_block_39 = 10499337961478622544;
            }
            14 => {
                current_block_39 = 14160224858983380336;
            }
            13 => {
                current_block_39 = 13323746484755204236;
            }
            12 => {
                current_block_39 = 16693832251570692409;
            }
            11 => {
                current_block_39 = 5847001814070732958;
            }
            10 => {
                current_block_39 = 16151286906503008035;
            }
            9 => {
                current_block_39 = 10200855469057411650;
            }
            8 => {
                current_block_39 = 9144189022125703358;
            }
            7 => {
                current_block_39 = 18280896646403916085;
            }
            6 => {
                current_block_39 = 11358724623442187095;
            }
            5 => {
                current_block_39 = 16753134882876430486;
            }
            4 => {
                current_block_39 = 8040436755072297083;
            }
            3 => {
                current_block_39 = 8934142917355348825;
            }
            2 => {
                current_block_39 = 4535140922845407500;
            }
            1 => {
                current_block_39 = 16721024496556810190;
            }
            _ => {
                current_block_39 = 4090602189656566074;
            }
        }
        loop {
            match current_block_39 {
                4090602189656566074 => {
                    break 's_192;
                }
                1146658625155211681 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh0 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh0 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 7655998149493490107;
                }
                7655998149493490107 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh1 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh1 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 11610033353793802299;
                }
                11610033353793802299 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh2 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh2 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 5222203566858599185;
                }
                5222203566858599185 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh3 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh3 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 10499337961478622544;
                }
                10499337961478622544 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh4 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh4 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 14160224858983380336;
                }
                14160224858983380336 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh5 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh5 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 13323746484755204236;
                }
                13323746484755204236 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh6 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh6 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 16693832251570692409;
                }
                16693832251570692409 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh7 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh7 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 5847001814070732958;
                }
                5847001814070732958 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh8 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh8 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 16151286906503008035;
                }
                16151286906503008035 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh9 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh9 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 10200855469057411650;
                }
                10200855469057411650 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh10 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh10 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 9144189022125703358;
                }
                9144189022125703358 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh11 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh11 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 18280896646403916085;
                }
                18280896646403916085 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh12 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh12 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 11358724623442187095;
                }
                11358724623442187095 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh13 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh13 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 16753134882876430486;
                }
                16753134882876430486 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh14 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh14 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 8040436755072297083;
                }
                8040436755072297083 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh15 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh15 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 8934142917355348825;
                }
                8934142917355348825 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh16 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh16 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 4535140922845407500;
                }
                4535140922845407500 => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh17 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh17 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    current_block_39 = 16721024496556810190;
                }
                _ => {
                    temp = temp.wrapping_mul(10 as libc::c_int as libc::c_ulonglong);
                    let fresh18 = str;
                    str = str.offset(1);
                    temp = temp
                        .wrapping_add(
                            (*fresh18 as libc::c_int & 15 as libc::c_int)
                                as libc::c_ulonglong,
                        );
                    if !(temp == 0) {
                        *((*libzahl_tmp_str_num.as_mut_ptr()).chars)
                            .offset(0 as libc::c_int as isize) = temp as zahl_char_t;
                        temp >>= 32 as libc::c_int;
                        *((*libzahl_tmp_str_num.as_mut_ptr()).chars)
                            .offset(1 as libc::c_int as isize) = temp as zahl_char_t;
                        (*libzahl_tmp_str_num.as_mut_ptr())
                            .used = (1 as libc::c_int + (temp != 0) as libc::c_int)
                            as size_t;
                        zadd(a, a, libzahl_tmp_str_num.as_mut_ptr());
                    }
                    if !(*str != 0) {
                        current_block_39 = 4090602189656566074;
                        continue;
                    }
                    zmul(a, a, libzahl_const_1e19.as_mut_ptr());
                    temp = 0 as libc::c_int as libc::c_ulonglong;
                    current_block_39 = 1146658625155211681;
                }
            }
        }
    }
    if neg != 0 {
        (*a).sign = -zsignum(a);
    }
    return 0 as libc::c_int;
}
