#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void printChildDetails(BinTree *child) {
    printf("id: %d, name: %s, gender: %c, age: %d\n",
           child->id, child->name, child->gender, child->age);
}

void inorder(BinTree *child) {
    if (child == NULL) {
        return;
    }
    inorder(child->left);
    printChildDetails(child);
    inorder(child->right);
}

void preorder(BinTree *child) {
    if (child == NULL) {
        return;
    }
    printChildDetails(child);
    preorder(child->left);
    preorder(child->right);
}

void postorder(BinTree *child) {
    if (child == NULL) {
        return;
    }
    postorder(child->left);
    postorder(child->right);
    printChildDetails(child);
}

BinTree *createBinTree(BinTree *child) {
    BinTree *root = (BinTree *) malloc(sizeof(BinTree));
    root->name = (char *) malloc(sizeof(char) * strlen(child->name));
    if (root == NULL) {
        return NULL;
    }

    root->id = child->id;
    strcpy(root->name, child->name);
    root->age = child->age; // maybe initialize this to 0
    root->gender = child->gender;
    root->task = child->task;
    root->action = child->action;
    root->left = child->left;
    root->right = child->right;
    return root;
}

Result addToBinTree(BinTree *root, BinTree *child) {
//    if (root == NULL) {
//        return FAILURE;
//    }
    if (root->id > child->id) {
        if (root->left != NULL) {
            return addToBinTree(root->left, child);
        }
        root->left = createBinTree(child);
        if (root->left == NULL) {
            return MEM_ERROR;
        } else {
            return SUCEESS;
        }
    }
    if (root->id < child->id) {
        if (root->right != NULL) {
            return addToBinTree(root->right, child);
        }
        root->right = createBinTree(child);
        if (root->right == NULL) {
            return MEM_ERROR;
        } else {
            return SUCEESS;
        }
    }
    return FAILURE;
}

void destroyBinTree(BinTree *root) {
    if (root == NULL) {
        return;
    }
    destroyBinTree(root->left);
    destroyBinTree(root->right);
    free(root);
}

BinTree *findInBinTree(BinTree *root, BinTree *child) {
    if (root == NULL) {
        return NULL;
    }
    if (root->id > child->id) {
        return findInBinTree(root->left, child);
    }
    if (root->id < child->id) {
        return findInBinTree(root->right, child);
    }
    return root;
}

int sizeOfBinTree(BinTree *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + sizeOfBinTree(root->left)
           + sizeOfBinTree(root->right);
}

void child_task(void *val) {
    printf("%s cry waaaa", (*(BinTree *) val).name);
}

void moshe_task(void *val) {
    printf("%s quiet", (*(BinTree *) val).name);
}