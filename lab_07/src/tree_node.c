#include "../inc/tree_node.h"

tree_node_t *node_create(char *name)
{
    tree_node_t *node;

    node = malloc(sizeof(tree_node_t));

    if (node)
    {
        node->name = name;
        node->count_repeat = 1;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void node_print(tree_node_t *node, void *param)
{
    const char *fmt = param;

    printf(fmt, node->name, node->count_repeat);

}

void node_free(tree_node_t *node, void *param)
{
    free(node->name);
    free(node);
}

void node_f(tree_node_t *node, void *param)
{
    free(node);
}

void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;
    fprintf(f, "%s [label=\" %s %d \"];", tree->name, tree->name, tree->count_repeat);
    if (tree->left)
    {
        fprintf(f, "%s [label=\" %s %d \"];", tree->left->name, tree->left->name, tree->left->count_repeat);
        fprintf(f, "%s -> %s;\n", tree->name, tree->left->name);
    }

    if (tree->right)
    {
        fprintf(f, "%s [label=\" %s %d \"];", tree->right->name, tree->right->name, tree->right->count_repeat);
        fprintf(f, "%s -> %s;\n", tree->name, tree->right->name);
    }
}
