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
    let mut node = chain;
    let mut node_idx = 0;
    let mut val;

    // Traverse the chain and populate counts
    while let Some(current_node) = node {
        end -= 1;
        counts[end] = current_node.count;
        node = current_node.tail.as_deref();
    }

    val = counts[15];
    while ptr >= end {
        while val > counts[ptr - 1] {
            bitlengths[leaves[(val - 1) as usize].count as usize] = value;
            val -= 1;
        }

        ptr -= 1;
        value += 1;
    }
}

pub fn BoundaryPMFinal(
    lists: &mut [&mut [Option<Box<Node>>; 2]],
    leaves: &[Node],
    numsymbols: i32,
    pool: &mut NodePool,
    index: usize,
) {
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
        lists[index][1].as_mut().unwrap().tail = lists[index - 1][1].clone();
    }
}
pub fn BoundaryPM(
    lists: &mut [Option<Box<Node>>; 2],
    leaves: &[Node],
    numsymbols: i32,
    pool: &mut NodePool,
    index: i32,
) {
    let lastcount = lists[1].as_ref().unwrap().count;
    if (index == 0) && (lastcount >= numsymbols) {
        return;
    }

    let newchain_idx = pool.next.take();
    let oldchain_idx = lists[1].take();
    
    lists[0] = oldchain_idx;
    lists[1] = newchain_idx;

    if index == 0 {
        let newchain = lists[1].as_mut().unwrap();
        InitNode(
            leaves[lastcount as usize].weight,
            lastcount + 1,
            Option::None,
            newchain,
        );
    } else {
        let sum = lists[0].as_ref().unwrap().weight + lists[1].as_ref().unwrap().weight;
        if (lastcount < numsymbols) && (sum > leaves[lastcount as usize].weight) {
            let (left, right) = lists.split_at_mut(1);
            let newchain = right[0].as_mut().unwrap();
            let oldchain_tail = left[0].as_ref().unwrap().tail.clone();
            InitNode(
                leaves[lastcount as usize].weight,
                lastcount + 1,
                oldchain_tail,
                newchain,
            );
        } else {
            let (left, right) = lists.split_at_mut(1);
            let newchain = right[0].as_mut().unwrap();
            let lists_index_1 = left[1].clone();
            InitNode(sum, lastcount, lists_index_1, newchain);
            
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
    let mut numBoundaryPMRuns;
    let mut nodes_idx = 0;
    let mut lists_idx = 0;

    // Initialize bitlengths to 0
    for i in 0..n as usize {
        bitlengths[i] = 0;
    }

    // Count non-zero frequencies and create leaves
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

    // Check various conditions
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

    // Process weights
    for i in 0..numsymbols as usize {
        if leaves[i].weight >= ((1 as usize) << ((std::mem::size_of::<usize>() * 8) - 9)) {
            return 1;
        }
        leaves[i].weight = (leaves[i].weight << 9) | (leaves[i].count as usize);
    }

    // Sort leaves
    leaves.sort_by(LeafComparator);

    // Restore weights
    for i in 0..numsymbols as usize {
        leaves[i].weight >>= 9;
    }

    let maxbits = if (numsymbols - 1) < maxbits {
        numsymbols - 1
    } else {
        maxbits
    };

    // Initialize nodes and lists
    let mut nodes: Vec<Node> = Vec::with_capacity((maxbits * 2 * numsymbols) as usize);
    pool.next = Some(Box::new(nodes[nodes_idx].clone()));
    let mut lists: Vec<[Option<Box<Node>>; 2]> = Vec::with_capacity(maxbits as usize);

    InitLists(
        &mut pool,
        &leaves,
        maxbits as usize,
        &mut lists.iter_mut().collect::<Vec<_>>(),
    );

    numBoundaryPMRuns = (2 * numsymbols) - 4;
    for i in 0..(numBoundaryPMRuns - 1) {
        BoundaryPM(
            &mut lists[lists_idx as usize],
            &leaves,
            numsymbols,
            &mut pool,
            maxbits - 1,
        );
    }

    BoundaryPMFinal(
        &mut lists.iter_mut().collect::<Vec<_>>(),
        &leaves,
        numsymbols,
        &mut pool,
        (maxbits - 1) as usize,
    );

    ExtractBitLengths(
        lists[(maxbits - 1) as usize + lists_idx as usize][1].as_ref().map(|v| &**v),
        &leaves,
        bitlengths,
    );

    0
}
