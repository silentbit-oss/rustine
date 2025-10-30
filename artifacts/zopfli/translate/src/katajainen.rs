use crate::*;
use std::cmp::Ordering;


fn LeafComparator(a: &Node, b: &Node) -> Ordering {
    a.weight.cmp(&b.weight)
}
fn InitNode(weight: usize, count: i32, tail: Option<Box<Node>>, node: &mut Node) {
    node.weight = weight;
    node.count = count;
    node.tail = tail;
}
pub fn InitLists(pool: &mut NodePool, leaves: &[Node], maxbits: usize, lists: &mut [&mut [Option<Box<Node>>; 2]]) {
    // Take ownership of the next two nodes from the pool
    let mut node0 = pool.next.take().unwrap();
    let mut node1 = pool.next.take().unwrap();

    // Initialize the nodes
    InitNode(leaves[0].weight, 1, None, &mut node0);
    InitNode(leaves[1].weight, 2, None, &mut node1);

    // Populate the lists
    for i in 0..maxbits {
        lists[i][0] = Some(node0.clone());
        lists[i][1] = Some(node1.clone());
    }
}
pub fn ExtractBitLengths(chain: Option<Box<Node>>, leaves: &[Node], bitlengths: &mut [u32]) {
    let mut counts = [0; 16];
    let mut end = 16;
    let mut ptr = 15;
    let mut value = 1;
    let mut node_idx = chain;
    let mut val;

    // First loop: populate counts array
    while let Some(node) = node_idx {
        end -= 1;
        counts[end] = node.count;
        node_idx = node.tail;
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
pub fn BoundaryPM(
    lists: &mut [Option<Box<Node>>; 2],
    leaves: &[Node],
    numsymbols: i32,
    pool: &mut NodePool,
    index: i32,
) {
    let lastcount = lists[1].as_ref().map_or(0, |node| node.count);
    
    if index == 0 && lastcount >= numsymbols {
        return;
    }

    let newchain_idx = pool.next.take();
    let oldchain_idx = lists[1].take();

    lists[0] = oldchain_idx.clone();
    lists[1] = newchain_idx;

    if index == 0 {
        let mut newchain = lists[1].as_mut().unwrap();
        InitNode(
            leaves[lastcount as usize].weight,
            lastcount + 1,
            Option::None,
            &mut newchain,
        );
    } else {
        let sum = lists[0].as_ref().map_or(0, |node| node.weight)
            + lists[1].as_ref().map_or(0, |node| node.weight);

        if lastcount < numsymbols && sum > leaves[lastcount as usize].weight {
            let (left, right) = lists.split_at_mut(1);
            let mut newchain = right[0].as_mut().unwrap();
            let tail = left[0].take();
            InitNode(
                leaves[lastcount as usize].weight,
                lastcount + 1,
                tail,
                &mut newchain,
            );
        } else {
            let (left, right) = lists.split_at_mut(1);
            let tail = right[0].take();
            let mut newchain = right[0].as_mut().unwrap();
            InitNode(sum, lastcount, tail, &mut newchain);

            BoundaryPM(lists, leaves, numsymbols, pool, index - 1);
            BoundaryPM(lists, leaves, numsymbols, pool, index - 1);
        }
    }
}
pub fn BoundaryPMFinal(lists: &mut [Option<Box<Node>>; 2], leaves: &[Node], numsymbols: i32, pool: &mut NodePool, index: usize) {
    let lastcount = lists[1].as_ref().and_then(|x| Some(x.as_ref())).unwrap().count;
    let sum = lists[0].as_ref().and_then(|x| Some(x.as_ref())).unwrap().weight + 
              lists[1].as_ref().and_then(|x| Some(x.as_ref())).unwrap().weight;
    
    if (lastcount < numsymbols) && (sum > leaves[lastcount as usize].weight) {
        let newchain = pool.next.take();
        let oldchain = lists[1].as_mut().and_then(|x| Some(x.as_mut())).unwrap().tail.take();
        *lists[1].as_mut().unwrap() = newchain.expect("Failed to get new node from pool");
        if let Some(ref mut node) = lists[1].as_mut().and_then(|x| Some(x.as_mut())) {
            node.count = lastcount + 1;
            node.tail = oldchain;
        }
    } else {
        lists[1].as_mut().and_then(|x| Some(x.as_mut())).unwrap().tail = 
            lists[1].as_ref().and_then(|x| Some(x.as_ref())).map(|x| Box::new((*x).clone()));
    }
}
pub fn ZopfliLengthLimitedCodeLengths(
    frequencies: &[usize],
    n: usize,
    maxbits: i32,
    bitlengths: &mut [u32],
) -> i32 {
    let mut pool = NodePool { next: Option::None };
    let mut numsymbols = 0;
    let mut numBoundaryPMRuns;
    let mut nodes_idx = 0;
    let mut lists_idx = 0;

    // Initialize bitlengths to 0
    for b in bitlengths.iter_mut().take(n) {
        *b = 0;
    }

    // Collect non-zero frequencies into leaves
    let mut leaves: Vec<Node> = frequencies
        .iter()
        .enumerate()
        .filter_map(|(i, &freq)| {
            if freq != 0 {
                numsymbols += 1;
                Some(Node {
                    weight: freq,
                    count: i as i32,
                    tail: Option::None,
                })
            } else {
                Option::None
            }
        })
        .collect();

    // Early returns for edge cases
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

    // Check for weight overflow and shift weights
    for leaf in &mut leaves {
        if leaf.weight >= (1 << (usize::BITS - 9) as usize) {
            return 1;
        }
        leaf.weight = (leaf.weight << 9) | (leaf.count as usize);
    }

    // Sort leaves
    leaves.sort_by(|a, b| a.weight.cmp(&b.weight));

    // Restore weights
    for leaf in &mut leaves {
        leaf.weight >>= 9;
    }

    let maxbits = if (numsymbols - 1) < maxbits {
        (numsymbols - 1) as i32
    } else {
        maxbits
    };

    // Initialize nodes and lists
    let mut nodes: Vec<Node> = Vec::with_capacity((maxbits * 2 * numsymbols) as usize);
    pool.next = Some(Box::new(nodes[0].clone()));
    
    let mut lists: Vec<[Option<Box<Node>>; 2]> = Vec::with_capacity(maxbits as usize);
    let mut lists_slice: Vec<&mut [Option<Box<Node>>; 2]> = Vec::with_capacity(maxbits as usize);
    for arr in &mut lists {
        lists_slice.push(arr);
    }
    InitLists(&mut pool, &leaves, maxbits as usize, &mut lists_slice);

    numBoundaryPMRuns = (2 * numsymbols) - 4;
    for _ in 0..(numBoundaryPMRuns - 1) {
        BoundaryPM(&mut lists[(maxbits - 1) as usize], &leaves, numsymbols, &mut pool, maxbits - 1);
    }

    BoundaryPMFinal(&mut lists[(maxbits - 1) as usize], &leaves, numsymbols, &mut pool, (maxbits - 1) as usize);
    ExtractBitLengths(lists[(maxbits - 1) as usize][1].clone(), &leaves, bitlengths);

    0
}
