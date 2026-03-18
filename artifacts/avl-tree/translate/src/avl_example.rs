use translate::*;
use std::env;
use std::any::Any;
pub fn main() {
    let avlt: Option<Box<AvlTree>> = avl_create(
        Some(Box::new(|a: &dyn Any, b: &dyn Any| -> i32 {
            let a = a.downcast_ref::<Mydata>().unwrap();
            let b = b.downcast_ref::<Mydata>().unwrap();
            compare_func(Some(a), Some(b))
        })),
        Some(Box::new(|a: &dyn Any| {
            let data = Box::new(a.downcast_ref::<Mydata>().unwrap().clone());
            destroy_func(Some(Box::new(*data)))
        })),
    );

    if avlt.is_none() {
        eprintln!("create AVL tree failed");
        return;
    }

    let mut avlt = avlt.unwrap();
    let a = ['R', 'E', 'D', 'S', 'O', 'X', 'C', 'U', 'B', 'T'];
    
    for &c in &a {
        let data = match makedata(c as i32) {
            Some(d) => Box::new(d) as Box<dyn Any>,
            None => {
                eprintln!("insert {}: out of memory", c as char);
                break;
            }
        };

        if avl_insert(&mut avlt, data).is_none() {
            eprintln!("insert {}: out of memory", c as char);
            break;
        }

        println!("insert {}", c as char);
        avl_print(&avlt, &|opt: Option<&dyn Any>| {
            if let Some(d) = opt {
                let d = d.downcast_ref::<Mydata>().unwrap();
                print_char_func(Some(d));
            }
        });
        println!();
    }

    let query = Mydata { key: 'O' as i32 };
    println!("delete {}", query.key as u8 as char);
    
    // Fix: Store the node data before deletion
    if let Some(node) = avl_find(&avlt, &query) {
        let node_data = node.data.as_ref().unwrap().downcast_ref::<Mydata>().unwrap().clone();
        let mut node_clone = AvlNode {
            left: node.left.as_ref().map(|_| panic!("Cannot clone Box<AvlNode>")),
            right: node.right.as_ref().map(|_| panic!("Cannot clone Box<AvlNode>")),
            parent: node.parent.as_ref().map(|_| panic!("Cannot clone Box<AvlNode>")),
            bf: node.bf,
            data: Some(Box::new(node_data)),
        };
        avl_delete(&mut avlt, &mut node_clone, 0);
    }
    
    avl_print(&avlt, &|opt: Option<&dyn Any>| {
        if let Some(d) = opt {
            let d = d.downcast_ref::<Mydata>().unwrap();
            print_char_func(Some(d));
        }
    });
    
    // Fix: Properly handle the min node deletion
    while let Some(node) = avlt.min.take() {
        print!("\ndelete ");
        let node_data = node.data.as_ref().unwrap().downcast_ref::<Mydata>().unwrap().clone();
        print_char_func(Some(&node_data));
        let mut node_clone = AvlNode {
            left: None,
            right: None,
            parent: None,
            bf: node.bf,
            data: Some(Box::new(node_data)),
        };
        avl_delete(&mut avlt, &mut node_clone, 0);
        avl_print(&avlt, &|opt: Option<&dyn Any>| {
            if let Some(d) = opt {
                let d = d.downcast_ref::<Mydata>().unwrap();
                print_char_func(Some(d));
            }
        });
    }

    avl_destroy(avlt);
}
