use ::libc;
extern "C" {
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    fn ti_buffer_new(size: libc::c_int) -> *mut ti_buffer;
    fn ti_buffer_free(buffer: *mut ti_buffer);
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ti_buffer {
    pub size: libc::c_int,
    pub pushes: libc::c_int,
    pub index: libc::c_int,
    pub sum: libc::c_double,
    pub vals: [libc::c_double; 1],
}
#[no_mangle]
pub unsafe extern "C" fn ti_mass_start(
    mut options: *const libc::c_double,
) -> libc::c_int {
    let mut sum_p: libc::c_int = *options.offset(0 as libc::c_int as isize)
        as libc::c_int - 1 as libc::c_int;
    return 16 as libc::c_int + sum_p;
}
#[no_mangle]
pub unsafe extern "C" fn ti_mass(
    mut size: libc::c_int,
    mut inputs: *const *const libc::c_double,
    mut options: *const libc::c_double,
    mut outputs: *const *mut libc::c_double,
) -> libc::c_int {
    let mut high: *const libc::c_double = *inputs.offset(0 as libc::c_int as isize);
    let mut low: *const libc::c_double = *inputs.offset(1 as libc::c_int as isize);
    let period: libc::c_int = *options.offset(0 as libc::c_int as isize) as libc::c_int;
    let mut output: *mut libc::c_double = *outputs.offset(0 as libc::c_int as isize);
    if period < 1 as libc::c_int {
        return 1 as libc::c_int;
    }
    if size <= ti_mass_start(options) {
        return 0 as libc::c_int;
    }
    let per: libc::c_double = 2 as libc::c_int as libc::c_double
        / (9.0f64 + 1 as libc::c_int as libc::c_double);
    let per1: libc::c_double = 1.0f64 - per;
    let mut ema: libc::c_double = *high.offset(0 as libc::c_int as isize)
        - *low.offset(0 as libc::c_int as isize);
    let mut ema2: libc::c_double = ema;
    let mut sum: *mut ti_buffer = ti_buffer_new(period);
    let mut i: libc::c_int = 0;
    i = 0 as libc::c_int;
    while i < size {
        let mut hl: libc::c_double = *high.offset(i as isize) - *low.offset(i as isize);
        ema = ema * per1 + hl * per;
        if i == 8 as libc::c_int {
            ema2 = ema;
        }
        if i >= 8 as libc::c_int {
            ema2 = ema2 * per1 + ema * per;
            if i >= 16 as libc::c_int {
                if (*sum).pushes >= (*sum).size {
                    (*sum).sum
                        -= *((*sum).vals).as_mut_ptr().offset((*sum).index as isize);
                }
                (*sum).sum += ema / ema2;
                *((*sum).vals).as_mut_ptr().offset((*sum).index as isize) = ema / ema2;
                (*sum).pushes += 1 as libc::c_int;
                (*sum).index = (*sum).index + 1 as libc::c_int;
                if (*sum).index >= (*sum).size {
                    (*sum).index = 0 as libc::c_int;
                }
                if i >= 16 as libc::c_int + period - 1 as libc::c_int {
                    let fresh0 = output;
                    output = output.offset(1);
                    *fresh0 = (*sum).sum;
                }
            }
        }
        i += 1;
        i;
    }
    ti_buffer_free(sum);
    if output.offset_from(*outputs.offset(0 as libc::c_int as isize)) as libc::c_long
        == (size - ti_mass_start(options)) as libc::c_long
    {} else {
        __assert_fail(
            b"output - outputs[0] == size - ti_mass_start(options)\0" as *const u8
                as *const libc::c_char,
            b"indicators/mass.c\0" as *const u8 as *const libc::c_char,
            80 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 73],
                &[libc::c_char; 73],
            >(
                b"int ti_mass(int, const double *const *, const double *, double *const *)\0",
            ))
                .as_ptr(),
        );
    };
    return 0 as libc::c_int;
}
