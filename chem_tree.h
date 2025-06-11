#ifndef CHEM_TREE_H
#define CHEM_TREE_H

#include "element.h"


// Struct for tabel priodik storage
typedef struct TreeNode {
    Element data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function pointer untuk comparator
typedef int (*CompareFunc)(const Element*, const Element*);

// Function prototype interface
TreeNode* create_tree_node(Element elem);
TreeNode* insert_to_tree(TreeNode* root, Element elem, CompareFunc compare);
Element* search_element(TreeNode* root, void* key, CompareFunc compare);
// Buld 2 different tree based on the atomic number/name
Element* search_by_atmnumb(int atomic_number);
Element* search_by_name(char* name);


void build_periodic_tree(TreeNode** tree_by_atomic, TreeNode** tree_by_name, const Element* table, int count);
void process_inorder(TreeNode* root);
void print_tree_table(TreeNode* root);
void free_tree(TreeNode* root);

#endif
