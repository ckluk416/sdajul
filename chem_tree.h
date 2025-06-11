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
Element* search_by_atmnumb(TreeNode* root, int atomic_number);
Element* search_by_name(TreeNode* root, char* name);
void build_periodic_tree(TreeNode** root, Element* table, int count);
void process_inorder(TreeNode* root);
void print_tree_table(TreeNode* root);
void free_tree(TreeNode* root);

#endif
