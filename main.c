#include "tree.h"

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
    char *fin_str;
    int buf, key;
    size_t len;
    Node *tree = 0, *node;
    do {
        printf("1 - add record to table\n"
               "2 - print bigger then key (in desc order)\n"
               "3 - search by key\n"
               "4 - search min key\n"
               "5 - delete by key\n"
               "6 - load from file\n"
               "7 - print tree\n"
               "0 - exit\n");
        if (getInt(&buf)) {
            free_tree(tree);
            return 0;
        }
        switch (buf) {
            case 1:
                printf("Enter key (int):\n");
                if (getInt(&key)) {
                    free_tree(tree);
                    return 0;
                }
                printf("Enter data (string):\n");
                if (getStr(str)) {
                    free_tree(tree);
                    return 0;
                }
                len = strlen(str) + 1;
                fin_str = malloc(len);
                strncpy(fin_str, str, len);
                if (add_record(&tree, key, fin_str) < 0) {
                    printf("ERROR");
                }
                free(fin_str);
                break;
            case 2:
                printf("Enter key (int):\n");
                if (getInt(&key)) {
                    free_tree(tree);
                    return 0;
                }
                print_bigger_than_key(tree, key);
                break;
            case 3:
                printf("Enter key (int):\n");
                if (getInt(&key)) {
                    free_tree(tree);
                    return 0;
                }
                char *result = search_by_key(tree, key);
                if (result) {
                    printf("FOUND: %s\n", result);
                } else {
                    printf("KEY NOT FOUND\n");
                }
                break;
            case 4:
                node = min_key(tree);
                if (node) {
                    printf("MIN KEY == %d, DATA == %s\n", node->key, node->data);
                } else {
                    printf("TREE IS EMPTY\n");
                }
                break;
            case 5:
                printf("Enter key (int):\n");
                if (getInt(&key)) {
                    free_tree(tree);
                    return 0;
                }
                if (delete_by_key(&tree, key) < 0) {
                    printf("KEY NOT FOUND\n");
                }
                break;
            case 6:
                printf("Enter filename:\n");
                if (getStr(str)) {
                    free_tree(tree);
                    return 0;
                }
                len = strlen(str) + 1;
                fin_str = malloc(len);
                strncpy(fin_str, str, len);
                if (load_from_file(&tree, fin_str) < 0) {
                    printf("ERROR\n");
                }
                free(fin_str);
                break;
            case 7:
                print_tree_wrapper(tree);
                break;
            case 0:
                free_tree(tree);
                return 0;
            default:
                printf("Undef command!\n");
                break;
        }
        printf("\n");
    } while (1);
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
