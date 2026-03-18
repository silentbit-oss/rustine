/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "avl_bf.h"
#include "avl_data.h"

#define MIN INT_MIN
#define MAX INT_MAX

static avltree *tree_create();
static avlnode *tree_find(avltree *avlt, int key);
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

int unit_test_atomic_deletion()
{
	avltree *avlt;
	int i, j;
	int test_count = 0;

	char *cases[] = {

	/* we could make a full tree by inserting A-Z and a-e */

	/* balanced */

		/* height decreased */
		"P", "P",
		"PH", "H",
		"PH", "P",
		"PX", "P",
		"PX", "X",

		/* height unchanged */
		"PHX", "H",
		"PHX", "P",
		"PHX", "X",

	/* arrangements required: deletion under P.right */

		/* P.left is left-heavy */  /* height decreased */

		/* H.height = 0 + 2 */
		"PHXD", "X",

		/* H.height = 1 + 2 */
		"PHXDLTBF", "X",
		"PHXDLTB", "X",
		"PHXDLTF", "X",

		/* P.left is balanced */

		/* H.height = 0 + 2 */
		"PHXDL", "X",

		/* H.height = 1 + 2 */
		"PHXDLTBFJN", "X",
		"PHXDLTBFJ", "X",
		"PHXDLTBFN", "X",
		"PHXDLTBJN", "X",
		"PHXDLTBJ", "X",
		"PHXDLTBN", "X",
		"PHXDLTFJN", "X",
		"PHXDLTFJ", "X",
		"PHXDLTFN", "X",

		/* P.left is right-heavy */  /* height decreased */

		/* H.height = 0 + 2 */
		"PHXL", "X",

		/* H.height = 1 + 2 */
		"PHXDLTJN", "X",
		"PHXDLTJ", "X",
		"PHXDLTN", "X",

	/* arrangements required: deletion under P.left */

		/* P.right is right-heavy */  /* height decreased */

		/* X.height = 0 + 2 */
		"PHXb", "H",

		/* X.height = 1 + 2 */
		"PHXDTbZd", "H",
		"PHXDTbZ", "H",
		"PHXDTbd", "H",

		/* P.right is balanced */

		/* X.height = 0 + 2 */
		"PHXTb", "H",

		/* X.height = 1 + 2 */
		"PHXDTbRVZd", "H",
		"PHXDTbRVZ", "H",
		"PHXDTbRVd", "H",
		"PHXDTbRZd", "H",
		"PHXDTbRZ", "H",
		"PHXDTbRd", "H",
		"PHXDTbVZd", "H",
		"PHXDTbVZ", "H",
		"PHXDTbVd", "H",

		/* P.right is left-heavy */  /* height decreased */

		/* X.height = 0 + 2 */
		"PHXT", "H",

		/* X.height = 1 + 2 */
		"PHXDTbRV", "H",
		"PHXDTbR", "H",
		"PHXDTbV", "H",

	/* end */
		0, 0

	};

	for (i = 0; i < sizeof(cases) / sizeof(cases[0]) && cases[i] != 0; i += 2) {
		test_count++;
		if ((avlt = tree_create()) == NULL) {
			fprintf(stdout, "Test %d: %s-%s - create AVL tree failed\n", test_count, cases[i], cases[i + 1]);
			return 0;
		}

		for (j = 0; j < strlen(cases[i]); j++) {
			if (tree_insert(avlt, cases[i][j]) == NULL || tree_check(avlt) != 1) {
				fprintf(stdout, "Test %d: %s-%s - insert %c failed\n", test_count, cases[i], cases[i + 1], cases[i][j]);
				avl_destroy(avlt);
				return 0;
			}
		}

		for (j = 0; j < strlen(cases[i + 1]); j++) {
			if (tree_delete(avlt, cases[i + 1][j]) == 0 || tree_check(avlt) != 1) {
				fprintf(stdout, "Test %d: %s-%s - delete %c failed\n", test_count, cases[i], cases[i + 1], cases[i + 1][j]);
				avl_destroy(avlt);
				return 0;
			}
		}

		avl_destroy(avlt);
	}

	printf("unit_test_atomic_deletion: %d test cases passed\n", test_count);
	return 1;
}

int main(int argc, char **argv)
{
	if (unit_test_atomic_deletion()) {
		printf("TEST PASSED\n");
		return 0;
	} else {
		printf("TEST FAILED\n");
		return 1;
	}
}
