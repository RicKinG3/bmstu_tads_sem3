#ifndef __STRUCT_INF_STDNT_H__
#define __STRUCT_INF_STDNT_H__

/* вариант 5
Type жилье = (дом, qerg);
Данные:
    Фамилия, имя, группа, пол (м, ж), возраст, средний балл за сессию, дата поступления
адрес:
    дом: (улица, №дома, №кв);
общежитие: (№общ., №комн.);

Ввести общий список студентов.
Вывести список студентов, указанного года поступления, живущих в общежитии
*/
#define MAX_LEN_STR 128
#define MAX_STDNT 5001

typedef enum type_home
{
    HOME,
    HOSTEL
} type_home_t;

typedef struct inf_stdnt
{
    char type_home[MAX_LEN_STR];
    type_home_t item_home;

    char second_name[MAX_LEN_STR];
    char name[MAX_LEN_STR];
    char group[MAX_LEN_STR];
    char gender[MAX_LEN_STR];
    int age;
    double avg_mark;
    int year_admission; // sort by this pool

    union
    {
        struct
        {
            char street[MAX_LEN_STR];
            int home;
            int flat;
        } home_t;
        struct
        {
            int number_hostel;
            int room;
        } hostel_t;
    } adress_u;

} inf_stdnt_t;

typedef struct key_tables
{
    int index;
    int year_admission;
} key_tables_t;

#endif
