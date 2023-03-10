#include <stdio.h>

#include "../inc/menu_io.h"
#include "../inc/check_f_str.h"
#include "../inc/io.h"

#include "../inc/errors.h"

void print_menu(void)
{
    puts("");
    puts("|||  МЕНЮ  |||");
    puts("");
    puts("1)  -  Считать с файла и Вывести дерева двоичного поиска");
    puts("2)  -  Поиск слово в дереве (добавление если слова нет)");
    puts("3)  -  Поиск слово в файле (добавление если слова нет)");
    puts("4)  -  Удаление слова в дереве");
    puts("5)  -  Удаление слова в файле");
    puts("6)  -  Сравнение времени поиска слова в дереве и в файле");
    puts("7)  -  Вывести содержимое файла");
    puts("8)  -  Вывести дерево прямой обход");
    puts("9)  -  Вывести дерево обратный обход");
    puts("10) -  Вывести дерево Фланговый  обход");
    puts("11) -  Вывести ИНФО");
    puts("");
    puts("0)  -  Выход из программы");
    puts("");
}

void print_info(void)
{
    puts("");
    puts("|||  ИНФО  |||");
    puts("");
    puts("1)  - Для выбора меню используйте целые числа от 0 до 11");
    puts("2)  - Для поиска/удаления слова ввод осуществляется через консоль, завершите слово [Enter] ");
    puts("3)  - Слово не должно состоять только из [Enter]");
    puts("4)  - Для поиска/вывода/удаления слова в дереве сначала его заполните ");
    puts("5)  - ");

    puts("");
}

// пустой файл

void print_error_message(int code)
{

    if (ERR_POINT_FILE == code)
        printf("\nОШИБКА не удалось отрыть файл. код ошибки =  %d\n", code);
    else if (ERR_INPUT_WORD == code)
    {
        printf("\nОШИБКА ВЫ не правильно ввели слово( попробуйте еще раз. код ошибки =  %d\n", code);
    }
    else if (END_OF_FILE == code)
    {
        printf("\nОШИБКА Файл пуст, заполните его, код ошибки =  %d\n", code);
    }
    else if (ERR_ALLOC == code)
    {
        printf("\nОШИБКА Не получилось выделить память, попробуйте еще раз либо перезапустите приложение, код ошибки =  %d\n", code);
    }
    else if (ERR_STR_READ == code)
    {
        printf("\nОШИБКА Вы ввели пустую строку, код ошибки =  %d\n", code);
    }
    else if (ERR_WRONG_ACTION == code)
    {
        printf("\nОШИБКА Выбора меню, введите целое число [0, 11]. код ошибки =  %d\n", code);
    }
}

int read_action_bim(void)
{
    puts("");
    puts("Данного слова нет, хотите его добавить ? [1 - да/ 0 - нет]");
    int rc = ERR_READ_ACTION;
    int action = 0;
    while (rc)
    {
        action = read_int();
        if (action == 0)
            break;

        else if (action == 1)
        {
            rc = PASS;
            puts("");
            puts("Cлово удачно добавлено в дерево и файл");
            puts("");
        }
        else
        {
            rc = ERR_READ_ACTION;
            puts("Повторите попытку");
        }
    }
    return action;
}

int choose_action(int *action)
{
    puts("Введите целое число от 0 до 11, для выбора меню:  ");
    int menu = read_int();

    if (menu < 0 || menu > 11)
        return ERR_WRONG_ACTION;

    *action = (int)menu;

    return PASS;
}
