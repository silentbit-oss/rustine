#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "avl_bf.h"
#include "avl_data.h"
#include "minunit.h"

#define MIN INT_MIN
#define MAX INT_MAX
#define CHARS "ABCDEFGHIJ"

int mu_tests= 0, mu_fails = 0;

static avltree *tree_create();
static avlnode *tree_find(avltree *avlt, int key);
static void tree_print(avltree *avlt);
static int tree_check(avltree *avlt);
static avlnode *tree_insert(avltree *avlt, int key);
static int tree_delete(avltree *avlt, int key);

avltree *tree_create()
{
	return avl_create(compare_func, destroy_func);
}

avlnode *tree_find(avltree *avlt, int key)
{
	mydata query;
	query.key = key;
	return avl_find(avlt, &query);
}

void tree_print(avltree *avlt)
{
	avl_print(avlt, print_func);
}

int tree_check(avltree *avlt)
{
	mydata min, max;
	int rc;

	min.key = MIN;
	max.key = MAX;
	rc = 1;

	if (avl_check_order(avlt, &min, &max) != 1) {
		fprintf(stdout, "tree_check: invalid order\n");
		rc = 0;
	}

	if (avl_check_height(avlt) != 1) {
		fprintf(stdout, "tree_check: invalid height\n");
		rc = 0;
	}

	return rc;
}

avlnode *tree_insert(avltree *avlt, int key)
{
	avlnode *node;
	mydata *data;

	if (key < MIN || key > MAX) {
		fprintf(stdout, "tree_insert: invalid key %d\n", key);
		return NULL;
	}
	
	if ((data = makedata(key)) == NULL || (node = avl_insert(avlt, data)) == NULL) {
		fprintf(stdout, "tree_insert: insert %d failed\n", key);
		free(data);
		return NULL;
	}

	return node;
}

int tree_delete(avltree *avlt, int key)
{
	avlnode *node;

	if ((node = tree_find(avlt, key)) == NULL) {
		fprintf(stdout, "tree_delete: %d not found\n", key);
		return 0;
	}

	avl_delete(avlt, node, 0);

	if (tree_find(avlt, key) == node) {
		fprintf(stdout, "tree_delete: delete %d failed\n", key);
		return 0;
	}

	return 1;
}

int unit_test_create()
{
	avltree *avlt;

	if ((avlt = tree_create()) == NULL) {
		fprintf(stdout, "create AVL tree failed\n");
		return 0;
	}

	if (avlt->compare != compare_func || \
		avlt->destroy != destroy_func || \
		avlt->nil.left != AVL_NIL(avlt) || \
		avlt->nil.right != AVL_NIL(avlt) || \
		avlt->nil.parent != AVL_NIL(avlt) || \
		avlt->nil.bf != 0 || \
		avlt->nil.data != NULL || \
		avlt->root.left != AVL_NIL(avlt) || \
		avlt->root.right != AVL_NIL(avlt) || \
		avlt->root.parent != AVL_NIL(avlt) || \
		avlt->root.bf != 0 || \
		avlt->root.data != NULL) {
		fprintf(stdout, "init 1\n");
		avl_destroy(avlt);
		return 0;
	}

	avl_destroy(avlt);
	return 1;
}

int unit_test_find()
{
	avltree *avlt;
	avlnode *r, *e, *d, *s, *o, *x, *c, *u, *b, *t;
	
	if ((avlt = tree_create()) == NULL) {
		fprintf(stdout, "create AVL tree failed\n");
		goto err0;
	}

	if ((r = tree_insert(avlt, 'R')) == NULL || \
		(e = tree_insert(avlt, 'E')) == NULL || \
		(d = tree_insert(avlt, 'D')) == NULL || \
		(s = tree_insert(avlt, 'S')) == NULL || \
		(o = tree_insert(avlt, 'O')) == NULL || \
		(x = tree_insert(avlt, 'X')) == NULL || \
		(c = tree_insert(avlt, 'C')) == NULL || \
		(u = tree_insert(avlt, 'U')) == NULL || \
		(b = tree_insert(avlt, 'B')) == NULL || \
		(t = tree_insert(avlt, 'T')) == NULL || \
		tree_check(avlt) != 1) {
		fprintf(stdout, "init failed\n");
		goto err;
	}

	if (avl_find(avlt, r->data) != r || \
		avl_find(avlt, e->data) != e || \
		avl_find(avlt, d->data) != d || \
		avl_find(avlt, s->data) != s || \
		avl_find(avlt, o->data) != o || \
		avl_find(avlt, x->data) != x || \
		avl_find(avlt, c->data) != c || \
		avl_find(avlt, u->data) != u || \
		avl_find(avlt, b->data) != b || \
		avl_find(avlt, t->data) != t) {
		fprintf(stdout, "find failed\n");
		goto err;
	}

	avl_destroy(avlt);
	return 1;

err:
	avl_destroy(avlt);
err0:
	return 0;
}

int unit_test_successor()
{
	avltree *avlt;
	avlnode *r, *e, *d, *s, *o, *x, *c, *u, *b, *t;
	
	if ((avlt = tree_create()) == NULL) {
		fprintf(stdout, "create AVL tree failed\n");
		goto err0;
	}

	if ((r = tree_insert(avlt, 'R')) == NULL || \
		(e = tree_insert(avlt, 'E')) == NULL || \
		(d = tree_insert(avlt, 'D')) == NULL || \
		(s = tree_insert(avlt, 'S')) == NULL || \
		(o = tree_insert(avlt, 'O')) == NULL || \
		(x = tree_insert(avlt, 'X')) == NULL || \
		(c = tree_insert(avlt, 'C')) == NULL || \
		(u = tree_insert(avlt, 'U')) == NULL || \
		(b = tree_insert(avlt, 'B')) == NULL || \
		(t = tree_insert(avlt, 'T')) == NULL || \
		tree_delete(avlt, 'O') != 1 || \
		tree_check(avlt) != 1) {
		fprintf(stdout, "init failed\n");
		goto err;
	}

	if (avl_successor(avlt, b) != c || \
		avl_successor(avlt, c) != d || \
		avl_successor(avlt, d) != e || \
		avl_successor(avlt, e) != r || \
		avl_successor(avlt, r) != s || \
		avl_successor(avlt, s) != t || \
		avl_successor(avlt, t) != u || \
		avl_successor(avlt, u) != x || \
		avl_successor(avlt, x) != NULL) {
		fprintf(stdout, "successor failed\n");
		goto err;
	}

	avl_destroy(avlt);
	return 1;

err:
	avl_destroy(avlt);
err0:
	return 0;
}

void all_tests()
{
	mu_test("unit_test_create", unit_test_create());
	mu_test("unit_test_find", unit_test_find());
	mu_test("unit_test_successor", unit_test_successor());
}

int main(int argc, char **argv)
{
	all_tests();

	if (mu_fails) {
		printf("*** %d/%d TESTS FAILED ***\n", mu_fails, mu_tests);
		return 1;
	} else {
		printf("ALL TESTS PASSED\n");
		printf("Tests run: %d\n", mu_tests);
		return 0;
	}
}
