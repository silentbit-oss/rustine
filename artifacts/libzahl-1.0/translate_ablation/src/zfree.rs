use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

lazy_static! {
    pub static ref LIBZAHL_POOL: Mutex<[Option<Box<[Option<Box<[ZahlCharT]>>]>>; (std::mem::size_of::<usize>() * 8)]> = {
        let size = std::mem::size_of::<usize>() * 8;
        let mut arr: [Option<Box<[Option<Box<[ZahlCharT]>>]>>; (std::mem::size_of::<usize>() * 8)] = 
            unsafe { std::mem::MaybeUninit::uninit().assume_init() };
        for item in &mut arr {
            *item = None;
        }
        Mutex::new(arr)
    };
}

lazy_static! {
    pub static ref LIBZAHL_POOL_ALLOC: Mutex<[usize; (std::mem::size_of::<usize>() * 8)]> =
        Mutex::new([0; (std::mem::size_of::<usize>() * 8)]);
}

lazy_static! {
    pub static ref LIBZAHL_POOL_N: [AtomicUsize; (std::mem::size_of::<usize>() * 8)] = {
        const SIZE: usize = std::mem::size_of::<usize>() * 8;
        let mut arr: [AtomicUsize; SIZE] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
        for item in &mut arr[..] {
            *item = AtomicUsize::new(0);
        }
        arr
    };
}

pub fn zfree(a: &mut z_t) {
    let a = &mut a[0];
    
    if a.chars.is_none() {
        return;
    }
    
    let mut i = 0;
    let mut x = a.alloced;
    while x > 0 {
        i += 1;
        x >>= 1;
    }
    
    let j = LIBZAHL_POOL_N[i].fetch_add(1, Ordering::SeqCst);
    let mut libzahl_pool_alloc = LIBZAHL_POOL_ALLOC.lock().unwrap();
    let mut libzahl_pool = LIBZAHL_POOL.lock().unwrap();
    
    if j == libzahl_pool_alloc[i] {
        let new_size = if j > 0 { (j * 3) / 2 } else { 128 };
        
        let new_pool = match &libzahl_pool[i] {
            Some(existing_pool) => {
                let mut new_vec = Vec::with_capacity(new_size);
                for item in existing_pool.iter() {
                    new_vec.push(item.clone());
                }
                new_vec.resize(new_size, None);
                Some(new_vec.into_boxed_slice())
            },
            None => {
                let mut new_vec = Vec::with_capacity(new_size);
                new_vec.resize(new_size, None);
                Some(new_vec.into_boxed_slice())
            }
        };
        
        if new_pool.is_none() {
            a.chars = None;
            libzahl_pool[i] = None;
            LIBZAHL_POOL_N[i].store(0, Ordering::SeqCst);
            libzahl_pool_alloc[i] = 0;
            return;
        }
        
        libzahl_pool[i] = new_pool;
        libzahl_pool_alloc[i] = new_size;
    }
    
    if let Some(pool_slice) = &mut libzahl_pool[i] {
        if j < pool_slice.len() {
            pool_slice[j] = a.chars.take();
        }
    }
}
