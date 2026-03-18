use std::cmp::Ordering;
use std::fmt::{self, Display};

/// Traversal order, mirroring the C `enum avltraversal`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Traversal {
    PreOrder,
    InOrder,
    PostOrder,
}

struct Node<T> {
    value: T,
    height: i32,
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    fn new(value: T) -> Box<Node<T>> {
        Box::new(Node {
            value,
            height: 1,
            left: None,
            right: None,
        })
    }

    fn update_height(&mut self) {
        self.height = 1 + height(&self.left).max(height(&self.right));
    }

    fn balance_factor(&self) -> i32 {
        height(&self.left) - height(&self.right)
    }
}

/// Height of a possibly-empty subtree (an empty subtree has height 0).
fn height<T>(link: &Option<Box<Node<T>>>) -> i32 {
    link.as_ref().map_or(0, |n| n.height)
}

// --- rotations: take a root, hand back the new root -------------------------

fn rotate_right<T>(mut root: Box<Node<T>>) -> Box<Node<T>> {
    // `root` must have a left child for this to be called.
    let mut pivot = root.left.take().expect("rotate_right needs a left child");
    root.left = pivot.right.take();
    root.update_height();
    pivot.right = Some(root);
    pivot.update_height();
    pivot
}

fn rotate_left<T>(mut root: Box<Node<T>>) -> Box<Node<T>> {
    let mut pivot = root.right.take().expect("rotate_left needs a right child");
    root.right = pivot.left.take();
    root.update_height();
    pivot.left = Some(root);
    pivot.update_height();
    pivot
}

/// Recompute height and apply at most one rotation to restore the AVL invariant.
fn rebalance<T>(mut node: Box<Node<T>>) -> Box<Node<T>> {
    node.update_height();
    match node.balance_factor() {
        // Left heavy.
        bf if bf > 1 => {
            // Left-Right case: turn it into a Left-Left case first.
            if node.left.as_ref().unwrap().balance_factor() < 0 {
                let left = node.left.take().unwrap();
                node.left = Some(rotate_left(left));
            }
            rotate_right(node)
        }
        // Right heavy.
        bf if bf < -1 => {
            // Right-Left case: turn it into a Right-Right case first.
            if node.right.as_ref().unwrap().balance_factor() > 0 {
                let right = node.right.take().unwrap();
                node.right = Some(rotate_right(right));
            }
            rotate_left(node)
        }
        _ => node,
    }
}

/// Detach the minimum node of a (non-empty) subtree.
/// Returns `(min_node, remaining_subtree)`, rebalancing the remainder.
fn extract_min<T>(mut node: Box<Node<T>>) -> (Box<Node<T>>, Option<Box<Node<T>>>) {
    match node.left.take() {
        // No smaller element: this node is the minimum. Its right child (if any)
        // takes its place.
        None => {
            let right = node.right.take();
            (node, right)
        }
        Some(left) => {
            let (min_node, new_left) = extract_min(left);
            node.left = new_left;
            (min_node, Some(rebalance(node)))
        }
    }
}

/// An AVL (height-balanced) binary search tree of unique `T` values.
pub struct AvlTree<T> {
    root: Option<Box<Node<T>>>,
    len: usize,
}

impl<T: Ord> AvlTree<T> {
    /// Create an empty tree. (`avl_create`)
    pub fn new() -> Self {
        AvlTree { root: None, len: 0 }
    }

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn is_empty(&self) -> bool {
        self.len == 0
    }

    /// Insert `value`. Returns `true` if it was newly inserted, `false` if an
    /// equal value already existed (in which case the tree is unchanged).
    /// (`avl_insert`)
    pub fn insert(&mut self, value: T) -> bool {
        fn go<T: Ord>(link: Option<Box<Node<T>>>, value: T) -> (Box<Node<T>>, bool) {
            match link {
                None => (Node::new(value), true),
                Some(mut node) => {
                    let inserted = match value.cmp(&node.value) {
                        Ordering::Less => {
                            let (child, ins) = go(node.left.take(), value);
                            node.left = Some(child);
                            ins
                        }
                        Ordering::Greater => {
                            let (child, ins) = go(node.right.take(), value);
                            node.right = Some(child);
                            ins
                        }
                        Ordering::Equal => false, // duplicate: leave as-is
                    };
                    if inserted {
                        (rebalance(node), true)
                    } else {
                        (node, false)
                    }
                }
            }
        }

        let (new_root, inserted) = go(self.root.take(), value);
        self.root = Some(new_root);
        if inserted {
            self.len += 1;
        }
        inserted
    }

    /// Remove the value equal to `value`. Returns `true` if something was removed.
    /// (`avl_delete` + `avl_find`)
    pub fn remove(&mut self, value: &T) -> bool {
        fn go<T: Ord>(
            link: Option<Box<Node<T>>>,
            value: &T,
        ) -> (Option<Box<Node<T>>>, bool) {
            let mut node = match link {
                None => return (None, false),
                Some(node) => node,
            };
            let removed = match value.cmp(&node.value) {
                Ordering::Less => {
                    let (child, r) = go(node.left.take(), value);
                    node.left = child;
                    r
                }
                Ordering::Greater => {
                    let (child, r) = go(node.right.take(), value);
                    node.right = child;
                    r
                }
                Ordering::Equal => {
                    match (node.left.take(), node.right.take()) {
                        // 0 or 1 child: splice the child in directly.
                        (None, None) => return (None, true),
                        (Some(left), None) => return (Some(left), true),
                        (None, Some(right)) => return (Some(right), true),
                        // 2 children: replace value with the in-order successor
                        // (minimum of the right subtree), then drop that node.
                        (Some(left), Some(right)) => {
                            let (successor, new_right) = extract_min(right);
                            node.value = successor.value; // moves the value out of the box
                            node.left = Some(left);
                            node.right = new_right;
                            true
                        }
                    }
                }
            };
            (Some(rebalance(node)), removed)
        }

        let (new_root, removed) = go(self.root.take(), value);
        self.root = new_root;
        if removed {
            self.len -= 1;
        }
        removed
    }

    /// Return a reference to the stored value equal to `value`, if present.
    /// (`avl_find`)
    pub fn get(&self, value: &T) -> Option<&T> {
        let mut cur = self.root.as_deref();
        while let Some(node) = cur {
            cur = match value.cmp(&node.value) {
                Ordering::Less => node.left.as_deref(),
                Ordering::Greater => node.right.as_deref(),
                Ordering::Equal => return Some(&node.value),
            };
        }
        None
    }

    pub fn contains(&self, value: &T) -> bool {
        self.get(value).is_some()
    }

    /// Smallest value in the tree, if any. (`AVL_MINIMAL`, as a peek.)
    pub fn min(&self) -> Option<&T> {
        let mut node = self.root.as_deref()?;
        while let Some(left) = node.left.as_deref() {
            node = left;
        }
        Some(&node.value)
    }

    /// Remove and return the smallest value. (the `AVL_MIN` delete loop)
    pub fn pop_min(&mut self) -> Option<T> {
        let (successor, new_root) = extract_min(self.root.take()?);
        self.root = new_root;
        self.len -= 1;
        Some(successor.value)
    }

    /// In-order successor: the least stored value strictly greater than `value`.
    /// Works whether or not `value` itself is present. (`avl_successor`)
    pub fn successor(&self, value: &T) -> Option<&T> {
        let mut best: Option<&T> = None;
        let mut cur = self.root.as_deref();
        while let Some(node) = cur {
            if node.value > *value {
                best = Some(&node.value); // candidate; look for a smaller one on the left
                cur = node.left.as_deref();
            } else {
                cur = node.right.as_deref();
            }
        }
        best
    }

    /// Height of the tree (an empty tree has height 0). (`avl_check_height` helper)
    pub fn height(&self) -> usize {
        height(&self.root).max(0) as usize
    }

    /// Visit every value with `f` in the requested order. (`avl_apply`)
    pub fn traverse<F: FnMut(&T)>(&self, order: Traversal, mut f: F) {
        fn go<T, F: FnMut(&T)>(link: &Option<Box<Node<T>>>, order: Traversal, f: &mut F) {
            if let Some(node) = link {
                match order {
                    Traversal::PreOrder => {
                        f(&node.value);
                        go(&node.left, order, f);
                        go(&node.right, order, f);
                    }
                    Traversal::InOrder => {
                        go(&node.left, order, f);
                        f(&node.value);
                        go(&node.right, order, f);
                    }
                    Traversal::PostOrder => {
                        go(&node.left, order, f);
                        go(&node.right, order, f);
                        f(&node.value);
                    }
                }
            }
        }
        go(&self.root, order, &mut f);
    }

    /// In-order iterator over `&T`. This is the idiomatic replacement for the
    /// most common `avl_apply(INORDER, ...)` use, and lets you use the tree with
    /// `for`, `.collect()`, `.map()`, etc.
    pub fn iter(&self) -> Iter<'_, T> {
        Iter {
            stack: Vec::new(),
            current: self.root.as_deref(),
        }
    }

    /// Verify BST ordering, the AVL balance condition, and cached heights.
    /// (`avl_check_order` + `avl_check_height`)
    pub fn check_invariants(&self) -> bool {
        fn check<T: Ord>(
            link: &Option<Box<Node<T>>>,
            lower: Option<&T>,
            upper: Option<&T>,
        ) -> Option<i32> {
            match link {
                None => Some(0),
                Some(node) => {
                    if lower.map_or(false, |lo| &node.value <= lo) {
                        return None;
                    }
                    if upper.map_or(false, |hi| &node.value >= hi) {
                        return None;
                    }
                    let lh = check(&node.left, lower, Some(&node.value))?;
                    let rh = check(&node.right, Some(&node.value), upper)?;
                    if (lh - rh).abs() > 1 {
                        return None;
                    }
                    let h = 1 + lh.max(rh);
                    if h != node.height {
                        return None;
                    }
                    Some(h)
                }
            }
        }
        check(&self.root, None, None).is_some()
    }
}

impl<T: Ord> Default for AvlTree<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T: Ord> FromIterator<T> for AvlTree<T> {
    fn from_iter<I: IntoIterator<Item = T>>(iter: I) -> Self {
        let mut tree = AvlTree::new();
        for value in iter {
            tree.insert(value);
        }
        tree
    }
}

/// Stack-based in-order iterator. Yields values in ascending order.
pub struct Iter<'a, T> {
    stack: Vec<&'a Node<T>>,
    current: Option<&'a Node<T>>,
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<&'a T> {
        while let Some(node) = self.current {
            self.stack.push(node);
            self.current = node.left.as_deref();
        }
        let node = self.stack.pop()?;
        self.current = node.right.as_deref();
        Some(&node.value)
    }
}

impl<'a, T: Ord> IntoIterator for &'a AvlTree<T> {
    type Item = &'a T;
    type IntoIter = Iter<'a, T>;
    fn into_iter(self) -> Iter<'a, T> {
        self.iter()
    }
}

/// Pretty 90°-rotated tree print (root at left, right subtree above).
/// (`avl_print`)
impl<T: Display> AvlTree<T> {
    pub fn pretty(&self) -> String {
        fn go<T: Display>(link: &Option<Box<Node<T>>>, depth: usize, out: &mut String) {
            if let Some(node) = link {
                go(&node.right, depth + 1, out);
                out.push_str(&"    ".repeat(depth));
                out.push_str(&format!("{}\n", node.value));
                go(&node.left, depth + 1, out);
            }
        }
        let mut out = String::new();
        go(&self.root, 0, &mut out);
        out
    }
}

impl<T: Display> fmt::Display for AvlTree<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.pretty())
    }
}

fn inorder_string(tree: &AvlTree<char>) -> String {
    tree.iter().collect()
}

fn main() {
    let mut tree = AvlTree::new();

    let items = ['R', 'E', 'D', 'S', 'O', 'X', 'C', 'U', 'B', 'T'];
    for &c in &items {
        tree.insert(c);
        println!("insert {c}: {}", inorder_string(&tree));
    }

    println!("\ntree shape:\n{tree}");

    let target = 'O';
    print!("delete {target}: ");
    tree.remove(&target);
    println!("{}", inorder_string(&tree));

    // Equivalent of the `#ifdef AVL_MIN` loop: repeatedly remove the minimum.
    while let Some(c) = tree.pop_min() {
        println!("delete {c}: {}", inorder_string(&tree));
    }

    assert!(tree.is_empty());
}

// --- tests ------------------------------------------------------------------


#[cfg(test)]
mod tests {
    use super::*;
    use std::collections::BTreeSet;

    /// Character set permuted exhaustively below. 7 unique chars => 5040 orders.
    const CHARS: &str = "ABCDEFG";

    // ---- harness helpers (cf. tree_create/insert/delete/find/print/check) ---

    fn tree_create() -> AvlTree<i32> {
        AvlTree::new()
    }
    fn tree_insert(t: &mut AvlTree<i32>, key: i32) -> bool {
        t.insert(key)
    }
    fn tree_delete(t: &mut AvlTree<i32>, key: i32) -> bool {
        t.remove(&key)
    }
    fn tree_find(t: &AvlTree<i32>, key: i32) -> Option<&i32> {
        t.get(&key)
    }
    #[allow(dead_code)]
    fn tree_print(t: &AvlTree<i32>) {
        print!("{t}");
    }
    fn tree_check(t: &AvlTree<i32>) -> bool {
        t.check_invariants()
    }

    /// Read the root value directly (tests are a submodule, so private fields
    /// are reachable). Lets us assert on tree *shape*, not just contents.
    fn root_of<T: Clone>(t: &AvlTree<T>) -> Option<T> {
        t.root.as_ref().map(|n| n.value.clone())
    }

    /// Generate every permutation of `a`, invoking `f` on each. Recursive
    /// swap-based generator, the analogue of the C `permute` + `swap`.
    fn permute<F: FnMut(&[char])>(a: &mut [char], start: usize, f: &mut F) {
        if start + 1 >= a.len() {
            f(a);
            return;
        }
        for i in start..a.len() {
            a.swap(start, i);
            permute(a, start + 1, f);
            a.swap(start, i); // restore
        }
    }

    /// Small deterministic xorshift PRNG so tests need no external crate.
    fn xorshift(state: &mut u64) -> u64 {
        *state ^= *state << 13;
        *state ^= *state >> 7;
        *state ^= *state << 17;
        *state
    }

    // ---- tests --------------------------------------------------------------

    #[test]
    fn unit_test_create() {
        let t = tree_create();
        assert!(t.is_empty());
        assert_eq!(t.len(), 0);
        assert_eq!(t.height(), 0);
        assert!(t.min().is_none());
        assert!(tree_check(&t));
    }

    #[test]
    fn unit_test_find() {
        let mut t = tree_create();
        let keys = [5, 3, 8, 1, 4, 7, 9];
        for k in keys {
            tree_insert(&mut t, k);
        }
        for k in keys {
            assert_eq!(tree_find(&t, k), Some(&k));
        }
        for k in [0, 2, 6, 10, -1] {
            assert!(tree_find(&t, k).is_none());
        }
    }

    #[test]
    fn unit_test_successor() {
        let mut t = tree_create();
        for k in [50, 30, 70, 20, 40, 60, 80] {
            tree_insert(&mut t, k);
        }
        assert_eq!(t.successor(&50), Some(&60)); // present key
        assert_eq!(t.successor(&40), Some(&50));
        assert_eq!(t.successor(&20), Some(&30));
        assert_eq!(t.successor(&80), None); // largest has no successor
        assert_eq!(t.successor(&45), Some(&50)); // absent key
        assert_eq!(t.successor(&5), Some(&20)); // below the minimum

        // Walking via successor() from the minimum yields the sorted order.
        let mut seen = Vec::new();
        let mut cur = t.min().copied();
        while let Some(v) = cur {
            seen.push(v);
            cur = t.successor(&v).copied();
        }
        assert_eq!(seen, vec![20, 30, 40, 50, 60, 70, 80]);
    }

    #[test]
    fn unit_test_atomic_insertion() {
        // Each ordering forces exactly one (single or double) rotation. All four
        // must converge to the same balanced tree: root 2, height 2, {1,2,3}.
        for order in [[1, 2, 3], [3, 2, 1], [3, 1, 2], [1, 3, 2]] {
            let mut t = tree_create();
            for k in order {
                tree_insert(&mut t, k);
            }
            assert!(tree_check(&t), "invariants after inserting {order:?}");
            assert_eq!(t.height(), 2, "rotation should cap height at 2 for {order:?}");
            assert_eq!(root_of(&t), Some(2), "middle value must become root for {order:?}");
            assert_eq!(t.iter().copied().collect::<Vec<_>>(), vec![1, 2, 3]);
        }
    }

    #[test]
    fn unit_test_atomic_deletion() {
        // Build a tree where removing one node unbalances the root, fixed by a
        // single left rotation.
        let mut t = tree_create();
        for k in [2, 1, 4, 3, 5] {
            tree_insert(&mut t, k);
        }
        assert_eq!(root_of(&t), Some(2));
        assert!(tree_delete(&mut t, 1));
        assert!(tree_check(&t));
        assert_eq!(root_of(&t), Some(4), "single left rotation should lift 4 to root");
        assert_eq!(t.iter().copied().collect::<Vec<_>>(), vec![2, 3, 4, 5]);
    }

    #[test]
    fn unit_test_chain_insertion() {
        // Ascending/descending inserts make rebalancing retrace up the tree on
        // nearly every step. 15 nodes settle into a perfect height-4 tree.
        for ascending in [true, false] {
            let mut t = tree_create();
            let range: Vec<i32> = if ascending {
                (1..=15).collect()
            } else {
                (1..=15).rev().collect()
            };
            for k in range {
                tree_insert(&mut t, k);
                assert!(tree_check(&t));
            }
            assert_eq!(t.height(), 4);
            assert_eq!(root_of(&t), Some(8));
            assert_eq!(t.iter().copied().collect::<Vec<_>>(), (1..=15).collect::<Vec<_>>());
        }
    }

    #[test]
    fn unit_test_chain_deletion() {
        // Deletions can cascade through several rotations on the way to the root.
        // Delete every key (in a strided order touching all parts of the tree),
        // re-checking invariants and size after each removal.
        let n = 100;
        let mut t: AvlTree<i32> = (1..=n).collect();
        let mut model: BTreeSet<i32> = (1..=n).collect();
        assert!(tree_check(&t));

        // 37 is coprime to 100, so this visits every key exactly once.
        let order: Vec<i32> = (0..n).map(|i| (i * 37) % n + 1).collect();
        for k in order {
            assert_eq!(tree_delete(&mut t, k), model.remove(&k));
            assert!(tree_check(&t));
            assert_eq!(t.len(), model.len());
        }
        assert!(t.is_empty());
    }

    #[test]
    fn unit_test_permutation_insertion() {
        // For every insertion order of CHARS, the tree must end up valid and
        // hold exactly the sorted set.
        let mut chars: Vec<char> = CHARS.chars().collect();
        let mut sorted = chars.clone();
        sorted.sort_unstable();

        let mut error = false;
        permute(&mut chars, 0, &mut |perm| {
            let mut t = AvlTree::new();
            for &c in perm {
                t.insert(c);
            }
            if !t.check_invariants() || t.iter().copied().collect::<Vec<_>>() != sorted {
                error = true;
            }
        });
        assert!(!error);
    }

    #[test]
    fn unit_test_permutation_deletion() {
        // For every deletion order of CHARS, deleting from the full tree must
        // succeed at each step, keep invariants, and end empty.
        let mut chars: Vec<char> = CHARS.chars().collect();
        let base = chars.clone();

        let mut error = false;
        permute(&mut chars, 0, &mut |perm| {
            let mut t: AvlTree<char> = base.iter().copied().collect();
            for &c in perm {
                if !t.remove(&c) || !t.check_invariants() {
                    error = true;
                }
            }
            if !t.is_empty() {
                error = true;
            }
        });
        assert!(!error);
    }

    #[test]
    fn unit_test_random_insertion_deletion() {
        // Mixed random ops checked against a BTreeSet model, with invariants and
        // size verified after every single operation.
        let mut state: u64 = 0x1234_5678_9abc_def0;
        let mut t = tree_create();
        let mut model = BTreeSet::new();

        for _ in 0..20_000 {
            let key = (xorshift(&mut state) % 500) as i32;
            if xorshift(&mut state) & 1 == 0 {
                assert_eq!(tree_insert(&mut t, key), model.insert(key));
            } else {
                assert_eq!(tree_delete(&mut t, key), model.remove(&key));
            }
            assert!(tree_check(&t));
            assert_eq!(t.len(), model.len());
        }

        assert_eq!(
            t.iter().copied().collect::<Vec<_>>(),
            model.iter().copied().collect::<Vec<_>>()
        );

        // Height must respect the AVL bound ~ 1.44 * log2(n+2).
        let n = t.len() as f64;
        let bound = 1.4405 * (n + 2.0).log2() + 1.0;
        assert!((t.height() as f64) <= bound);
    }

    #[test]
    fn unit_test_dup() {
        let mut t = tree_create();
        assert!(tree_insert(&mut t, 42)); // first insert: true
        assert!(!tree_insert(&mut t, 42)); // duplicate: false, no change
        assert!(!tree_insert(&mut t, 42));
        assert_eq!(t.len(), 1);
        assert!(tree_check(&t));

        // Interleaved duplicates never inflate the set.
        for _ in 0..5 {
            for k in [1, 2, 3, 2, 1] {
                tree_insert(&mut t, k);
            }
        }
        assert_eq!(t.iter().copied().collect::<Vec<_>>(), vec![1, 2, 3, 42]);
        assert_eq!(t.len(), 4);
    }

    #[test]
    fn unit_test_min() {
        let mut t = tree_create();
        assert!(t.min().is_none());
        assert!(t.pop_min().is_none());

        for k in [5, 2, 8, 1, 9, 3, 7] {
            tree_insert(&mut t, k);
        }
        assert_eq!(t.min(), Some(&1));

        // pop_min drains in ascending order, staying balanced throughout.
        let mut drained = Vec::new();
        while let Some(m) = t.pop_min() {
            drained.push(m);
            assert!(tree_check(&t));
        }
        assert_eq!(drained, vec![1, 2, 3, 5, 7, 8, 9]);
        assert!(t.is_empty());
    }
}
