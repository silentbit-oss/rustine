/*
 * Generated test for avl_apply function
 * Tests tree traversal with callback function in PREORDER, INORDER, POSTORDER
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "avl_bf.h"
#include "avl_data.h"

#define MIN INT_MIN
#define MAX INT_MAX

/* Test state structure to collect visited nodes */
typedef struct {
    int *values;
    int count;
    int capacity;
} visit_context;

/* Helper functions */
static avltree *tree_create();
static avlnode *tree_insert(avltree *avlt, int key);
static int tree_check(avltree *avlt);

/* Callback function for collecting node values */
static int collect_callback(void *data, void *cookie);

/* Test functions */
static int test_preorder();
static int test_inorder();
static int test_postorder();

avltree *tree_create()
{
    return avl_create(compare_func, destroy_func);
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

/* Callback function to collect visited node values */
int collect_callback(void *data, void *cookie)
{
    mydata *node_data = (mydata *)data;
    visit_context *ctx = (visit_context *)cookie;

    if (ctx->count >= ctx->capacity) {
        fprintf(stdout, "collect_callback: context buffer overflow\n");
        return 1; /* error */
    }

    ctx->values[ctx->count++] = node_data->key;
    return 0; /* success */
}

/* Test PREORDER traversal */
int test_preorder()
{
    avltree *avlt;
    int result = 0;
    int i;

    printf("Testing PREORDER traversal...\n");

    if ((avlt = tree_create()) == NULL) {
        fprintf(stdout, "create AVL tree failed\n");
        return 1;
    }

    /* Build a tree with 7 nodes: 4, 2, 6, 1, 3, 5, 7 */
    int keys[] = {4, 2, 6, 1, 3, 5, 7};
    int num_keys = 7;

    for (i = 0; i < num_keys; i++) {
        if (tree_insert(avlt, keys[i]) == NULL || tree_check(avlt) != 1) {
            fprintf(stdout, "insert %d failed\n", keys[i]);
            result = 1;
            goto cleanup;
        }
    }

    /* Expected PREORDER: 4, 2, 1, 3, 6, 5, 7 */
    int expected[] = {4, 2, 1, 3, 6, 5, 7};

    /* Create context to collect visited values */
    visit_context ctx;
    ctx.capacity = 10;
    ctx.count = 0;
    ctx.values = (int *)malloc(ctx.capacity * sizeof(int));
    if (ctx.values == NULL) {
        fprintf(stdout, "malloc failed\n");
        result = 1;
        goto cleanup;
    }

    /* Apply traversal */
    if (AVL_APPLY(avlt, collect_callback, &ctx, PREORDER) != 0) {
        fprintf(stdout, "avl_apply failed\n");
        free(ctx.values);
        result = 1;
        goto cleanup;
    }

    /* Verify results */
    if (ctx.count != num_keys) {
        fprintf(stdout, "PREORDER: Expected %d values, got %d\n", num_keys, ctx.count);
        result = 1;
    } else {
        for (i = 0; i < num_keys; i++) {
            if (ctx.values[i] != expected[i]) {
                fprintf(stdout, "PREORDER: Mismatch at position %d: expected %d, got %d\n",
                        i, expected[i], ctx.values[i]);
                result = 1;
                break;
            }
        }
    }

    if (result == 0) {
        printf("PREORDER test PASSED\n");
    }

    free(ctx.values);

cleanup:
    avl_destroy(avlt);
    return result;
}

/* Test INORDER traversal */
int test_inorder()
{
    avltree *avlt;
    int result = 0;
    int i;

    printf("\nTesting INORDER traversal...\n");

    if ((avlt = tree_create()) == NULL) {
        fprintf(stdout, "create AVL tree failed\n");
        return 1;
    }

    /* Build a tree with 7 nodes: 4, 2, 6, 1, 3, 5, 7 */
    int keys[] = {4, 2, 6, 1, 3, 5, 7};
    int num_keys = 7;

    for (i = 0; i < num_keys; i++) {
        if (tree_insert(avlt, keys[i]) == NULL || tree_check(avlt) != 1) {
            fprintf(stdout, "insert %d failed\n", keys[i]);
            result = 1;
            goto cleanup;
        }
    }

    /* Expected INORDER: 1, 2, 3, 4, 5, 6, 7 (sorted) */
    int expected[] = {1, 2, 3, 4, 5, 6, 7};

    /* Create context to collect visited values */
    visit_context ctx;
    ctx.capacity = 10;
    ctx.count = 0;
    ctx.values = (int *)malloc(ctx.capacity * sizeof(int));
    if (ctx.values == NULL) {
        fprintf(stdout, "malloc failed\n");
        result = 1;
        goto cleanup;
    }

    /* Apply traversal */
    if (AVL_APPLY(avlt, collect_callback, &ctx, INORDER) != 0) {
        fprintf(stdout, "avl_apply failed\n");
        free(ctx.values);
        result = 1;
        goto cleanup;
    }

    /* Verify results */
    if (ctx.count != num_keys) {
        fprintf(stdout, "INORDER: Expected %d values, got %d\n", num_keys, ctx.count);
        result = 1;
    } else {
        for (i = 0; i < num_keys; i++) {
            if (ctx.values[i] != expected[i]) {
                fprintf(stdout, "INORDER: Mismatch at position %d: expected %d, got %d\n",
                        i, expected[i], ctx.values[i]);
                result = 1;
                break;
            }
        }
    }

    if (result == 0) {
        printf("INORDER test PASSED\n");
    }

    free(ctx.values);

cleanup:
    avl_destroy(avlt);
    return result;
}

/* Test POSTORDER traversal */
int test_postorder()
{
    avltree *avlt;
    int result = 0;
    int i;

    printf("\nTesting POSTORDER traversal...\n");

    if ((avlt = tree_create()) == NULL) {
        fprintf(stdout, "create AVL tree failed\n");
        return 1;
    }

    /* Build a tree with 7 nodes: 4, 2, 6, 1, 3, 5, 7 */
    int keys[] = {4, 2, 6, 1, 3, 5, 7};
    int num_keys = 7;

    for (i = 0; i < num_keys; i++) {
        if (tree_insert(avlt, keys[i]) == NULL || tree_check(avlt) != 1) {
            fprintf(stdout, "insert %d failed\n", keys[i]);
            result = 1;
            goto cleanup;
        }
    }

    /* Expected POSTORDER: 1, 3, 2, 5, 7, 6, 4 */
    int expected[] = {1, 3, 2, 5, 7, 6, 4};

    /* Create context to collect visited values */
    visit_context ctx;
    ctx.capacity = 10;
    ctx.count = 0;
    ctx.values = (int *)malloc(ctx.capacity * sizeof(int));
    if (ctx.values == NULL) {
        fprintf(stdout, "malloc failed\n");
        result = 1;
        goto cleanup;
    }

    /* Apply traversal */
    if (AVL_APPLY(avlt, collect_callback, &ctx, POSTORDER) != 0) {
        fprintf(stdout, "avl_apply failed\n");
        free(ctx.values);
        result = 1;
        goto cleanup;
    }

    /* Verify results */
    if (ctx.count != num_keys) {
        fprintf(stdout, "POSTORDER: Expected %d values, got %d\n", num_keys, ctx.count);
        result = 1;
    } else {
        for (i = 0; i < num_keys; i++) {
            if (ctx.values[i] != expected[i]) {
                fprintf(stdout, "POSTORDER: Mismatch at position %d: expected %d, got %d\n",
                        i, expected[i], ctx.values[i]);
                result = 1;
                break;
            }
        }
    }

    if (result == 0) {
        printf("POSTORDER test PASSED\n");
    }

    free(ctx.values);

cleanup:
    avl_destroy(avlt);
    return result;
}

int main()
{
    int failures = 0;

    printf("=== Testing avl_apply function ===\n\n");

    if (test_preorder() != 0) failures++;
    if (test_inorder() != 0) failures++;
    if (test_postorder() != 0) failures++;

    printf("\n=== Test Results ===\n");
    if (failures == 0) {
        printf("All tests PASSED\n");
        return 0;
    } else {
        printf("%d test(s) FAILED\n", failures);
        return 1;
    }
}
