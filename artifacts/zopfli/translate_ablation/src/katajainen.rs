use crate::*;
use std::cmp::Ordering;
use std::usize;
// use rand::Rng;
pub fn LeafComparator(a: &Node, b: &Node) -> Ordering {
    a.weight.cmp(&b.weight)
}
pub fn InitNode(weight: usize, count: i32, tail: Option<Box<Node>>, node: &mut Node) {
    node.weight = weight;
    node.count = count;
    node.tail = tail;
}

pub fn InitLists(pool: &mut NodePool, leaves: &[Node], maxbits: usize, lists: &mut [&mut [Option<Box<Node>>; 2]]) {
    // Take ownership of the next two nodes from the pool
    let mut node0 = pool.next.take().expect("Expected node0 in pool");
    let mut node1 = pool.next.take().expect("Expected node1 in pool");

    // Initialize the nodes
    InitNode(leaves[0].weight, 1, None, &mut node0);
    InitNode(leaves[1].weight, 2, None, &mut node1);

    // Populate the lists
    for i in 0..maxbits {
        lists[i][0] = Some(node0.clone());
        lists[i][1] = Some(node1.clone());
    }
}

pub fn ExtractBitLengths(chain: Option<&Node>, leaves: &[Node], bitlengths: &mut [u32]) {
    let mut counts = [0; 16];
    let mut end = 16;
    let mut ptr = 15;
    let mut value = 1;
    let mut val;

    // Traverse the chain and populate counts array
    let mut current_node = chain;
    while let Some(node) = current_node {
        end -= 1;
        counts[end] = node.count;
        current_node = node.tail.as_deref();
    }

    val = counts[15];
    while ptr >= end {
        while val > counts[ptr - 1] {
            let leaf_index = (val - 1) as usize;
            if leaf_index < leaves.len() {
                let node_count = leaves[leaf_index].count as usize;
                if node_count < bitlengths.len() {
                    bitlengths[node_count] = value;
                }
            }
            val -= 1;
        }
        ptr -= 1;
        value += 1;
    }
}

pub fn BoundaryPMFinal(lists: &mut [&mut [Option<Box<Node>>; 2]], leaves: &[Node], numsymbols: i32, pool: &mut NodePool, index: usize) {
    let lastcount = lists[index][1].as_ref().unwrap().count;
    let sum = lists[index - 1][0].as_ref().unwrap().weight + lists[index - 1][1].as_ref().unwrap().weight;
    
    if (lastcount < numsymbols) && (sum > leaves[lastcount as usize].weight) {
        let newchain = pool.next.take();
        let oldchain = lists[index][1].as_mut().unwrap().tail.take();
        lists[index][1] = newchain;
        if let Some(ref mut node) = lists[index][1] {
            node.count = lastcount + 1;
            node.tail = oldchain;
        }
    } else {
        let prev_tail = lists[index - 1][1].take();
        lists[index][1].as_mut().unwrap().tail = prev_tail;
    }
}
pub fn BoundaryPM(lists: &mut [Option<Box<Node>>; 2], leaves: &[Node], numsymbols: i32, pool: &mut NodePool, index: i32) {
    let lastcount = lists[1].as_ref().unwrap().count;
    
    if (index == 0) && (lastcount >= numsymbols) {
        return;
    }
    
    let newchain = pool.next.take();
    let oldchain = lists[1].take();
    
    lists[0] = oldchain.clone();
    lists[1] = newchain;
    
    if index == 0 {
        InitNode(
            leaves[lastcount as usize].weight,
            lastcount + 1,
            Option::None,
            lists[1].as_mut().unwrap()
        );
    } else {
        let sum = lists[0].as_ref().unwrap().weight + lists[1].as_ref().unwrap().weight;
        
        if (lastcount < numsymbols) && (sum > leaves[lastcount as usize].weight) {
            InitNode(
                leaves[lastcount as usize].weight,
                lastcount + 1,
                lists[0].as_ref().unwrap().tail.clone(),
                lists[1].as_mut().unwrap()
            );
        } else {
            InitNode(
                sum,
                lastcount,
                lists[1].clone(),
                lists[1].as_mut().unwrap()
            );
            
            BoundaryPM(lists, leaves, numsymbols, pool, index - 1);
            BoundaryPM(lists, leaves, numsymbols, pool, index - 1);
        }
    }
}
pub fn ZopfliLengthLimitedCodeLengths(
    frequencies: &[usize],
    n: i32,
    maxbits: i32,
    bitlengths: &mut [u32],
) -> i32 {
    let mut pool = NodePool { next: None };
    let mut numsymbols = 0;
    let numBoundaryPMRuns;
    
    // Initialize bitlengths to 0
    for i in 0..n as usize {
        bitlengths[i] = 0;
    }

    // Count non-zero frequencies and collect leaves
    let mut leaves: Vec<Node> = Vec::with_capacity(n as usize);
    for i in 0..n as usize {
        if frequencies[i] != 0 {
            leaves.push(Node {
                weight: frequencies[i],
                tail: None,
                count: i as i32,
            });
            numsymbols += 1;
        }
    }

    if (1 << maxbits) < numsymbols {
        return 1;
    }
    if numsymbols == 0 {
        return 0;
    }
    if numsymbols == 1 {
        bitlengths[leaves[0].count as usize] = 1;
        return 0;
    }
    if numsymbols == 2 {
        bitlengths[leaves[0].count as usize] += 1;
        bitlengths[leaves[1].count as usize] += 1;
        return 0;
    }

    // Check weight limits and pack weight with count
    for i in 0..numsymbols {
        if leaves[i].weight >= ((1 as usize) << ((std::mem::size_of::<usize>() * 8) - 9)) {
            return 1;
        }
        leaves[i].weight = (leaves[i].weight << 9) | (leaves[i].count as usize);
    }

    // Sort leaves
    leaves.sort_by(|a, b| LeafComparator(a, b));
    
    // Unpack weights
    for i in 0..numsymbols {
        leaves[i].weight >>= 9;
    }

    let mut maxbits = maxbits;
    if (numsymbols - 1) < maxbits as usize {
        maxbits = (numsymbols - 1) as i32;
    }

    // Allocate nodes
    let nodes_count = (maxbits * 2) as usize * numsymbols;
    let mut nodes: Vec<Node> = vec![
        Node {
            weight: 0,
            tail: None,
            count: 0
        };
        nodes_count
    ];
    
    // Set up pool with nodes
    if !nodes.is_empty() {
        pool.next = Some(Box::new(nodes[0].clone()));
        let mut current = &mut pool.next;
        for i in 1..nodes_count {
            if let Some(ref mut node) = current {
                node.tail = Some(Box::new(nodes[i].clone()));
                current = &mut node.tail;
            }
        }
    }

    let mut lists: Vec<[Option<Box<Node>>; 2]> = vec![[None, None]; maxbits as usize];
    
    // Convert lists to mutable references for InitLists
    let mut lists_refs: Vec<&mut [Option<Box<Node>>; 2]> = Vec::with_capacity(maxbits as usize);
    for list in lists.iter_mut() {
        lists_refs.push(list);
    }

    InitLists(&mut pool, &leaves, maxbits as usize, &mut lists_refs);
    numBoundaryPMRuns = (2 * numsymbols) - 4;
    
    for _ in 0..(numBoundaryPMRuns - 1) {
        BoundaryPM(&mut lists[(maxbits - 1) as usize], &leaves, numsymbols as i32, &mut pool, maxbits - 1);
    }

    // Recreate lists_refs for BoundaryPMFinal
    let mut lists_refs_final: Vec<&mut [Option<Box<Node>>; 2]> = Vec::with_capacity(maxbits as usize);
    for list in lists.iter_mut() {
        lists_refs_final.push(list);
    }
    
    BoundaryPMFinal(&mut lists_refs_final, &leaves, numsymbols as i32, &mut pool, (maxbits - 1) as usize);
    
    if let Some(chain) = &lists[(maxbits - 1) as usize][1] {
        ExtractBitLengths(Some(chain), &leaves, bitlengths);
    }

    0
}
