<!-- pandoc --pdf-engine=context -V mainfont="CMU Serif" -V monofont="CMU Typewriter Text"  -V geometry:a4paper -V documentclass=article -o report_Volnyga_Maxim_IU7-36.pdf markdown.md -->
### Описание условия

Разработать программу работы со стеком, реализующую операции добавления и
удаления элементов из стека и отображения текущего состояния стека. Реализовать
стек: а) массивом; б) списком.

Все стандартные операции со стеком должны быть оформлены отдельными
подпрограммами. В случае реализации стека в виде списка при отображении
текущего состояния стека предусмотреть возможность просмотра адресов
элементов стека и создания дополнительного собственного списка свободных
областей (адресов освобождаемой памяти при удалении элемента, который
можно реализовать как списком, так и массивом) с выводом его на экран.
Список свободных областей необходим для того, чтобы проследить, каким
образом происходит выделение памяти менеджером памяти при запросах на
нее и убедиться в возникновении или отсутствии фрагментации памяти.

Ввести арифметическое выражение типа:
число|знак| ... число|знак| число
Числа целые. Вычислить значение выражения
Доступные операции: «+» - сложить
«-» - вычесть
«*» - умножить
«/» - разделить

### Описание ТЗ

#### Описание исходных данных и результатов:

(типы, форматы, точность, способ передачи, ограничения)
Программа получает на вход:

Целое число для выбора ввода меню [0, 12]

Вывод результата: 

1. Стек в виде списка
2. Стек в виде массива 
3. Результат вычисления выражения в виде списка
4. Результат вычисления выражения в виде массива 
5. Замеры времени и памяти  
6. Массив освободившихся адрессов 
7. Сообщение об ошибке (при ее возникновении)

#### Описание задачи, реализуемой программой

Программа предоставляет работу с стеками в виде массива или списка, а именно: 

Меню:  

Стек в виде массива:
1. Записать несколько элементов в стек
2. Добавить один элемент в стек
3. Удалить элемент из стека
4. Вывести текущее состояние стека
5. Произвести вычисление и вывести результат на экран
6. Вывести замеры времени и памяти         

Стек в виде списка:
7.  Записать несколько элементов в стек
8.  Добавить один элемент в стек
9.  Удалить элемент из стека
10. Вывести текущее состояние стека
11. Произвести вычисление и вывести результат на экран
12. Распечатать массив освободившихся адресов
     

#### Способ обращения к программе

Запускается через терминал командой ./app.exe
Обращение к программе происходит путём консольного ввода.

#### Описание возможных аварийных ситуаций и ошибок пользователя

Аварийные ситуации:

1. Неверно введен пункт меню (не целое число или число меньшее 0 или больше 12)
2. Неверно введен символ при вводе выражения (не целое число или не знак)
3. Первый символ в выражении знак (+,-,*,/)
4. Последний символ в выражении знак (+,-,*,/)
5. Максимальный размер стека (массива / списка ) введен неверно (не целое число или число меньшее 1 или большее 10000)
6. Переполнение стека (достигнута граница стека)
7. Неверно введено число при добавлении элемента в стек (не целое число)
8. Неверно введено число элементов для добавления в стек (не целое число или число меньшее 1 или большее максимальной величины стека)
9. Неверно введено выражение (введен пробел между операндами) 


### Описание внутренних СД

### Структура стека, реализованного в виде массива
```c
typedef struct arr
{
    int *arr; //указатель на текущий элемент стека
    int len; //количество элементов в стеке
} arr_t;

```
### Структура стека, реализованного в виде списка
```c

typedef struct list
{
    int ind; //номер элемента в стеке
    int num; //значение текущего элемента в стеке

    struct list *next; //указатель на следующий элемент стека
} list_t;

```
### Описание алгоритма

Основной алгоритм - произведение вычисление с использованием стека в виде списка и массива:

(стек чисел = СЧ, стек знаков = СЗ)

Добавление знака в СЗ
* 1. стек пуст
* 2. знак имеет приоритет больше, чем последний знак в стеке

Производим вычисление операции если:
* 1.  операция имеет приоритет меньше или равный, чем крайняя
    * 1. достаем из СЧ последнии два числа
    * 2. достаем предпоследнюю операцию  из СЗ
    * 3. результат операции кладем в СЧ 

Пример: 1 + 2 * 3 + 4 - 5/5 
1) добавить 1 в СЧ (1)
2) добавить + в СЗ (+)
3) добавить 2 в СЧ (1 2)
4) добавить * в СЗ (приоритет выше) (+ *)
5) добавить 3 в СЧ  (1 2 3)
6) (+) имеет приоритет ниже чем * ==> производим умножение (достаем 2 последних числа из СЧ и операцию * из СЗ) 2 * 3 = 6 
7) добавить результат вычисления  6 в СЧ (1 6)
8) добавить + в СЗ (+ +)
9) Так как в СЗ (+ +) две одинаковые операции ==> производим операцию (достаем 2 последних числа из СЧ и операцию + из СЗ) 1 + 6 = 7
10) добавить результат вычисления в СЧ (7)
11) добавить 4 в СЧ (7 4)
12) добавить - в СЗ (+ -)
13) добавить 5 в СЧ (7 4 5)
14) добавить / в СЗ (+ - /)
15) добавить 5 в СЧ (7 4 5 5)
16) так как больше нет эл идем с конца 
17) 5 / 5 = 1 (достаем 2 последних числа из СЧ и операцию из СЗ), добавляем результат в СЧ) (7 4 1) (+ -)
18) 4 - 1 = 3  (достаем 2 последних числа из СЧ и операцию из СЗ), добавляем результат в СЧ) (7 3) (+)
19) 7 + 3 = 10  (достаем 2 последних числа из СЧ и операцию из СЗ), добавляем результат в СЧ) (10) ()
20) в СЧ один эл, а в СЗ 0 ==> вычисление произведено


### Набор тестов с указанием проверяемого параметра
#### Позитивные тесты для 1./7Записать несколько элементов в стек в виде массива

| Ввод| Вывод| Что|
| --- | --- | --- |
| размер стека = 10 эл, кол-во эл = 5 эл: 5 1 2 3 4 5 | Стек массивом успешно создан | проверка заполнение стека (5 4 3 2 1) | 
| размер стека = 1 эл, кол-во эл = 1 эл: 1 | Стек массивом успешно создан |проверка заполнение стека  стек (1) |

#### Негативные тесты для 1./7Записать несколько элементов в стек в виде массива

| Ввод| Вывод| Что|
| --- | --- | --- |
| размер стека = 10 эл, кол-во эл = 11 | Ошибка: неверно введено количество элементов в стеке | проверка ввода ко-ва эл размер стека < кол-во эл |
| размер стека = 10 эл, кол-во эл = 0 | Ошибка: неверно введено количество элементов в стеке |  проверка  ко-ва эл кол-во эл = 0| 
| размер стека = -10 эл| Ошибка: размер стека это целое число, ∈ [1, 10000] | проверка  размера стека | 
| размер стека = 10000000 эл| Ошибка: размер стека это целое число, ∈ [1, 10000] |  проверка размера стека |
| размер стека = строка(qwe) | Ошибка: размер стека это целое число, ∈ [1, 10000] | размера ввода размера стека | 
| размер стека = 1 кол-во эл = строка(qwe) | Ошибка: неверно введено количество элементов в стеке | проверка  ко-ва эл кол-во эл | 
| размер стека = 10 эл, кол-во эл = 1 эл: stroka | Ошибка: крайний элемент был введен неверно, повторите попытку | проверка ввода элемента стека |
| размер стека = 1 эл, кол-во эл = 1 эл: 1.4 | Ошибка: крайний элемент был введен неверно, повторите попытку | проверка ввода элемента стека |


#### Позитивные тесты для 2./8 Добавить один элемент в стек

| Ввод| Вывод| Что|
| --- | --- | --- |
| размер стека = 1 эл, эл: 5 | Элемент успешно добавлен | проверка заполнение стека (5) | 
| размер стека = 12 эл, эл: 5 | Элемент успешно добавлен | проверка заполнение стека (5) | 

#### Негативные тесты для  2./8 Добавить один элемент в стек
| Ввод| Вывод| Что|
| --- | --- | --- |
| размер стека = 1 эл, эл: строка(qwe) | Ошибка: неверно введен элемент для добавления | проверка ввода  эл стека |
| размер стека = 1 эл, эл: 13.5 | Ошибка: неверно введен элемент для добавления | проверка ввода  эл стека |
| размер стека = 1 эл, в стеке уже есть 1 эл | Ошибка: стек переполнен | проверка переполнение стека |


#### Позитивные тесты для 3./9 Удалить элемент из стека

| Ввод| Вывод| Что|
| --- | --- | --- |
| размер стека = 2 эл, (1 5) | Элемент удален | проверка удаление эл из стека  (1) | 
| размер стека = 1 эл, (1) | Элемент удален | проверка удаление эл из стека () | 

#### Негативные тесты для  3./9 Удалить элемент из стека и 4. Вывести текущее состояние стека
| Ввод| Вывод| Что|
| --- | --- | --- |
| размер стека = 0 эл | Стек пуст  | проверка удаление эл из пустого  стека |
| размер стека = 0 эл | Стек пуст  | вывода пустого стека |

#### Позитивные тесты для 5./11 Произвести вычисление и вывести результат на экран

| Ввод| Вывод| Что|
| --- | --- | --- |
| 1+2*3+4-5/5 | Результат вычисления выражения: 10 | проверка вычисление выражения | 
| 1+1 | Результат вычисления выражения: 2 | проверка вычисление выражения | 

#### Негативные тесты для  5./11 Произвести вычисление и вывести результат на экран

| Ввод| Вывод| Что|
| --- | --- | --- |
| строка(qwe) | Ошибка: неверный символ в выражении | проверка ввода  выражения | 
| 1.5*8 | Ошибка: неверный символ в выражении | проверка ввода  выражения  | 
| -7*8 | Ошибка: первым должно быть введено число | проверка ввода  выражения  | 
| 7*8- | Ошибка: последним должно быть введено число | проверка ввода  выражения  | 
| 7+-8 | Ошибка: не может быть введено несколько знаков подряд | проверка ввода  выражения  | 
| 7++8 | Ошибка: не может быть введено несколько знаков подряд | проверка ввода  выражения  | 
| 7+qwe | Ошибка: неверный символ в выражении | проверка ввода  выражения  | 


### Оценка эффективности

```
В стеках по 10 элементов
Замеры добавления элемента

МАССИВ: 0.0000000769 секунд
СПИСОК: 0.0000002391 секунд

Замеры удаления элемента

МАССИВ: 0.0000000680 секунд
СПИСОК: 0.0000002251 секунд

Замеры вычисления выражения

МАССИВ: 0.0000016789 секунд
СПИСОК: 0.0000019826 секунд

Кол-во памяти для 10 элементов:         
Массив: 48 байт        
Список: 160 байт
```
```
В стеках по 100 элементов
Замеры добавления элемента

МАССИВ: 0.0000006623 секунд
СПИСОК: 0.0000027131 секунд

Замеры удаления элемента

МАССИВ: 0.0000006874 секунд
СПИСОК: 0.0000027394 секунд

Замеры вычисления выражения

МАССИВ: 0.0000165414 секунд
СПИСОК: 0.0000217506 секунд

Кол-во памяти для 100 элементов:         
Массив: 408 байт        
Список: 1600 байт
```

```
В стеках по 1000 элементов
Замеры добавления элемента

МАССИВ: 0.0000068389 секунд
СПИСОК: 0.0000291094 секунд

Замеры удаления элемента

МАССИВ: 0.0000038654 секунд
СПИСОК: 0.0000157189 секунд

Замеры вычисления выражения

МАССИВ: 0.0000836829 секунд
СПИСОК: 0.0001120146 секунд

Кол-во памяти для 1000 элементов:         
Массив: 4008 байт        
Список: 16000 байт
```

### Выводы по проделанной работе

Структура стека в виде массива с одним элементов занимает 48 Байт, а структура стека в виде списка 160Б ==> стек в виде массива выигрывает по памяти  в 4* раза, потому что списку кроме хранение самого элемента необходимо хранить указатель на следующий элемент списка. При этом скорость работы с элементами списка так же отстает от массива, при удалении в 3* раза, при добавлении в 4* раз, при подсчете выражения 1.3* (* - примерно). Из этого я сделал вывод, что если мне потребуется реализовать стек, то я буду использовать стек в виде массива (динамического)

### Ответы на вопросы

1. Что такое стек?

Стек – это последовательный список с переменной длиной, в котором
включение и исключение элементов происходит только с одной стороны – с его вершины, организованных по принципу LIFO 

2. Каким образом и сколько памяти выделяется под хранение стека
при различной его реализации?

Если хранить как массив — либо в куче если динамический, либо на стеке если статический
Если хранить стек как список, память выделяется в куче.  Для списка выделяется на 4 или 8 байт (в зависимости от операционной системы) больше, чем для массива, это связанно из-за того, что списку необходимо хранить еще указатель на след структуру.

3. Каким образом освобождается память при удалении элемента стека

при различной реализации стека?
Если хранить стек как массив (статический), то смещается только указатель на начало стека
Если хранить стек как список, то верхний элемент удаляется при помощи операции освобождения памяти для него и смещением указателя, который указывает на начало стека

4. Что происходит с элементами стека при его просмотре?

При просмотре стека мы имеем возможность добраться только до верхушки стека. 

5. Каким образом эффективнее реализовывать стек? От чего это
зависит?

Стек эффективнее реализовать с помощью массива, так как он выигрывает в количестве занимаемой памяти  и во времени обработки стека
так как при добавление новых элементов приходится выделять новую память под эти элементы, чтобы выделить память ее нужно сначала найти, что существенно сказывается на времени работы.