use crate::*;

pub fn ZopfliInitOptions(options: &mut ZopfliOptions) {
    options.verbose = 0;
    options.verbose_more = 0;
    options.numiterations = 15;
    options.blocksplitting = 1;
    options.blocksplittinglast = 0;
    options.blocksplittingmax = 15;
}
