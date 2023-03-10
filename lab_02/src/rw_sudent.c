#include "../inc/error.h"
#include "../inc/rw_student.h"
#include "../inc/check_str.h"

size_t read_line(char *s, size_t n, FILE *f)
{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
    s[i] = '\0';
    if (i == 0 || s[0] == '\n')
        return ERR_READ;
    return PASS;
}

void init_struct_null(inf_stdnt_t stdnt)
{
    memset(stdnt.type_home, '\0', MAX_LEN_STR);
    memset(stdnt.second_name, '\0', MAX_LEN_STR);
    memset(stdnt.name, '\0', MAX_LEN_STR);
    memset(stdnt.group, '\0', MAX_LEN_STR);
    memset(stdnt.gender, '\0', MAX_LEN_STR);
    memset(stdnt.adress_u.home_t.street, '\0', MAX_LEN_STR);
}

int input_stdnt(inf_stdnt_t *stdnt, int count_stdnt, FILE *f, int mode, int pos)
{
    char temp[MAX_LEN_STR] = {0};
    int temp_int = 0;
    double temp_double = 0.0;

    for (int i = pos; i < count_stdnt; i++)
    {
        init_struct_null(stdnt[i]);
        if (mode)
            printf("Введите тип жилья(home or hostel):");
        // input type home + check
        if (fgets(stdnt[i].type_home, MAX_LEN_STR, f) == NULL)
            return ERR_TYPE_HOME;
        // del \n in end str
        stdnt[i].type_home[strlen(stdnt[i].type_home) - 1] = '\0';
        // chek
        if (check_type_home(stdnt, i))
            return ERR_TYPE_HOME;

        // input second name
        if (mode)
            printf("\nВведите фамилию:");
        if (fgets(stdnt[i].second_name, MAX_LEN_STR, f) == NULL)
            return ERR_SECOND_NAME;
        stdnt[i].second_name[strlen(stdnt[i].second_name) - 1] = '\0';
        if (check_name(stdnt[i].second_name))
            return ERR_SECOND_NAME;

        // input name
        if (mode)
            printf("\nВведите имя:");
        if (fgets(stdnt[i].name, MAX_LEN_STR, f) == NULL)
            return ERR_NAME;
        stdnt[i].name[strlen(stdnt[i].name) - 1] = '\0';
        if (check_name(stdnt[i].name))
            return ERR_NAME;

        // input group
        if (mode)
            printf("\nВведите группу:");
        if (fgets(stdnt[i].group, MAX_LEN_STR, f) == NULL)
            return ERR_GROUP;
        stdnt[i].group[strlen(stdnt[i].group) - 1] = '\0';
        if (check_group(stdnt[i].group))
            return ERR_GROUP;

        // input gender
        if (mode)
            printf("\nВведите гендер:");

        if (fgets(stdnt[i].gender, MAX_LEN_STR, f) == NULL)
            return ERR_GENDER;
        stdnt[i].gender[strlen(stdnt[i].gender) - 1] = '\0';
        if (check_gender(stdnt[i].gender))
            return ERR_GENDER;

        memset(temp, '\0', MAX_LEN_STR);
        temp_int = 0;

        // input age student
        if (mode)
            printf("\nВведите возвраст:");

        if (read_line(temp, sizeof(temp), f) == ERR_READ)
            return ERR_AGE_STUDENT;
        if (check_int(temp))
            return ERR_AGE_STUDENT;

        temp_int = atoi(temp);
        if (temp_int <= 0 || temp_int > 150)
            return ERR_AGE_STUDENT;
        stdnt[i].age = temp_int;

        temp_int = 0;
        memset(temp, '\0', MAX_LEN_STR);

        // input double avg mark
        if (mode)
            printf("\nВведите средний балл студента:");

        if (read_line(temp, sizeof(temp), f) == ERR_READ)
            return ERR_AVG_MARK_STUDENT;
        if (check_double(temp))
            return ERR_AVG_MARK_STUDENT;

        temp_double = atof(temp);
        stdnt[i].avg_mark = temp_double;

        temp_double = 0;
        memset(temp, '\0', MAX_LEN_STR);

        // year year_admission
        if (mode)
            printf("\nВведите год поступления:");

        if (read_line(temp, sizeof(temp), f) == ERR_READ)
            return ERR_YEAR;
        if (check_int(temp))
            return ERR_YEAR;

        temp_int = atoi(temp);
        if (temp_int <= 1900 || temp_int > 2023)
            return ERR_YEAR;

        stdnt[i].year_admission = temp_int;
        temp_int = 0;
        memset(temp, '\0', MAX_LEN_STR);

        // adress variable field
        if (stdnt[i].item_home == HOME)
        {
            // input street in home
            if (mode)
                printf("\nВведите улицу дома:");

            if (fgets(stdnt[i].adress_u.home_t.street, MAX_LEN_STR, f) == NULL)
                return ERR_STREET;
            stdnt[i].adress_u.home_t.street[strlen(stdnt[i].adress_u.home_t.street) - 1] = '\0';
            if (check_group(stdnt[i].adress_u.home_t.street))
                return ERR_STREET;

            // number home
            if (mode)
                printf("\nВведите номемр дома:");

            if (read_line(temp, sizeof(temp), f) == ERR_READ)
                return ERR_NUMBER_HOME;
            if (check_int(temp))
                return ERR_NUMBER_HOME;

            temp_int = atoi(temp);
            if (temp_int == 0)
                return ERR_NUMBER_HOME;

            stdnt[i].adress_u.home_t.home = temp_int;
            temp_int = 0;
            memset(temp, '\0', MAX_LEN_STR);

            // number flat
            if (mode)
                printf("\nВведите номемр квартиры:");

            if (read_line(temp, sizeof(temp), f) == ERR_READ)
                return ERR_NUMBER_FLAT;
            if (check_int(temp))
                return ERR_NUMBER_FLAT;

            temp_int = atoi(temp);
            if (temp_int == 0)
                return ERR_NUMBER_FLAT;

            stdnt[i].adress_u.home_t.flat = temp_int;
            temp_int = 0;
            memset(temp, '\0', MAX_LEN_STR);
        }
        else if (stdnt[i].item_home == HOSTEL)
        {
            // input number hostel
            if (mode)
                printf("\nВведите номемр общажития:");

            if (read_line(temp, sizeof(temp), f) == ERR_READ)
                return ERR_NUMBER_HOSTEL;
            if (check_int(temp))
                return ERR_NUMBER_HOSTEL;

            temp_int = atoi(temp);
            if (temp_int == 0)
                return ERR_NUMBER_HOSTEL;

            stdnt[i].adress_u.hostel_t.number_hostel = temp_int;
            temp_int = 0;
            memset(temp, '\0', MAX_LEN_STR);

            // input room hostel
            // number flat
            if (mode)
                printf("\nВведите номер комнаты:");

            if (read_line(temp, sizeof(temp), f) == ERR_READ)
                return ERR_NUMBER_ROOM;
            if (check_int(temp))
                return ERR_NUMBER_ROOM;

            temp_int = atoi(temp);
            if (temp_int == 0)
                return ERR_NUMBER_ROOM;

            stdnt[i].adress_u.hostel_t.room = temp_int;
            temp_int = 0;
            memset(temp, '\0', MAX_LEN_STR);
        }
    }
    return PASS;
}

void input_key_tables(inf_stdnt_t *arr_stdnt, key_tables_t *arr_key, int num_count_std)
{
    for (int i = 0; i < num_count_std; i++)
    {
        arr_key[i].index = i;
        arr_key[i].year_admission = arr_stdnt[i].year_admission;
    }
}
void print_key_tables(key_tables_t *arr_key, int num_count_std)
{
    puts("");
    printf("%-3s | %-3s | %-5s |\n", "N", "ind", "year");
    printf(":-----------------:\n");
    for (int i = 0; i < num_count_std; i++)
    {
        printf("%-3d | %-3d | %-5d |\n", i, arr_key[i].index, arr_key[i].year_admission);
    }
    puts("");
}

int item_input(FILE *f, inf_stdnt_t *arr_stdnt, char *count_stdnt, int *num_count_std, int item)
{
    if (item)
    {
        printf("Ведите кол-во студентов: ");

        if (read_line(count_stdnt, sizeof(count_stdnt), stdin) == ERR_READ)
        {
            puts("Ошибка введено не верное целое число студентов");
            return ERR_COUNT_STUDENT;
        }
        if (check_int(count_stdnt))
        {
            puts("Ошибка введено не верное целое число студентов");
            return ERR_COUNT_STUDENT;
        }
        *num_count_std = atoi(count_stdnt);
        if (*num_count_std > MAX_STDNT || *num_count_std < 1)
        {
            puts("Ошибка введеное не верное количество студентов диапозон от 1 до 40");
            return ERR_COUNT_STUDENT;
        }
        puts("");
        return input_stdnt(arr_stdnt, *num_count_std, stdin, LOUD_INPUT, START);
    }
    else
    {
        fscanf(f, "%d\n", num_count_std);
        if (*num_count_std > MAX_STDNT || *num_count_std < 1)
            return ERR_COUNT_STUDENT;
        return input_stdnt(arr_stdnt, *num_count_std, f, QUIT_INPUT, START);
    }

    return PASS;
}

void print_menu(void)
{
    printf("\n  ||| МЕНЮ |||\n");
    printf("    0) Выход из программы \n");
    printf("    1) Добавить 1 запись в конец\n");
    printf("    2) Удалить всех студентов имеющий введенный год поступления\n");
    printf("    3) Вывести список студентов, указанного года поступления, живущих в общежитии\n");
    printf("    4) Вывести отсортированную таблицу ключей\n");
    printf("    5) Вывести отсортированную структуру\n");
    printf("    6) Вывести отсортированную структуру по ключу\n");
    printf("    7) Вывести структуру\n");
    printf("    8) Вывести результат сравнения эффективности работы программы "
           "при обработке данных в исходной таблице и в таблице ключей;\n");
    printf("    9) Вывести результат использования различных алгоритмов сортировок\n");
    printf("   10) Информация ввода\n");
}

void print_error_input(int rc)
{
    if (rc)
    {
        if (rc == ERR_TYPE_HOME)
            puts("Ошибка введено не верный тип жилья  home or hostel");
        else if (rc == ERR_SECOND_NAME)
            puts("Ошибка введено не верная фамилия, в фамилии не должно быть символов отличных от символов англ яз");
        else if (rc == ERR_NAME)
            puts("Ошибка введено не верное имя,в имени не должно быть символов отличных от символов англ яз");
        else if (rc == ERR_GROUP)
            puts("Ошибка введено не верная группа, в группе не должно быть пробелов");
        else if (rc == ERR_GENDER)
            puts("Ошибка введено не верный пол, пол либо m либо f");
        else if (rc == ERR_AGE_STUDENT)
            puts("Ошибка введено не верный возраст, возраст либо от 1 до 150");
        else if (rc == ERR_AVG_MARK_STUDENT)
            puts("Ошибка введено не верный средний балл, балл должен быть вещественный и может содержать только одну точку");
        else if (rc == ERR_YEAR)
            puts("Ошибка введено не верный год, год должен быть больше 1900 и меньше 2023");
        else if (rc == ERR_STREET)
            puts("Ошибка введено не верная улица, улица не может содержать пробелов");
        else if (rc == ERR_NUMBER_HOME)
            puts("Ошибка введено не верный номер дома, номер должен быть целым и не содержать знака");
        else if (rc == ERR_NUMBER_FLAT)
            puts("Ошибка введено не верный номер квартиры, номер должен быть целым и не содержать знака");
        else if (rc == ERR_NUMBER_HOSTEL)
            puts("Ошибка введено не верный номер общаги, номер должен быть целым и не содержать знака");
        else if (rc == ERR_NUMBER_ROOM)
            puts("Ошибка введено не верный номер комнаты, номер должен быть целым и не содержать знака");
    }
}

void print_info(void)
{
    printf("\n  ||| ИНФО ПРАВИЛА ВВОДА |||\n");
    printf("    *) Все поля вводятся без пробелов, максимальная строка ввода = 127\n");
    printf("    0) Тип жилья вводится латинскими буквами и необходимо выбрать home - дом или hostel - общежитие\n");
    printf("    1) Фамилия вводится только латинскими буквами\n");
    printf("    2) Имя вводится только латинскими буквами\n");
    printf("    3) Группа вводится латинскими буквами и может содержать цифры, или другие символы\n");
    printf("    4) Гендер может содержать только m - мужской или f - женский\n");
    printf("    5) Возраст вводится целыми без знаковыми числами и должен быть больше 1 и меньше 150 лет\n");
    printf("    6) Средний балл вводится в вещественном формате может иметь только одну точку не в начале числа\n");
    printf("    7) Год поступления вводится целым без знаковым числом и должен быть больше 1900 и меньше 2024 года\n");
    printf("    8) Если выбран тип жилья - home, то вводится улица дома, номер дома -  целое без занка число,  квартира - целое беззнаковое число\n");
    printf("    9) Если выбран тип жилья - hostel, то вводится номер общежитии - целое без знака число, номер комнаты - целое без знака число \n");
    printf("   10) Для выбора меню вводятся числа от 0 до 9\n");
}

void print_stdnt(inf_stdnt_t *stdnt, key_tables_t *arr_key, int count_std, int mode)
{
    puts("");
    printf("%-2c | %-6s | %-10.40s | %-10.40s | %-10.10s | %-4s | %-3s | %-5s | %-4s | %-15.40s | %-4s | %-4s |\n", 'N', "type", "second name", "name", "group", "sex", "age", "mark", "year", "street", "N home", "N flat");
    printf("::----------------------------------------------------------------------------------------------------------------::\n");
    for (int j = 0; j < count_std; j++)
    {
        int i = j;
        if (mode)
        {
            i = arr_key[j].index;
        }
        printf("%-2d | %-6s | %-11.40s | %-10.40s | %-10.10s | %-4s | %-3d | %05.3lf | %d |", i + 1, stdnt[i].type_home, stdnt[i].second_name, stdnt[i].name, stdnt[i].group, stdnt[i].gender, stdnt[i].age, stdnt[i].avg_mark, stdnt[i].year_admission);

        if (stdnt[i].item_home == HOME)
            printf(" %-15.40s | %-6d | %-6d |\n", stdnt[i].adress_u.home_t.street, stdnt[i].adress_u.home_t.home, stdnt[i].adress_u.home_t.flat);
        else if (stdnt[i].item_home == HOSTEL)
            printf(" %-15.40s | %-6d | %-6d |\n", "      -", stdnt[i].adress_u.hostel_t.number_hostel, stdnt[i].adress_u.hostel_t.room);
    }
    puts("");
}

void print_stnt_hostel_by_year(inf_stdnt_t *stdnt, int count_std, int year)
{
    puts("");
    printf("%-2c | %-6s | %-10.40s | %-10.40s | %-10.10s | %-4s | %-3s | %-5s | %-4s | %-15.40s | %-4s | %-4s |\n", 'N', "type", "second name", "name", "group", "sex", "age", "mark", "year", "street", "N home", "N flat");
    printf("::----------------------------------------------------------------------------------------------------------------::\n");
    int count = 0;
    for (int i = 0; i < count_std; i++)
    {
        if (year == stdnt[i].year_admission && stdnt[i].item_home == HOSTEL)
        {
            printf("%-2d | %-6s | %-11.40s | %-10.40s | %-10.10s | %-4s | %-3d | %05.3lf | %d |", i + 1, stdnt[i].type_home, stdnt[i].second_name, stdnt[i].name, stdnt[i].group, stdnt[i].gender, stdnt[i].age, stdnt[i].avg_mark, stdnt[i].year_admission);
            count++;
            printf(" %-15.40s | %-6d | %-6d |\n", "      -", stdnt[i].adress_u.hostel_t.number_hostel, stdnt[i].adress_u.hostel_t.room);
        }
    }
    if (count == 0)
        puts("Ни одного подходящего студента");
    puts("");
}
