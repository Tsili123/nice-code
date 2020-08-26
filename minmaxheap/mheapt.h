#ifndef MHEAPT_H
#define MHEAPT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNode{

    char* disease;
    int counter;
    struct HeapNode* child_a;
    struct HeapNode* child_b;
    struct HeapNode* parent;

}HeapNode;

typedef struct HeapTree{

    HeapNode *root;
    HeapNode *next_free;
    HeapNode *last_node;
    int h;

}HeapTree;


HeapTree* new_heap_tree();
HeapNode* new_node(HeapTree* tree, char* disease, int counter);
HeapNode* search_tree(HeapNode * root, char* disease);
void swap_up(HeapNode* node);
HeapNode* findfreeparent(HeapTree* tree);
HeapNode* find_parent(HeapNode* node, int height);
void printPreorder(HeapNode* node);

#endif
