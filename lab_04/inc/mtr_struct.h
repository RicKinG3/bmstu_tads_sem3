#ifndef __MTR_STRUCT_H__
#define __MTR_STRUCT_H__

// Структура для хранения размеров матрицы
typedef struct
{
    int rows;     //Количество строк
    int columns;  //Количество столбцов
    int nonzeros; //Количество ненулевых элементов
} mtr_size_t;

// Структура матрицы в разреженном виде
typedef struct
{
    mtr_size_t sizes; //Размеры матрицы
    int *elements;       // Указатель на массив элементов матрицы
    int *rows;           // Указатель на массив строк, соответсвующих элементам
    int *columns;        // Указатель на массив номеров элементов, с которых начинается столбец
} sparse_mtr_t;

//Структура матрицы в стандарном виде
typedef struct
{
    mtr_size_t sizes; //Размеры матрицы
    int **mtr;        //  Матрица
} mtr_t;

#endif