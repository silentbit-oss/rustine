use crate::*;

pub type PyCFunction = Option<Box<dyn Fn(Option<Box<PyObject>>, Option<Box<PyObject>>) -> Option<Box<PyObject>>>>;

