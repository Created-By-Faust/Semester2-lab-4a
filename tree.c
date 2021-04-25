#include "tree.h"

int add_record_wr(Node **root, int key, char *data, Node *parent) {
    if (*root == 0) {
        *root = malloc(sizeof(Node));
        Node *elem = *root;
        elem->key = key;
        elem->data = data;
        elem->parent = parent;
        elem->left = 0;
        elem->right = 0;
        return 0;
    } else {
        if (key > (*root)->key)
            return add_record_wr(&(*root)->right, key, data, *root);
        else if (key < (*root)->key)
            return add_record_wr(&(*root)->left, key, data, *root);
        else
            return -1;
    }
}

int add_record(Node **root, int key, char *data) {
    return add_record_wr(root, key, data, 0);
}

void print_bigger_than_key(Node *node, int key) {
    if (node) {
        print_bigger_than_key(node->right, key);
        if (node->key > key) {
            printf("%d %s\n", node->key, node->data);
            print_bigger_than_key(node->left, key);
        }
    }
}

char *search_by_key(Node *node, int key) {
    if (node) {
        if (key > node->key)
            return search_by_key(node->right, key);
        else if (key < node->key)
            return search_by_key(node->left, key);
        else
            return node->data;
    } else {
        return 0;
    }
}

Node *min_key(Node *node) {
    if (node) {
        if (node->left) {
            return min_key(node->left);
        } else {
            return node;
        }
    } else {
        return 0;
    }
}

Node *minimum(Node *parent) {
    if (parent->left) {
        return parent->left;
    } else if (parent->right) {
        return parent->right;
    } else {
        return parent;
    }
}

int delete_by_key(Node **root, unsigned int key) {
    if (*root) {
        if (key < (*root)->key)
            return delete_by_key(&(*root)->left, key);
        else if (key > (*root)->key)
            return delete_by_key(&(*root)->right, key);
        else if ((*root)->left && (*root)->right) {
            Node *node = minimum((*root)->right);
            (*root)->key = node->key;
            free((*root)->data);
            (*root)->data = node->data;
            return delete_by_key(&(*root)->right, (*root)->key);
        } else {
            if ((*root)->left) {
                *root = (*root)->left;
            } else if ((*root)->right) {
                *root = (*root)->right;
            } else {
                free(*root);
                *root = 0;
            }
            return 0;
        }
    } else {
        return -1;
    }
}

void print_tree(Node *node, int depth) {
    if (node) {
        print_tree(node->right, depth + 1);
        for (int i = 0; i < depth; ++i)
            printf("\t");
        printf("%d (%s)\n", node->key, node->data);
        print_tree(node->left, depth + 1);
    }
}

void print_tree_wrapper(Node *node) {
    print_tree(node, 0);
}

int load_from_file(Node **tree, char *file) {
    FILE *fp = fopen(file, "r");
    int wait_for_index = 1;
    int index;
    char *line = 0;
    size_t len = 0;
    ssize_t read;
    if (!fp)
        return -1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        if (wait_for_index) {
            wait_for_index = 0;
            long index_l = strtol(line, 0, 10);
            index = (int) index_l;
        } else {
            wait_for_index = 1;
            if (line[read - 1] != '\n' && line[read - 1] != '\r')
                read++;
            char *data = malloc(read);
            strncpy(data, line, read);
            data[read - 1] = 0;
            if (add_record(tree, index, data) < 0) {
                free(data);
            }
            len = 0;
        }
        free(line);
        line = 0;
    }
    free(line);
    fclose(fp);
    return 0;
}

void free_tree(Node *tree) {
    if (tree) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree->data);
        free(tree);
    }
}
KeySpace2 *search(KeySpace2 *ptable, int size, char *k) {
    int strt, i, h = 1; /* шаг перемешивания */
    /* вычисление исходной позиции таблицы */

    unsigned char *k_unsigned = (unsigned char *) k;
    strt = i = hash(k_unsigned, size);

    while (ptable[i].busy >= 0) { /* позиция не свободна */
        if (ptable[i].busy > 0 && !strcmp(ptable[i].key, k))
            return &ptable[i]; /* элемент найден */
        i = (i + h) % size; /* следующая позиция */
        if (i == strt)
            break;
    }

    return 0;
}

int add_element_to_keySpace2(KeySpace2 *keySpace2, int keySpace2_size, char *key2, Item *item) {
    int strt, i, h = 1; /* шаг перемешивания */

    /* вычисление исходной позиции таблицы */
    unsigned char *key2_uc = (unsigned char *) key2;
    strt = i = hash(key2_uc, keySpace2_size);

    while (keySpace2[i].busy > 0) { /* позиция занята */
        char *dbKey = keySpace2[i].key;
        if (!strcmp(dbKey, key2)) {
            return -1; /* элемент с заданным ключом есть в таблице */
        }
        i = (i + h) % keySpace2_size; /* следующая позиция */
        if (i == strt)
            return -2; /* вернулись в исходную позицию - таблица полна */
    }

    /* занесение нового элемента */
    keySpace2[i].key = key2;
    keySpace2[i].busy = 1;
    keySpace2[i].info = item;

    return 0;
}

int add_element(Table *table, int key1, char *key2, Record *record) {
    Item *newItem = malloc(sizeof(Item));
    newItem->release = 1;
    newItem->next = 0;
    newItem->info = record;
    newItem->key1 = key1;
    newItem->key2 = key2;

    KeySpace2 *result = search(table->ks2, table->msize2, key2);
    if (result && result->info->key1 == key1) {
        // Добавить версию
        Item *info_iter = result->info;
        newItem->release = info_iter->release + 1;
        newItem->next = info_iter;
        result->info = newItem;
        KeySpace1* iter;
        for (iter = table->ks1; iter; iter = iter->next) {
            if (iter->key == key1) {
                iter->info = newItem;
            }
        }
    } else if (result) {
        // Второй ключ есть, первого нет -> Ошибка
        free(newItem);
        return -1;
    } else {
        // Второго ключа нет в таблице
        // Проверяем, есть ли первый ключ
        // Если есть -> Ошибка
        // Если нет -> Создаём элемент
        if (!table->ks1) {
            table->ks1 = malloc(sizeof(KeySpace1));
            KeySpace1 *keySpace1 = table->ks1;
            keySpace1->key = key1;
            keySpace1->info = newItem;
            keySpace1->next = 0;
            add_element_to_keySpace2(table->ks2, table->msize2, key2, newItem);
        } else {
            KeySpace1 *prev = table->ks1;
            for (KeySpace1 *iter = table->ks1; iter; prev = iter, iter = iter->next) {
                if (iter->key == key1) {
                    free(newItem);
                    return -1;
                }
            }

            prev->next = malloc(sizeof(KeySpace1));
            KeySpace1 *newElem = prev->next;
            newElem->next = 0;
            newElem->key = key1;
            newElem->info = newItem;
            add_element_to_keySpace2(table->ks2, table->msize2, key2, newItem);
        }
    }

    return 0;
}

void free_all_versions(Item *item) {
    Item *tmp;

    while (item != 0) {
        tmp = item;
        item = item->next;
        free(tmp->info->str);
        free(tmp->info);
        free(tmp->key2);
        free(tmp);
    }
}

void free_keySpace1(KeySpace1 *item) {
    KeySpace1 *tmp;

    while (item != 0) {
        tmp = item;
        item = item->next;
        free(tmp);
    }
}

void free_keySpace2(KeySpace2 *keySpace2, int size) {
    for (int i = 0; i < size; ++i) {
        if (keySpace2[i].busy == 1) {
            free_all_versions(keySpace2[i].info);
        }
    }
    free(keySpace2);
}

void free_table(Table *table) {
    free_keySpace1(table->ks1);
    free_keySpace2(table->ks2, table->msize2);
    free(table);
}

void print_all_versions(Item *item) {
    for (Item *item_iter = item; item_iter; item_iter = item_iter->next) {
        Record *record = item_iter->info;
        printf("(%f, %f, %s)\t", record->f1, record->f2, record->str);
    }
}

void print_item_for_key1(Item *item) {
    printf("%d\t|\t%s\t|\tv%d\t", item->key1, item->key2, item->release);
    print_all_versions(item);
    printf("\n");
}

void print_item_for_key2(Item *item) {
    printf("%s\t|\t%d\t|\tv%d\t", item->key2, item->key1, item->release);
    print_all_versions(item);
    printf("\n");
}

Item *search_by_Key1(Table *table, int key1) {
    for (KeySpace1 *iter = table->ks1; iter; iter = iter->next) {
        if (iter->key == key1) {
            return iter->info;
        }
    }
    return 0;
}

Item *search_by_Key2(Table *table, char *key2) {
    KeySpace2 *keySpace2_elem = search(table->ks2, table->msize2, key2);
    if (keySpace2_elem) {
        return keySpace2_elem->info;
    } else {
        return 0;
    }
}

void print_table(Table *table) {
    for (KeySpace1 *iter = table->ks1; iter; iter = iter->next) {
        print_item_for_key1(iter->info);
    }
}

void print_table_by_ks2(Table *table) {
    for (KeySpace2 *iter = table->ks2; *iter != "\n"; *iter++) {
        print_item_for_key2(*iter);
    }
}

int delete_element_by_first_key(Table *table, int key1) {
    KeySpace1 *prev = table->ks1;
    int i = 0;
    for (KeySpace1 *iter = table->ks1; iter; prev = iter, iter = iter->next, i++) {
        if (iter->key == key1) {
            print_item_for_key1(iter->info);
            if (i == 0) {
                table->ks1 = iter->next;
            } else {
                prev->next = iter->next;
            }

            KeySpace2 *ks2Elem = search(table->ks2, table->msize2, iter->info->key2);
            if (ks2Elem) {
                ks2Elem->busy = 0;
                ks2Elem->info = 0;
                ks2Elem->key = 0;
            }

            free_all_versions(iter->info);
            free(iter);
            return 0;
        }
    }
    return -1;
}

int delete_element_by_second_key(Table *table, char *key2) {
    KeySpace2 *ks2Elem = search(table->ks2, table->msize2, key2);
    if (ks2Elem) {
        int key1 = ks2Elem->info->key1;
        return delete_element_by_first_key(table, key1);
    } else {
        return -1;
    }
}

int delete_element_by_compose_key(Table *table, int key1, char *key2) {
    KeySpace2 *item = search(table->ks2, table->msize2, key2);
    if (item && item->info->key1 == key1) {
        delete_element_by_first_key(table, key1);
        return 0;
    }
    return -1;
}

Table *search_by_key1_range(Table *table, int range_start, int range_end) {
    KeySpace1 *keySpace1 = table->ks1;
    Table *result = init_table();
    for (KeySpace1 *iter = keySpace1; iter; iter = iter->next) {
        if (range_start <= iter->key && iter->key <= range_end) {
            Item *item = iter->info;
            for (Item *item_iter = item; item_iter; item_iter = item_iter->next) {
                size_t key2_len = strlen(item->key2) + 1;
                char *key2_copy = malloc(key2_len);
                strncpy(key2_copy, item->key2, key2_len);

                Record *record_copy = malloc(sizeof(Record));
                memcpy(record_copy, item->info, sizeof(Record));

                size_t str_data_len = strlen(record_copy->str) + 1;
                char *str_data_copy = malloc(str_data_len);
                strncpy(str_data_copy, record_copy->str, str_data_len);
                record_copy->str = str_data_copy;

                add_element(result, item->key1, key2_copy, record_copy);
            }
        }
    }
    return result;
}
