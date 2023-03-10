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
#include "../inc/hash.h"

#define END_PROG 0
#define READ_BIN_TREE 1
#define FIND_WORD 2
#define FIND_WORD_HASH 3
#define BALANSE 4
#define EFF_FIND 5
#define EFF_ADD_KEY_HASH 10

#define PRINT_FILE 6
#define PRINT_DDP 7
#define PRINT_HASH 8

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
    hash_table_t table;
    size_t count_w = 0;
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
                puts("Файл не валидный");
                break;
            }
            else
            {
                if (root)
                {
                    btree_apply_post(root, node_free, NULL);
                    root = NULL;
                }

                count_w = 0;
                rc = read_f_in_bin_tree_ex(f, &root, &count_w);
                if (!rc)
                {
                    printf_tree_and_gener_gv(root);
                    rewind(f);
                    hash_table_init(&table, count_w);
                    rc = create_hash_table(f, &table);
                    print_table(&table);
                }

                rewind(f);
            }
        }
        else if (action == FIND_WORD)
        {
            if (count_w)
            {
                char *input_word = read_str_in_stdin();
                if (input_word)
                {
                    find_word_tree_ex(f, &root, input_word, &table);
                    printf_tree_and_gener_gv(root);
                }
                else
                    rc = ERR_STR_READ;
                rewind(f);
            }
            else
            {
                puts("Сначала заполните данные из файла пункт меню ( 1 )");
            }
        }
        else if (action == FIND_WORD_HASH)
        {
            rewind(f);
            if (!count_w)
            {
                puts("Сначала заполните данные из файла пункт меню ( 1 )");
                continue;
            }
            char *input_word = read_str_in_stdin();
            if (input_word)
            {
                printf("\nВведите допустимое число сравнений в хеш-таблице: ");
                int count_cmprs = 0;
                count_cmprs = read_int();
                if (count_cmprs < 1)
                    printf("\nНеверное число сравнений\n");
                else
                {
                    int count_cmp = 0;
                    hash_t *find = NULL;
                    int is_find = PASS;

                    find = hash_find_in_table(&table, input_word, count_cmprs, &is_find, &count_cmp);
                    if (find && is_find == PASS)
                    {
                        puts("Cлово успешно найдено!");
                        printf("{ %s } кол-во сравнений = %d", find->word, count_cmp);
                    }
                    else if (find && is_find == RESTRUCT)
                    {
                        rewind(f);
                        printf("\nЭлемент найден, но требуется реструктуризация\n");
                        printf("{ %s }", find->word);

                        restructuring(f, &table);
                        rewind(f);

                        printf("\nНовая хеш-таблица:\n");
                        print_table(&table);
                    }
                    else
                    {
                        add_word_ex(f, &root, input_word, NOT_FIND_WORD, NULL, &table);
                    }
                }
            }
            else
                rc = ERR_STR_READ;

            rewind(f);
        }
        else if (action == BALANSE)
        {
            if (!is_normal_file(f))
            {
                puts("Файл не валидный");
                break;
            }
            else
            {
                rewind(f);

                if (root)
                {
                    btree_apply_post(root, node_free, NULL);
                   
                    root = NULL;
                }
                count_w = 0;
                rc =  create_tree_avl(&root, f);
                if (!rc)
                {
                    printf_tree_and_gener_gv(root);
                    rewind(f);
                }

                rewind(f);
            }
        }
        else if (action == EFF_FIND)
        {
            print_measurement();
        }
        // else if (action == EFF_ADD_KEY_HASH)
        // {
        //     print_measurement_add();
            
        // }
        else if (action == PRINT_FILE)
        {
            if (!is_normal_file(f))
            {
                puts("Файл не валидный");
                break;
            }
            else
            {
                print_file(f);
            }
        }
        else if (action == PRINT_DDP)
        {
            if (root)
            {
                printf_tree_and_gener_gv(root);
            }
            else
            {
                puts("Сначала заполните дерево");
            }
        }
        else if (action == PRINT_HASH)
        {
            if (count_w)
            {
                print_table(&table);
            }
            else
                puts("Сначала заполните данные из файла пункт меню ( 1 )");
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
