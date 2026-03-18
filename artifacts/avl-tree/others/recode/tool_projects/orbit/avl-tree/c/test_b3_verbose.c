#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "avl_bf.h"
#include "avl_data.h"

#define MIN INT_MIN
#define MAX INT_MAX

static avltree *tree_create();
static int tree_check(avltree *avlt);
static avlnode *tree_insert(avltree *avlt, int key);

avltree *tree_create()
{
	return avl_create(compare_func, destroy_func);
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

int main()
{
	avltree *avlt;
	int i, j;
	int num_cases = 0;

	char *cases[] = {
		"P",
		"PH",
		"PX",
		"PHD",
		"PHXDLB",
		"PHXDLF",
		"PHL",
		"PHXDLJ",
		"PHXDLN",
		"PXb",
		"PHXTbZ",
		"PHXTbd",
		"PHXT",
		"PHXTbRV",
		"PHXTbR",
		"PHXTbV",
		0
	};

	for (i = 0; i < sizeof(cases) / sizeof(cases[0]) && cases[i]; i++) {
		num_cases++;
		if ((avlt = tree_create()) == NULL) {
			fprintf(stdout, "%s - create AVL tree failed\n", cases[i]);
			return 1;
		}

		for (j = 0; j < strlen(cases[i]); j++) {
			if (tree_insert(avlt, cases[i][j]) == NULL || tree_check(avlt) != 1) {
				fprintf(stdout, "%s - insert %c failed\n", cases[i], cases[i][j]);
				avl_destroy(avlt);
				return 1;
			}
		}

		avl_destroy(avlt);
	}

	printf("ALL TESTS PASSED\n");
	printf("Test cases: %d\n", num_cases);
	return 0;
}
