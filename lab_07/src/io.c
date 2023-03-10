#define _GNU_SOURCE

#include "../inc/io.h"
#include "../inc/errors.h"
#include "../inc/tree.h"
#include "../inc/check_f_str.h"
#define MAX_MENU_ITEM_LEN 128

int read_line(FILE *f, char **const str)
{
    if (f == NULL)
        return ERR_POINT_FILE;

    size_t len = 0;
    ssize_t read;

    read = getline(str, &len, f);

    if (read == ERR_GETLINE)
    {
        free(*str);
        *str = NULL;
        return ERR_DATA;
    }

    return PASS;
}

void printf_tree_and_gener_gv(tree_node_t *root)
{
    generate_gv(root);
    printf("\nПрямой обход по дереву: \n");
    btree_apply_pre(root, node_print, "{%s rep: %d} ");
    printf("\n");
}

char *read_str_in_stdin(void)
{
    printf("\nВведите слово: ");
    char *input_word = NULL;
    if (read_line(stdin, &input_word))
        return NULL;
    if (input_word[0] == '\n')
        return NULL;
    if (input_word[strlen(input_word) - 1] == '\n')
        input_word[strlen(input_word) - 1] = '\0';
    puts("");
    return input_word;
}

int read_f_in_bin_tree_ex(FILE *f, tree_node_t **root, size_t *count)
{
    int rc = PASS;
    if (!f)
        return ERR_POINT_FILE;
    if (feof(f))
        return END_OF_FILE;

    char *temp_word = NULL;
    tree_node_t *node;
    *count = 0;

    while (!rc)
    {
        if (feof(f))
            break;

        rc = read_line(f, &temp_word);
        if (temp_word[strlen(temp_word) - 1] == '\n')
            temp_word[strlen(temp_word) - 1] = '\0';

        if (rc)
        {
            btree_apply_post(*root, node_free, NULL);
            break;
        }

        node = node_create(temp_word);
        if (!node)
        {
            btree_apply_post(*root, node_free, NULL);
            rc = ERR_ALLOC;
            break;
        }

        // 0 btree_lookup_1(*root, node->name);

        *root = btree_insert(*root, node);

        temp_word = NULL;
        (*count)++;
    }
    if (*count < 0)
        *count = 0;
    (*root)->height = 0;

    return rc;
}

int read_int(void)
{
    char str[MAX_MENU_ITEM_LEN] = {0};

    if (read_line_action(str, MAX_MENU_ITEM_LEN, stdin) != PASS)
        return ERR_READ_ACTION;

    if (check_int(str))
        return ERR_WRONG_ACTION;
    int num = atoi(str);
    return num;
}

size_t read_line_action(char *s, size_t n, FILE *f)
{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
    s[i] = '\0';
    if (i == 0 || s[0] == '\n')
        return ERR_STR_READ;
    return PASS;
}

int generate_gv(tree_node_t *root)
{
    remove("test.gv");
    FILE *f = fopen("data/main.gv", "w");
    if (f == NULL)
        return ERR_POINT_FILE;

    btree_export_to_dot(f, "test_tree", root);
    fclose(f);
    return PASS;
}

int generate_gv_ex(tree_node_t *root, char *name_f)
{
    FILE *f = fopen(name_f, "w");
    if (f == NULL)
        return ERR_POINT_FILE;

    btree_export_to_dot(f, "test_tree", root);
    fclose(f);
    return PASS;
}
