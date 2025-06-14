#include "chem_tree.h"
#include <string.h>
#include <stdlib.h>

// Deklarasi 2 tree secara global to make it always empty 
TreeNode* periodic_tree_by_atomic = NULL;
TreeNode* periodic_tree_by_name = NULL;

// Fungsi perbandingan
int compare_by_atomic_number(const Element* a, const Element* b) {
    return a->atomic_number - b->atomic_number;
}

int compare_by_name(const Element* a, const Element* b) {
    return strcmp(a->name, b->name);
}

TreeNode* create_tree_node(Element elem){
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node){
        new_node->data = elem;
        new_node->left = new_node->right = NULL;
    
    }
    return new_node;
}

TreeNode* insert_to_tree(TreeNode* root, Element elem, CompareFunc compare) {
    if (root == NULL) {
        return create_tree_node(elem);
    
    int cmp = compare(&elem, &root->data);
    if (cmp < 0){
        root->left = insert_to_tree(root->left, elem, compare);
    } else if (cmp > 0){
        root->right = insert_to_tree(root->right, elem, compare);
    }
    
    return root;
}

Element* search_element(TreeNode* root, void* key, CompareFunc compare) {
    if (root == NULL) {
        return NULL;
    }

    
}