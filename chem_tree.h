#ifndef CHEM_TREE_H
#define CHEM_TREE_H

#include "element.h"

// Struct for tabel priodik storage
typedef struct TreeNode {
    Element data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function prototype interface
TreeNode* create_tree_node(Element elem);
TreeNode* insert_to_tree(TreeNode* root, Element elem);
Element* search_element(TreeNode* root, int atomic_number);
void build_periodic_tree(TreeNode** root, Element* table, int count);

#endif
