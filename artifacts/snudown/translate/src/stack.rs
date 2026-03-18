use crate::*;


pub struct Stack {
    pub item: Option<Vec<Option<Box<dyn std::any::Any>>>>,
    pub size: usize,
    pub asize: usize,
}

pub fn stack_grow(st: &mut Stack, new_size: usize) -> i32 {
    // Check if current allocated size is already sufficient
    if st.asize >= new_size {
        return 0;
    }

    // Create new vector with the requested size
    let mut new_items = Vec::with_capacity(new_size);
    
    // Preserve existing items by moving them rather than cloning
    if let Some(items) = st.item.take() {
        for item in items.into_iter().take(st.size) {
            new_items.push(item);
        }
    }

    // Fill remaining space with None
    while new_items.len() < new_size {
        new_items.push(None);
    }

    // Update stack properties
    st.item = Some(new_items);
    st.asize = new_size;
    
    // Adjust size if it exceeds new allocated size
    if st.size > new_size {
        st.size = new_size;
    }

    0
}
pub fn stack_push(st: &mut Stack, item: Option<Box<dyn std::any::Any>>) -> i32 {
    if stack_grow(st, st.size * 2) < 0 {
        return -1;
    }
    if let Some(ref mut items) = st.item {
        items.push(item);
        st.size += 1;
        0
    } else {
        -1
    }
}
pub fn stack_free(st: &mut Stack) {
    if st.item.is_none() {
        return;
    }
    
    // Free the Vec by replacing it with None
    st.item = None;
    st.size = 0;
    st.asize = 0;
}
pub fn stack_pop(st: &mut Stack) -> Option<Box<dyn std::any::Any>> {
    if st.size == 0 {
        return None;
    }
    st.size -= 1;
    st.item.as_mut()?.pop().flatten()
}
pub fn stack_top(st: &Stack) -> Option<&Box<dyn std::any::Any>> {
    if st.size == 0 {
        return None;
    }
    st.item.as_ref().and_then(|v| v[st.size - 1].as_ref())
}
pub fn stack_init(st: &mut Stack, initial_size: usize) -> i32 {
    st.item = None;
    st.size = 0;
    st.asize = 0;
    let size = if initial_size == 0 { 8 } else { initial_size };
    stack_grow(st, size)
}
