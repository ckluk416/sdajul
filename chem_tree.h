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


#endif
