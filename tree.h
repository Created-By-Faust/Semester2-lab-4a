#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    unsigned int key;
    char* data;
} Node;

int add_record(Node** root, int key, char* data);

void print_bigger_than_key(Node *node, int key);

char* search_by_key(Node *node, int key);

Node* min_key(Node* node);

int delete_by_key(Node** root, unsigned int key);

void print_tree_wrapper(Node* node);

int load_from_file(Node** tree, char *file);

void free_tree(Node *tree);
