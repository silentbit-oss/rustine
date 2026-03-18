/*
 * Test B.6: Single permutation test
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "avl_bf.h"
#include "avl_data.h"
#include "minunit.h"

#define MIN INT_MIN
#define MAX INT_MAX
#define CHARS "ABCDEFGHIJ"

int mu_tests = 0, mu_fails = 0;
int permutation_error = 0;

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

int main(int argc, char **argv)
{
	avltree *avlt;
	avlnode *node;
	int i;

	if ((avlt = tree_create()) == NULL) {
		fprintf(stdout, "create AVL tree failed\n");
		return 1;
	}

	char b[] = CHARS;

	printf("Inserting: %s\n", b);
	for (i = 0; i < strlen(b); i++) {
		if ((node = tree_insert(avlt, b[i])) == NULL || tree_find(avlt, b[i]) != node || tree_check(avlt) != 1) {
			fprintf(stdout, "insert %c failed\n", b[i]);
			return 1;
		}
	}

	// Try the permutation BACDEFGHIJ
	char delete_order[] = "CABDEFGHIJ";
	printf("\nDeleting: %s\n", delete_order);
	for (i = 0; i < strlen(delete_order); i++) {
		printf("[%d] Deleting %c\n", i+1, delete_order[i]);
		if (tree_delete(avlt, delete_order[i]) != 1 || tree_check(avlt) != 1) {
			fprintf(stdout, "delete %c failed\n", delete_order[i]);
			avl_print(avlt, print_func);
			return 1;
		}
	}

	avl_destroy(avlt);
	printf("\nSUCCESS\n");
	return 0;
}
