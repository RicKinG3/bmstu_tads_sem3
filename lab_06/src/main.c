// Построить частотный словарь (слово – количество повторений) из слов текстового
// файла в виде дерева двоичного поиска. Вывести его на экран в виде дерева.
// Осуществить поиск указанного слова в дереве и в файле. Если слова нет, то (по
// желанию пользователя) добавить его в дерево и, соответственно, в файл. Сравнить
// время поиска слова в дереве и в файле

// Реализовать основные операции работы с деревом: обход дерева,
// включение, исключение и поиск узлов. Сравнить эффективность алгоритмов
// сортировки и поиска в зависимости от высоты дерева и степени его ветвления.

#include <assert.h>
#include <stdio.h>
#include "../inc/tree.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/menu_io.h"
#include "../inc/check_f_str.h"
#include "../inc/file.h"
#include "../inc/meansure_tree.h"

#define END_PROG 0
#define READ_BIN_TREE 1
#define FIND_WORD 2
#define FIND_WORD_F 3
#define DEL_NODE 4
#define DEL_NODE_F 5
#define MENSUARE 6
#define PRINT_FILE 7
#define PRINT_PRE 8
#define PRINT_POST 9
#define PRINT_IN 10
#define PRINT_INFO 11

int main(int argc, char **argv)
{
    int rc = PASS;
    int action = READ_BIN_TREE;
    FILE *f = check_in_f(argc, argv[1]);
    if (!f)
    {
        print_error_message(ERR_POINT_FILE);
        return ERR_POINT_FILE;
    }
    tree_node_t *root = NULL;

    while (action)
    {
        print_menu();

        rc = choose_action(&action);
        if (rc)
        {
            print_error_message(rc);
            continue;
        }
        if (action == END_PROG)
        {
            rc = action;
            btree_apply_post(root, node_free, NULL);
            break;
        }
        else if (action == READ_BIN_TREE)
        {
            if (!is_normal_file(f))
            {
                break;
            }
            else
            {
                if (root)
                {
                    btree_apply_post(root, node_free, NULL);
                    root = NULL;
                }

                rc = read_f_in_bin_tree_ex(f, &root);
                if (!rc)
                    printf_tree_and_gener_gv(root);
                rewind(f);
            }
        }
        else if (action == FIND_WORD)
        {
            char *input_word = read_str_in_stdin();
            if (input_word)
            {
                find_word_tree_ex(f, &root, input_word);
                printf_tree_and_gener_gv(root);
            }
            else
                rc = ERR_STR_READ;
            rewind(f);
        }
        else if (action == FIND_WORD_F)
        {
            rewind(f);
            char *input_word = read_str_in_stdin();
            if (input_word)
            {
                rc = find_word_file_ex(f, &root, input_word);
            }
            else
                rc = ERR_STR_READ;

            rewind(f);
        }
        else if (action == DEL_NODE)
        {
            if (root)
            {
                char *input_word = read_str_in_stdin();
                if (input_word)
                {
                    delete_word(&root, input_word);
                    printf_tree_and_gener_gv(root);
                }
                else
                    rc = ERR_ALLOC;
            }
            else
                puts("Для начала заполните дерево");
        }
        else if (action == DEL_NODE_F)
        {
            rewind(f);
            char *input_word = read_str_in_stdin();
            if (input_word)
            {
                rc = del_word_in_file(f, input_word, argv[1]);
                if (rc == NOT_FIND_WORD)
                    puts("Слово не найдено в файле");
                else
                    puts("Слово успешно удаленно");
                rc = PASS;
            }
            else
                rc = ERR_ALLOC;
        }
        else if (action == MENSUARE)
        {
            print_measurement();
        }
        else if (action == PRINT_FILE)
        {
            if (!is_normal_file(f))
            {
                break;
            }
            print_file(f);
        }
        else if (action == PRINT_PRE)
        {
            if (root)
            {
                printf("\nПрямой обход по дереву: \n");
                btree_apply_pre(root, node_print, "{%s rep: %d} ");
            }
            else
            {
                puts("Сначала заполните дерево");
            }
        }
        else if (action == PRINT_POST)
        {
            if (root)
            {
                printf("\nОбратный обход по дереву: \n");
                btree_apply_post(root, node_print, "{%s rep: %d} ");
            }
            else
            {
                puts("Сначала заполните дерево");
            }
        }
        else if (action == PRINT_IN)
        {
            if (root)
            {
                printf("\nФланговый обход по дереву: \n");
                btree_apply_in(root, node_print, "{%s rep: %d} ");
            }
            else
            {
                puts("Сначала заполните дерево");
            }
        }
        else if (action == PRINT_INFO)
        {
            print_info();
        }

        if (rc)
        {
            print_error_message(rc);
            rc = PASS;

            continue;
        }
    }

    fclose(f);
    return rc;
}
