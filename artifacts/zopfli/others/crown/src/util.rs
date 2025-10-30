use ::libc;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor21 { dummy: () }
#[no_mangle]
pub unsafe extern "C" fn ZopfliInitOptions(mut options: *mut crate::src::blocksplitter::ZopfliOptions) {
    (*options).verbose = 0 as libc::c_int;
    (*options).verbose_more = 0 as libc::c_int;
    (*options).numiterations = 15 as libc::c_int;
    (*options).blocksplitting = 1 as libc::c_int;
    (*options).blocksplittinglast = 0 as libc::c_int;
    (*options).blocksplittingmax = 15 as libc::c_int;
}
