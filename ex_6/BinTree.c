#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void generic_function(BinTree *root, void(*task)(void *)) {
    task(root);
}

int generic_int_function(BinTree *root, int(*task)(void *)) {
    return task(root);
}

BinTree *createNode(int id, const char *name, int age, char gender) {
    BinTree *node = (BinTree *) malloc(sizeof(BinTree));
    node->id = id;
    node->name = (char *) calloc(11, sizeof(char));
    strcpy(node->name, name);
    node->age = age;
    node->gender = gender;
    node->task = (strcmp(name, "Moshe") == 0 && gender == 'M') ? moshe_task
                                                               : child_task;
    node->action = node->name;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BinTree *addChild(BinTree *root, int id,
                  const char *name, int age, char gender) {
    if (root == NULL) {
        return createNode(id, name, age, gender);
    }
    if (id < root->id) {
        root->left = addChild(root->left, id, name, age, gender);
    } else if (id > root->id) {
        root->right = addChild(root->right, id, name, age, gender);
    }
    return root;
}

void freeNode(BinTree *node) {
    free(node->name);
    free(node);
}

void freeIsrael(BinTree *root) {
    deleteNodes(root);
    root = NULL;
}

void deleteNodes(BinTree *root) {
    if (root == NULL) return;
    deleteNodes(root->left);
    deleteNodes(root->right);
    freeNode(root);
}

void printChildDetails(BinTree *child) {
    printf("id: %d, name: %s, gender: %c, age: %d\n",
           child->id, child->name, child->gender, child->age);
}

void inorderPrintDetails(BinTree *root) {
    if (root == NULL) {
        return;
    }
    inorderPrintDetails(root->left);
    printChildDetails(root);
    inorderPrintDetails(root->right);
}

void preorderPrintDetails(BinTree *root) {
    if (root == NULL) {
        return;
    }
    printChildDetails(root);
    preorderPrintDetails(root->left);
    preorderPrintDetails(root->right);
}

void postorderPrintDetails(BinTree *root) {
    if (root == NULL) {
        return;
    }
    postorderPrintDetails(root->left);
    postorderPrintDetails(root->right);
    printChildDetails(root);
}

void inorderTask(BinTree *child) {
    if (child == NULL) {
        return;
    }
    inorderTask(child->left);
    child->task(child->action);
    inorderTask(child->right);
}

void preorderTask(BinTree *child) {
    if (child == NULL) {
        return;
    }
    child->task(child->action);
    preorderTask(child->left);
    preorderTask(child->right);
}

void postorderTask(BinTree *child) {
    if (child == NULL) {
        return;
    }
    postorderTask(child->left);
    postorderTask(child->right);
    child->task(child->action);
}

//TODO: DELETE LATER
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
    root->action = root;
    root->left = child->left;
    root->right = child->right;
    return root;
}

BinTree *deleteId(BinTree *root, int id) {
    if (root == NULL) return root;
    if (id < root->id) {
        root->left = deleteId(root->left, id);
    } else if (id > root->id) {
        root->right = deleteId(root->right, id);
    } else {
        // Node found
        if (root->left == NULL) {
            if (root->right != NULL) {
                BinTree *temp = root->right;
                if (root->name != NULL) free(root->name);
                free(root);
                return temp;
            } else {
                if (root->name != NULL) free(root->name);
                free(root);
                root = NULL;
                return root;
            }
        } else if (root->right == NULL) {
            if (root->left != NULL) {
                BinTree *temp = root->left;
                if (root->name != NULL) free(root->name);
                free(root);
                return temp;
            } else {
                if (root->name != NULL) free(root->name);
                free(root);
                return NULL;
            }
        }
        // Node has two children
        BinTree *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->id = temp->id;
        if (root->name != NULL) free(root->name);
        if (temp->name != NULL) {
            root->name = malloc(strlen(temp->name) + 1);
            strcpy(root->name, temp->name);
        } else {
            root->name = NULL;
        }
        root->age = temp->age;
        root->gender = temp->gender;
        root->task = temp->task;
        root->action = root->name;
        root->right = deleteId(root->right, temp->id);
    }
    return root;
}

BinTree *findMoshe(BinTree *root) {
    if (root == NULL) return NULL;
    BinTree *found = findMoshe(root->left);
    if (found != NULL) return found;
    if (root->gender == 'M' && strcmp(root->name, "Moshe") == 0) {
        return root;
    }
    return findMoshe(root->right);
}

int findMen(BinTree *root) {
    if (root == NULL) return -1;
    int id = findMen(root->left);
    if (id != -1) return id;
    if (root->gender == 'M' && strcmp(root->name, "Moshe") != 0) {
        return root->id;
    }
    return findMen(root->right);
}

int findDead(BinTree *root) {
    if (root == NULL) return -1;
    int id = findDead(root->left);
    if (id != -1) return id;
    if (root->age >= 120) {
        return root->id;
    }
    return findDead(root->right);
}

BinTree **deleteDead(BinTree **root) {
    int idToDel = generic_int_function(*root, (void *) (findDead));
    while (idToDel != -1) {
        *root = deleteId(*root, idToDel);
        idToDel = generic_int_function(*root, (void *) (findDead));
    }

    return root;
}

BinTree **deleteMen(BinTree **root) {
    int idToDel = generic_int_function(*root, (void *) (findMen));
    while (idToDel != -1) {
        *root = deleteId(*root, idToDel);
        idToDel = generic_int_function(*root, (void *) (findMen));
    }

    return root;
}

void lookForMoshe(BinTree *root) {
    BinTree *moshe = findMoshe(root);
    if (moshe != NULL) {
        if (moshe->age >= 80) {
            printf("%s say: let my people go!\n", moshe->name);
            generic_function(root, (void *) (freeIsrael));
            exit(0);
        }
    }
}

int getOrder() {
    printf("please choose order:\n"
           "(1) preorder\n"
           "(2) inorder\n"
           "(3) postorder\n");
    int order;
    scanf("%d", &order);
    if (order != 1 && order != 2 && order != 3) {
        printf("wrong order!\n");
        return -1;
    }
    return order;
}

void printAllChildren(BinTree *root) {
    int order = getOrder();
    if (order == -1) {
        return;
    }
    void (*orderFunction[])(BinTree *) = {preorderPrintDetails,
                                          inorderPrintDetails,
                                          postorderPrintDetails};
    generic_function(root, (void *) (orderFunction[order - 1]));
}

int doTask(BinTree *root) {
    int order = getOrder();
    if (order == -1) {
        return 1;
    }
    void
    (*orderFunction[])(BinTree *) = {preorderTask, inorderTask, postorderTask};
    generic_function(root, (void *) (orderFunction[order - 1]));

    return 0;
}

void fuckMoshe(BinTree **root) {
    int wrongOrder = generic_int_function(*root, (void *) (doTask));
    BinTree *found = findMoshe(*root);
    if (found) {
        deleteMen(root);
    } else if (!wrongOrder) {
        printf("Moshe Not Found!\n");
    }
}

void incrementAge(BinTree *root) {
    if (root == NULL) return;
    incrementAge(root->left);
    root->age += 20;
    incrementAge(root->right);
}


int sizeOfJews(BinTree *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + sizeOfJews(root->left)
           + sizeOfJews(root->right);
}

int sizeOfFemale(BinTree *root) {
    if (root == NULL) {
        return 0;
    }
    int isGood = root->gender == 'F' ? 1 : 0;
    return isGood + sizeOfFemale(root->left)
           + sizeOfFemale(root->right);
}

int sizeOfMale(BinTree *root) {
    if (root == NULL) {
        return 0;
    }
    int isGood = root->gender == 'M' ? 1 : 0;
    return isGood + sizeOfMale(root->left)
           + sizeOfMale(root->right);
}

void child_task(void *val) {
    printf("%s cry waaaa\n", (char *) val);
}

void moshe_task(void *val) {
    printf("%s quiet\n", (char *) val);
}