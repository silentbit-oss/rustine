/*
 * Test B.5: Chain insertion and deletion tests
 */

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

int mu_tests = 0, mu_fails = 0;

static avltree *tree_create();
static avlnode *tree_find(avltree *avlt, int key);
static int tree_check(avltree *avlt);
static avlnode *tree_insert(avltree *avlt, int key);
static int tree_delete(avltree *avlt, int key);

static int unit_test_chain_insertion();
static int unit_test_chain_deletion();

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

/*
 * chain insertion
 * move up until height unchanged (one rebalancing operation is performed) or root reached
 */
int unit_test_chain_insertion()
{
	avltree *avlt;
	int i, j;

	char *cases[] = {
		"PHXDB",
		"PHXDF",
		"PHXLJ",
		"PHXLN",
		"PHXTR",
		"PHXTV",
		"PHXbZ",
		"PHXbd",
		"PHXDLB",
		"PHXDLF",
		"PHXDLJ",
		"PHXDLN",
		"PHXTbR",
		"PHXTbV",
		"PHXTbV",
		"PHXTbZ",
		"PHXTbd",
		0
	};

	for (i = 0; i < sizeof(cases) / sizeof(cases[0]) && cases[i] != 0; i++) {
		if ((avlt = tree_create()) == NULL) {
			fprintf(stdout, "%s - create AVL tree failed\n", cases[i]);
			goto err0;
		}

		for (j = 0; j < strlen(cases[i]); j++) {
			if (tree_insert(avlt, cases[i][j]) == NULL || tree_check(avlt) != 1) {
				fprintf(stdout, "%s - insert %c failed\n", cases[i], cases[i][j]);
				goto err;
			}
		}

		avl_destroy(avlt);
	}

	return 1;

err:
	avl_destroy(avlt);
err0:
	return 0;
}

/*
 * chain deletion
 * move up until height unchanged (after one or more rebalancing operations) or root reached
 */
int unit_test_chain_deletion()
{
	avltree *avlt;
	int i, j;

	char *cases[] = {
		"PHXDLTbFJNZK", "T",
		"PHXDLTbFJNZdK", "T",
		"PHXDLTbFJNdK", "T", /* equivalents to PHXDLTzFJNbK */
		"PHXDLTbFRVZU", "L",
		"PHXDLTbBFRVZU", "L",
		"PHXDLTbBRVZU", "L", /* equivalents to PHXFLTbDRVZU */
		0, 0
	};

	for (i = 0; i < sizeof(cases) / sizeof(cases[0]) && cases[i] != 0; i += 2) {
		if ((avlt = tree_create()) == NULL) {
			fprintf(stdout, "%s-%s - create AVL tree failed\n", cases[i], cases[i + 1]);
			goto err0;
		}

		for (j = 0; j < strlen(cases[i]); j++) {
			if (tree_insert(avlt, cases[i][j]) == NULL || tree_check(avlt) != 1) {
				fprintf(stdout, "%s-%s - insert %c failed\n", cases[i], cases[i + 1], cases[i][j]);
				goto err;
			}
		}

		for (j = 0; j < strlen(cases[i + 1]); j++) {
			if (tree_delete(avlt, cases[i + 1][j]) == 0 || tree_check(avlt) != 1) {
				fprintf(stdout, "%s-%s - delete %c failed\n", cases[i], cases[i + 1], cases[i + 1][j]);
				goto err;
			}
		}

		avl_destroy(avlt);
	}

	return 1;

err:
	avl_destroy(avlt);
err0:
	return 0;
}

void all_tests()
{
	mu_test("unit_test_chain_insertion", unit_test_chain_insertion());
	mu_test("unit_test_chain_deletion", unit_test_chain_deletion());
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
