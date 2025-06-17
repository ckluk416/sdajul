#include "chem_tree.h"
#include <string.h>
#include <stdlib.h>

TreeNode* create_tree_node(Element elem) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) {
        printf("Error: malloc failed!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = elem;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Insert element to BST by atomic number
TreeNode* insert_to_tree(TreeNode* root, Element elem) {
    if (root == NULL) return create_tree_node(elem);
    if (elem.atomic_number < root->data.atomic_number)
        root->left = insert_to_tree(root->left, elem);
    else if (elem.atomic_number > root->data.atomic_number)
        root->right = insert_to_tree(root->right, elem);
    return root;
}

// Search element by atomic number
Element* search_element(TreeNode* root, int atomic_number) {
    if (root == NULL) return NULL;
    if (atomic_number == root->data.atomic_number)
        return &(root->data);
    else if (atomic_number < root->data.atomic_number)
        return search_element(root->left, atomic_number);
    else
        return search_element(root->right, atomic_number);
}

// Build tree from table
void build_periodic_tree(TreeNode** root, Element* table, int count) {
    for (int i = 0; i < count; i++) {
        *root = insert_to_tree(*root, table[i]);
    }
}

// Process inorder to print sorted tree
void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%3d | %-3s | %-11s | %8.3f | %6d | %5d\n",
               root->data.atomic_number,
               root->data.symbol,
               root->data.name,
               root->data.atomic_weight,
               root->data.period,
               root->data.group);
        inorder_traversal(root->right);
    }
}
