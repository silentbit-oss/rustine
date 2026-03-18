/*
 * AVL Tree Example Program
 * Translated from C implementation by xieqing
 */

use avl_tree::{avl_create, avl_delete, avl_destroy, avl_find, avl_insert, avl_print, makedata, MyData};

fn main() {
    // Create a AVL tree
    let mut avlt = avl_create::<MyData>();

    // Insert items
    let a = ['R', 'E', 'D', 'S', 'O', 'X', 'C', 'U', 'B', 'T'];

    for &ch in &a {
        let data = makedata(ch as i32);
        match avl_insert(&mut avlt, data) {
            Some(_) => {
                print!("insert {}", ch);
                avl_print(&avlt);
                println!();
            }
            None => {
                eprintln!("insert {}: out of memory", ch);
                break;
            }
        }
    }

    // Delete item
    let query = MyData { key: 'O' as i32 };
    print!("delete {}", query.key as u8 as char);
    if avl_find(&avlt, &query).is_some() {
        avl_delete(&mut avlt, &query, false);
    }
    avl_print(&avlt);

    avl_destroy(avlt);
}
