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
