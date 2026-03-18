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

int unit_test_atomic_insertion()
{
	avltree *avlt;
	int i, j;

	char *cases[] = {

	/* we could make a full tree by inserting A-Z and a-e */

	/* balanced */

		/* height insreased */
		"P",
		"PH",
		"PX",

		/* height unchanged
		"PHX",
		"PXH",

	/* arrangements required: insertion under P.left */

		/* P.left is left-heavy */

		/* H.height = 0 + 2 */
		"PHD",

		/* H.height = 1 + 2 */
		"PHXDLB",
		"PHXDLF",

		/* P.left is right-heavy */

		/* H.height = 0 + 2 */
		"PHL",

		/* H.height = 1 + 2 */
		"PHXDLJ",
		"PHXDLN",

	/* arrangements required: insertion under P.right */

		/* P.right is right-heavy */

		/* X.height = 0 + 2 */
		"PXb",

		/* X.height = 1 + 2 */
		"PHXTbZ",
		"PHXTbd",

		/* P.right is left-heavy */

		/* X.height = 0 + 2 */
		"PHXT",

		/* X.height = 1 + 2 */
		"PHXTbRV",
		"PHXTbR",
		"PHXTbV",

	/* end */
		0

	};

	for (i = 0; i < sizeof(cases) / sizeof(cases[0]) && cases[i]; i++) {
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

void all_tests()
{
	mu_test("unit_test_atomic_insertion", unit_test_atomic_insertion());
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
