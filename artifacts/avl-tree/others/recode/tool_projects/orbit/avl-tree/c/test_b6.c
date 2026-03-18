/*
 * Test B.6: Permutation insertion and deletion tests
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

static void swap(char *x, char *y);
static void permute(char *a, int start, int end, void func(char *));
static void permutation_insert(char *a);
static void permutation_delete(char *a);

static int unit_test_permutation_insertion();
static int unit_test_permutation_deletion();

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

void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void permute(char *a, int start, int end, void func(char *))
{
	if (start == end) {
		func(a);
		return;
	}

	int i;
	for (i = start; i <= end; i++) {
		swap(a + start, a + i);
		permute(a, start + 1, end, func);
		swap(a + start, a + i);
	}
}

void permutation_insert(char *a)
{
	avltree *avlt;
	avlnode *node;
	int i;

	if ((avlt = tree_create()) == NULL) {
		fprintf(stdout, "create AVL tree failed\n");
		permutation_error++;
		return;
	}

	for (i = 0; i < strlen(a); i++) {
		if ((node = tree_insert(avlt, a[i])) == NULL || tree_find(avlt, a[i]) != node || tree_check(avlt) != 1) {
			fprintf(stdout, "insert %c failed\n", a[i]);
			permutation_error++;
			return;
		}
	}

	avl_destroy(avlt);
}

void permutation_delete(char *a)
{
	avltree *avlt;
	avlnode *node;
	int i;

	if ((avlt = tree_create()) == NULL) {
		fprintf(stdout, "create AVL tree failed\n");
		permutation_error++;
		return;
	}

	char b[] = CHARS;

	for (i = 0; i < strlen(b); i++) {
		if ((node = tree_insert(avlt, b[i])) == NULL || tree_find(avlt, b[i]) != node || tree_check(avlt) != 1) {
			fprintf(stdout, "insert %c failed\n", b[i]);
			permutation_error++;
			return;
		}
	}

	for (i = 0; i < strlen(a); i++) {
		if (tree_delete(avlt, a[i]) != 1 || tree_check(avlt) != 1) {
			fprintf(stdout, "delete %c failed\n", a[i]);
			permutation_error++;
			return;
		}
	}

	avl_destroy(avlt);
}

int unit_test_permutation_insertion()
{
	char a[] = CHARS;

	permutation_error = 0;
	permute(a, 0, strlen(a) - 1, permutation_insert);
	return (permutation_error == 0);
}

int unit_test_permutation_deletion()
{
	char a[] = CHARS;

	permutation_error = 0;
	permute(a, 0, strlen(a) - 1, permutation_delete);
	return (permutation_error == 0);
}

void all_tests()
{
	mu_test("unit_test_permutation_insertion", unit_test_permutation_insertion());
	mu_test("unit_test_permutation_deletion", unit_test_permutation_deletion());
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
