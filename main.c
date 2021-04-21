#include "table.h"

int getStr(char *a) {
    int n;
    do {
        n = scanf("%[^\n]", a);
        if (n == 0) {
            printf("Error in input flow, try again\n");
            n = scanf("%[^\n]", a);
        }
    } while (n == 0);
    scanf("%*c");
    if (n < 0) {
        printf("Unknown error.");
        return 1;
    }
    return 0;
}

int getInt(int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            printf("Error in input flow, try again\n");
            scanf("%*s");
        }
    } while (n == 0);
    scanf("%*c");
    if (n < 0) {
        printf("Unknown error.");
        return 1;
    }
    return 0;
}

int getFloat(float *a) {
    int n;
    do {
        n = scanf("%f", a);
        if (n == 0) {
            printf("Error in input flow, try again\n");
            scanf("%*s");
        }
    } while (n == 0);
    scanf("%*c");
    if (n < 0) {
        printf("Unknown error.");
        return 1;
    }
    return 0;
}


int main() {
    char str[256];
    int buf;
    Table *table = init_table();
    do {
        printf("1 - add record to table\n"
               "2 - print table\n"
               "3 - search element by key1\n"
               "4 - search element by key2\n"
               "5 - remove by key1 and key2\n"
               "6 - remove by key1\n"
               "7 - remove by key2\n"
               "8 - search by key1 range\n"
               "0 - exit\n");
        if (getInt(&buf)) {
            return 0;
        }
        switch (buf) {
            case 1:
                printf("Enter first key (int):\n");
                int key1 = 0;
                if (getInt(&key1)) {
                    free_table(table);
                    return 0;
                }
                printf("Enter second key (string):\n");
                if (getStr(str)) {
                    free_table(table);
                    return 0;
                }
                size_t n = strlen(str) + 1;
                char *key2 = malloc(n);
                strncpy(key2, str, n);

                Record *record = malloc(sizeof(Record));

                printf("Enter record property (float):\n");
                if (getFloat(&record->f1)) {
                    free_table(table);
                    return 0;
                }

                printf("Enter record property (float):\n");
                if (getFloat(&record->f2)) {
                    free_table(table);
                    return 0;
                }

                printf("Enter record property (string):\n");
                if (getStr(str)) {
                    free_table(table);
                    return 0;
                }
                size_t len = strlen(str) + 1;
                record->str = malloc(len);
                strncpy(record->str, str, len);

                if (add_element(table, key1, key2, record) < 0) {
                    printf("ERROR\n");
                }
                break;
            case 2:
                printf("Table by 1 keyspace:\n");
                print_table(table);
                break;
            case 3:
                printf("Enter first key (int):\n");
                key1 = 0;
                if (getInt(&key1)) {
                    free_table(table);
                    return 0;
                }

                Item* search_result = search_by_Key1(table, key1);
                if (search_result) {
                    print_item_for_key1(search_result);
                } else {
                    printf("NOT_FOUND\n");
                }
                break;
            case 4:
                printf("Enter second key (string):\n");
                if (getStr(str)) {
                    free_table(table);
                    return 0;
                }
                n = strlen(str) + 1;
                key2 = malloc(n);
                strncpy(key2, str, n);

                Item* result = search_by_Key2(table, key2);
                if (result) {
                    print_item_for_key2(result);
                } else {
                    printf("NOT_FOUND\n");
                }
                break;
            case 5:
                printf("Enter first key (int):\n");
                key1 = 0;
                if (getInt(&key1)) {
                    free_table(table);
                    return 0;
                }

                printf("Enter second key (string):\n");
                if (getStr(str)) {
                    free_table(table);
                    return 0;
                }
                n = strlen(str) + 1;
                key2 = malloc(n);
                strncpy(key2, str, n);

                if (delete_element_by_compose_key(table, key1, key2) < 0)
                    printf("NOT_FOUND\n");
                break;
            case 6:
                printf("Enter first key (int):\n");
                key1 = 0;
                if (getInt(&key1)) {
                    free_table(table);
                    return 0;
                }
                if (delete_element_by_first_key(table, key1) < 0)
                    printf("NOT FOUND\n");
                break;
            case 7:
                printf("Enter second key (string):\n");
                if (getStr(str)) {
                    free_table(table);
                    return 0;
                }
                n = strlen(str) + 1;
                key2 = malloc(n);
                strncpy(key2, str, n);
                if (delete_element_by_second_key(table, key2) < 0)
                    printf("NOT FOUND\n");
                break;
            case 8:
                printf("Enter range start (int):\n");
                int range_start = 0;
                if (getInt(&range_start)) {
                    free_table(table);
                    return 0;
                }
                printf("Enter range end (int, inclusive):\n");
                int range_end = 0;
                if (getInt(&range_end)) {
                    free_table(table);
                    return 0;
                }

                Table* range_search_result = search_by_key1_range(table, range_start, range_end);
                if (range_search_result->ks1) {
                    print_table(range_search_result);
                } else {
                    printf("NOT FOUND\n");
                }
                free_table(range_search_result);
                break;
            case 9:
                printf("Table by 2 keyspace:\n");
                print_table_by_ks2(table);
                break;
            case 0:
                free_table(table);
                return 0;
            default:
                printf("Undef command!\n");
                break;
        }
        printf("\n");
    } while (1);
}
