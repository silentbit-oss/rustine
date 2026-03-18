/*
 * AVL Tree Library
 * Translated from C implementation by xieqing
 */

pub mod avl_bf;
pub mod avl_data;
pub mod minunit;

// Re-export commonly used items
pub use avl_bf::{
    avl_apply, avl_check_height, avl_check_order, avl_create, avl_delete, avl_destroy, avl_find,
    avl_insert, avl_print, avl_successor, AvlBf, AvlNode, AvlTraversal, AvlTree,
};

#[cfg(feature = "min")]
pub use avl_bf::avl_minimal;

pub use avl_data::{makedata, MyData};
