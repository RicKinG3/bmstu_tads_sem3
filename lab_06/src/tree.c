#include "../inc/tree.h"
#include "../inc/io.h"
#include "../inc/errors.h"
#include "../inc/file.h"
#include "../inc/menu_io.h"

int add_word_trr(tree_node_t **tree, char *input_word)
{
    int rc = PASS;
    tree_node_t *node = node_create(input_word);
    if (!node)
    {
        btree_apply_post(*tree, node_free, NULL);
        rc = ERR_ALLOC;
    }
    else
        *tree = btree_insert(*tree, node);

    return rc;
}

int find_word_tree(tree_node_t **tree, char *input_word, tree_node_t **find_node)
{
    (*find_node) = btree_lookup_1(*tree, input_word);
    if (*find_node)
        return IS_FIND_WORD;
    else
        return NOT_FIND_WORD;
}

void add_word_ex(FILE *f, tree_node_t **root, char *input_word, int action, tree_node_t *find_node)
{
    if (action == NOT_FIND_WORD)
    {
        action = read_action_bim();
        if (action == 1) // add word
        {
            add_word_in_f(f, input_word);
            add_word_trr(root, input_word);
        }
    }
    else
    {
        puts("Слово найдено");
        node_print(find_node, "{%s rep: %d} ");
        puts("");
    }
}

void find_word_tree_ex(FILE *f, tree_node_t **root, char *input_word)
{
    int action = PASS;
    tree_node_t *find_node = NULL;
    action = find_word_tree(root, input_word, &find_node);
    add_word_ex(f, root, input_word, action, find_node);
}

tree_node_t *btree_insert(tree_node_t *tree, tree_node_t *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = strcmp(node->name, tree->name);
    if (cmp == 0)
        tree->count_repeat++;
    else if (cmp < 0)
        tree->left = btree_insert(tree->left, node);
    else
        tree->right = btree_insert(tree->right, node);

    return tree;
}

tree_node_t *btree_lookup_1(tree_node_t *tree, const char *name)
{
    int cmp;

    if (tree == NULL)
        return NULL;

    cmp = strcmp(name, tree->name);
    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        return btree_lookup_1(tree->left, name);
    else
        return btree_lookup_1(tree->right, name);
}

tree_node_t *btree_lookup_2(tree_node_t *tree, const char *name)
{
    int cmp;

    while (tree != NULL)
    {
        cmp = strcmp(name, tree->name);

        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}

void btree_apply_pre(tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}

void btree_apply_in(tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_in(tree->left, f, arg);
    f(tree, arg);
    btree_apply_in(tree->right, f, arg);
}

void btree_apply_post(tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_post(tree->left, f, arg);
    btree_apply_post(tree->right, f, arg);
    f(tree, arg);
}

void btree_export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

typedef void (*search_t)(tree_node_t **curr, char *word, tree_node_t **parent);
static tree_node_t *get_min_word(tree_node_t *curr);
static void search_word(tree_node_t **curr, char *word, tree_node_t **parent);
static int delete_node(tree_node_t **tree, char *word, search_t search);

void delete_word(tree_node_t **tree, char* word)
{
    int rc = delete_node(tree, word, search_word);
    if (rc != 0)
        printf("В бинарном дереве нет такого слова\n");
    else
        printf("Данные успешно удалены\n");
}

tree_node_t *findMaximumKey(tree_node_t *ptr)
{
    while (ptr->right != NULL)
    {
        ptr = ptr->right;
    }
    return ptr;
}

// функция для поиска в поддереве с корнем curr и установки его родителя
static void search_word(tree_node_t **curr, char *word, tree_node_t **parent)
{
    // обход дерева и поиск ключа
    while (*curr != NULL && (strcmp(word, (*curr)->name) != 0))
    {
        // обновить родителя до текущего узла
        *parent = *curr;

        // если заданный ключ меньше текущего узла, переходим в левое поддерево
        // иначе идем в правое поддерево
        int cmp = strcmp(word, (*curr)->name);
        if (cmp < 0)
            *curr = (*curr)->left;
        else
            *curr = (*curr)->right;
    }
}

// Вспомогательная функция для поиска узла минимального значения в поддереве с корнем curr
static tree_node_t *get_min_word(tree_node_t *curr)
{
    while (curr->left != NULL)
        curr = curr->left;

    return curr;
}
/*
 * Функция удаляет узел из дерева
 *
 * Принимает указатель на указатель на корень, слово и функцию для поиска
 */

static int delete_node(tree_node_t **tree, char *word, search_t search)
{
    // указатель для хранения родителя текущего узла
    tree_node_t *parent = NULL;

    // начинаем с корневого узла
    tree_node_t *curr = *tree;

    // поиск ключа и установка его родительского указателя
    search(&curr, word, &parent);

    // возвращаем, если ключ не найден в дереве
    if (curr == NULL)
        return 1;

    // Случай 1: удаляемый узел не имеет дочерних элементов, т. е. является листовым узлом
    if ((curr->left == NULL) && (curr->right == NULL))
    {
        // если удаляемый узел не является корневым узлом, то устанавливаем его
        // родительский левый/правый дочерний элемент в null
        if (curr != *tree)
        {
            if (parent->left == curr)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        // если дерево имеет только корневой узел, устанавливаем его в null
        else
        {
            *tree = NULL;
        }

        // освобождаем память
        free(curr); // или delete curr;
    }

    // Случай 2: удаляемый узел имеет двух потомков
    else if (curr->left && curr->right)
    {
        // найти его неупорядоченный узел-преемник
        tree_node_t *successor = get_min_word(curr->right);

        // сохраняем последующее значение
        char word_tmp[MAX_STR_LEN + 1];
        strcpy(word_tmp, successor->name);

        // рекурсивно удаляем преемника. Обратите внимание, что преемник
        // будет иметь не более одного потомка (правого потомка)
        delete_node(tree, successor->name, search_word);

        // копируем значение преемника в текущий узел
        strcpy(curr->name, word_tmp);
    }
    // Случай 3: удаляемый узел имеет только одного потомка
    else
    {
        // выбираем дочерний узел
        tree_node_t *child = (curr->left) ? curr->left : curr->right;

        // если удаляемый узел не является корневым узлом, устанавливаем его родителя
        // своему потомку
        if (curr != *tree)
        {
            if (curr == parent->left)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        // если удаляемый узел является корневым узлом, то установить корень дочернему
        else
        {
            *tree = child;
        }

        // освобождаем память
        free(curr);
    }

    return 0;
}
