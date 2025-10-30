use ::libc;
extern "C" {
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
}
#[no_mangle]
pub unsafe extern "C" fn ti_cmo_start(
    mut options: *const libc::c_double,
) -> libc::c_int {
    return *options.offset(0 as libc::c_int as isize) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn ti_cmo(
    mut size: libc::c_int,
    mut inputs: *const *const libc::c_double,
    mut options: *const libc::c_double,
    mut outputs: *const *mut libc::c_double,
) -> libc::c_int {
    let mut input: *const libc::c_double = *inputs.offset(0 as libc::c_int as isize);
    let mut output: *mut libc::c_double = *outputs.offset(0 as libc::c_int as isize);
    let period: libc::c_int = *options.offset(0 as libc::c_int as isize) as libc::c_int;
    if period < 1 as libc::c_int {
        return 1 as libc::c_int;
    }
    if size <= ti_cmo_start(options) {
        return 0 as libc::c_int;
    }
    let mut up_sum: libc::c_double = 0 as libc::c_int as libc::c_double;
    let mut down_sum: libc::c_double = 0 as libc::c_int as libc::c_double;
    let mut i: libc::c_int = 0;
    i = 1 as libc::c_int;
    while i <= period {
        up_sum
            += if *input.offset(i as isize)
                > *input.offset((i - 1 as libc::c_int) as isize)
            {
                *input.offset(i as isize)
                    - *input.offset((i - 1 as libc::c_int) as isize)
            } else {
                0 as libc::c_int as libc::c_double
            };
        down_sum
            += if *input.offset(i as isize)
                < *input.offset((i - 1 as libc::c_int) as isize)
            {
                *input.offset((i - 1 as libc::c_int) as isize)
                    - *input.offset(i as isize)
            } else {
                0 as libc::c_int as libc::c_double
            };
        i += 1;
        i;
    }
    let fresh0 = output;
    output = output.offset(1);
    *fresh0 = 100 as libc::c_int as libc::c_double * (up_sum - down_sum)
        / (up_sum + down_sum);
    i = period + 1 as libc::c_int;
    while i < size {
        up_sum
            -= if *input.offset((i - period) as isize)
                > *input.offset((i - period - 1 as libc::c_int) as isize)
            {
                *input.offset((i - period) as isize)
                    - *input.offset((i - period - 1 as libc::c_int) as isize)
            } else {
                0 as libc::c_int as libc::c_double
            };
        down_sum
            -= if *input.offset((i - period) as isize)
                < *input.offset((i - period - 1 as libc::c_int) as isize)
            {
                *input.offset((i - period - 1 as libc::c_int) as isize)
                    - *input.offset((i - period) as isize)
            } else {
                0 as libc::c_int as libc::c_double
            };
        up_sum
            += if *input.offset(i as isize)
                > *input.offset((i - 1 as libc::c_int) as isize)
            {
                *input.offset(i as isize)
                    - *input.offset((i - 1 as libc::c_int) as isize)
            } else {
                0 as libc::c_int as libc::c_double
            };
        down_sum
            += if *input.offset(i as isize)
                < *input.offset((i - 1 as libc::c_int) as isize)
            {
                *input.offset((i - 1 as libc::c_int) as isize)
                    - *input.offset(i as isize)
            } else {
                0 as libc::c_int as libc::c_double
            };
        let fresh1 = output;
        output = output.offset(1);
        *fresh1 = 100 as libc::c_int as libc::c_double * (up_sum - down_sum)
            / (up_sum + down_sum);
        i += 1;
        i;
    }
    if output.offset_from(*outputs.offset(0 as libc::c_int as isize)) as libc::c_long
        == (size - ti_cmo_start(options)) as libc::c_long
    {} else {
        __assert_fail(
            b"output - outputs[0] == size - ti_cmo_start(options)\0" as *const u8
                as *const libc::c_char,
            b"indicators/cmo.c\0" as *const u8 as *const libc::c_char,
            64 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 72],
                &[libc::c_char; 72],
            >(
                b"int ti_cmo(int, const double *const *, const double *, double *const *)\0",
            ))
                .as_ptr(),
        );
    };
    return 0 as libc::c_int;
}
