use ::libc;
extern "C" {
    fn sqrt(_: libc::c_double) -> libc::c_double;
}
#[no_mangle]
pub unsafe extern "C" fn ti_sqrt_start(
    mut options: *const libc::c_double,
) -> libc::c_int {
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn ti_sqrt(
    mut size: libc::c_int,
    mut inputs: *const *const libc::c_double,
    mut options: *const libc::c_double,
    mut outputs: *const *mut libc::c_double,
) -> libc::c_int {
    let mut in1: *const libc::c_double = *inputs.offset(0 as libc::c_int as isize);
    let mut output: *mut libc::c_double = *outputs.offset(0 as libc::c_int as isize);
    let mut i: libc::c_int = 0;
    i = 0 as libc::c_int;
    while i < size {
        *output.offset(i as isize) = sqrt(*in1.offset(i as isize));
        i += 1;
        i;
    }
    return 0 as libc::c_int;
}
