#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define msize 10
typedef struct Record {
    float f1;
    float f2;
    char *str;
} Record;

struct KeySpace1;

typedef struct Item {
    Record *info;
    /* указатель на информацию     */
    int release;
    /* версия элемента      */
    struct Item *next;
    /* указатель на следующий элемент с данным составным ключем */
    int key1;
    char *key2;
} Item;

typedef struct KeySpace1 {
    int key;                 /* ключ элемента    */
    Item *info;              /* указатель на информацию   */
    struct KeySpace1 *next;  /* указатель на следующий элемент  */
} KeySpace1;


typedef struct KeySpace2 {
    char *key;   /* ключ элемента   */
    Item *info;  /* указатель на информацию  */
    int busy;    /* признак занятости элемента  */
} KeySpace2;

typedef struct Table {
    KeySpace1 *ks1;
    /* указатель на первое пространство ключей   */
    KeySpace2 *ks2;
    /* указатель на второе пространство ключей   */
/*также может содержать опциональные поля, ограничивающие размер пространства ключей  */
/*при этом их наличие определяется типом организации соответствующего пространства,   */
/*(см. предыдущие пункт задания):        */

    int msize2;
    /* размер области 2-го пространства ключей    */

/*также может содержать опциональные поля с текущим количеством элементов в пространстве ключей */
/*при этом их наличие определяется типом организации соответствующего пространства,   */
/*(см. предыдущие пункт задания):        */
} Table;

Table *init_table();

void free_table(Table *table);

int add_element(Table *table, int key1, char *key2, Record *record);

void print_table(Table *table);

Table* search_by_key1_range(Table* table, int range_start, int range_end);

Item* search_by_Key1(Table *table, int key1);

void print_item_for_key1(Item *item);

void print_item_for_key2(Item *item);

Item* search_by_Key2(Table *table, char *key2);

int delete_element_by_first_key(Table *table, int key1);

int delete_element_by_second_key(Table *table, char *key2);

int delete_element_by_compose_key(Table *table, int key1, char *key2);

void print_table_by_ks2(Table *table);
