#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinTree.h"

static BinTree* root = NULL;

void printMenu() {
    printf("please choose an action\n"
           "(1) A child was born\n"
           "(2) Throw into the Nile\n"
           "(3) Find Moshe\n"
           "(4) Print All\n"
           "(5) Size of jews\n"
           "(6) Exit\n");
}

enum Options {
    BORN_CHILD = 1,
    THROW_INTO_NILE,
    FIND_MOSHE,
    PRINT_ALL,
    SIZE_JEWS,
    EXIT,
};

BinTree* createNode(int id, const char* name, int age, char gender, void (*task)(void* val)) {
    BinTree* node = (BinTree*)malloc(sizeof(BinTree));
    node->id = id;
    node->name = strdup(name);
    node->age = age;
    node->gender = gender;
    node->task = task;
    node->action = node->name;
    node->left = NULL;
    node->right = NULL;
    return node;
}


BinTree* addNode(BinTree* local, int id, const char* name, int age,
                 char gender, void (*task)(void* val)) {
    if (local == NULL) {
        return createNode(id, name, age, gender, task);
    }
    if (id < local->id) {
        local->left = addNode(local->left, id, name, age, gender, task);
    } else {
        local->right = addNode(local->right, id, name, age, gender, task);
    }
    return root;
}

BinTree *addChild(BinTree* root) {
    int id;
    char name[11];
    char gender;
    int age = 0;
    void (*task)(void *val);
    printf("please enter child id:\n");
    scanf("%d", &id);
    printf("please insert child name:\n");
    scanf("%s", name);
    printf("please insert child gender:\n");
    scanf(" %c", &gender);

    task = strcmp(name, "Moshe") == 0 ? moshe_task : child_task;

    return addNode(root, id, name, age, gender, task);

//    if (root == NULL) {
//        root = createBinTree(child);
////        root = (BinTree *) generic_int_function(child, createBinTree);
//    } else {
//        addToBinTree(root, createBinTree(child));
////        BinTree *var[] = {
////                (BinTree*)root,
////                (BinTree*)generic_int_function(child, createBinTree),
////                };
////        generic_function(var, addToBinTree);
//    }
}

BinTree* minValueNode(BinTree* node) {
    BinTree * cur = node;

    // loop down to find the leftmost leaf
    while (cur && cur->left != NULL)
        cur = cur->left;

    return cur;
}

void freeNode(struct BinTree* node) {
    free(node->name);
    free(node);
}

BinTree *deleteIT(BinTree* root, int id) {
    if (root == NULL) return root;
    if (id < root->id) {
        root->left = deleteIT(root->left, id);
    } else if (id > root->id) {
        root->right = deleteIT(root->right, id);
    } else {
        // Node found
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node has two children
        struct BinTree* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->id = temp->id;
        root->right = deleteIT(root->right, temp->id);
    }
    return root;
}

//
//BinTree* deleteNode(BinTree *child, BinTree *parent) {
//    // if node is leaf - easy just set parent to null and free memory
//    if (parent->left == child) {
//        parent->left = NULL;
////        free(child->name);
//        free(child);
//        return parent;
//    }
//    if (parent->right == child) {
//        parent->right = NULL;
////        free(child->name);
//        free(child);
//        return parent;
//    }
//    if (child->left == NULL && child->right == NULL) {
//        free(child);
//        child = NULL;
//        return child;
//    }
//
//    // NOT LEAF BELOW
//    // if node has one son
//    if (child->left == NULL && child->right != NULL) {
//        BinTree * temp = child->right;
//        // delete child
////        free(child->name);
////        free(child);
//        if (child == parent) {
//            // this is root we wish to delete
//            BinTree* todel = root;
//            root = temp;
//            free(todel);
//            todel = NULL;
//            return root;
//        }
//        // set parent to point to child
//        parent->right = temp;
//        return parent;
//    }
//    if (child->left != NULL && child->right == NULL) {
//        BinTree * temp = child->left;
//        // delete child
////        free(child->name);
////        free(child);
//        // set parent to point to child
//        if (child == parent) {
//            // this is root we wish to delete
//            BinTree* todel = root;
//            root = temp;
//            free(todel);
//            todel = NULL;
//            return root;
//        }
//        parent->left = temp;
//        return root;
//    }
//
//    if (child->left != NULL && child->right != NULL) {
//        BinTree* temp = minValueNode(child->right);
//
//        // Copy the inorder
//        // successor's content to this node
//        child->id = temp->id;
//        child->id = temp->id;
//        strcpy(child->name, temp->name);
//        child->age = temp->age;
//        child->gender = temp->gender;
//        child->task = temp->task;
//        child->action = temp->action;
//
//        // Delete the inorder successor
//        child->right = deleteNode(child->right, temp);
//        return root;
//    }
//
//}

void findAndKillAllMen(BinTree *child, BinTree *parent) {
    if (child == NULL) {
        return;
    }

    if (child->gender == 'M' && strcmp(child->name, "Moshe") != 0) {
        child = deleteIT(child->id);
    }
    if (child == NULL) {
        return;
    }
    findAndKillAllMen(child->left, child);
    findAndKillAllMen(child->right, child);
}

int getOrder() {
    printf("please choose order\n"
           "(1) preorder\n"
           "(2) inorder\n"
           "(3) postorder\n");
    int order;
    scanf("%d", &order);
    return order;
}

void findMoshe(BinTree *root) {
    int order = getOrder();
    void (*orderFunction[])(BinTree*) = {preorder, inorder, postorder};
    (*orderFunction[order - 1])(root);
//    generic_function(root, *orderFunction[order - 1]);
}

void printAllChildren(BinTree* root) {
    int order = getOrder();
    void (*orderFunction[])(BinTree*) = {preorderDetails, inorderDetails, postorderDetails};
    (orderFunction[order - 1])(root);
//    generic_function(root, *orderFunction[order - 1]);
}

int main() {
    BinTree *root = NULL;
    while (1) {
        printMenu();
        // INCREMENT AGE OF ALL CHILDREN BY 20 EACH ITERATION
        int choice;
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 6) {
            switch (choice) {
                case BORN_CHILD:
                    root = addChild(root);
                    printMenu();
                    break;
                case THROW_INTO_NILE:
//                    generic_function(root, findAndKillAllMen);

                    deleteNodes(root);
                    printMenu();
                    break;
                case FIND_MOSHE:
                    // whoever wrote this exercise is a fucking idiot
                    findMoshe(root);
                    printMenu();
                    break;
                case PRINT_ALL:
                    printAllChildren(root);
                    printMenu();
//                    findContactByName(phonebook);
                    break;
                case SIZE_JEWS:
                    printf("1 - All jews, 2 - Male, 3 - Female\n");
                    int whichSize;
                    scanf("%d", &whichSize);
                    void (*sizeOfFunction[])(int) ={
                            sizeOfJews,
                            sizeOfMale,
                            sizeOfFemale
                    };

                    int size = generic_int_function
                            (root,sizeOfFunction[whichSize - 1]);
                    switch (whichSize) {
                        case 1:
                            setbuf(stdout, 0);
                            printf("size of all jews is: %d\n", size);
                            break;
                        case 2:
                            setbuf(stdout, 0);
                            printf("size of all male jews is: %d\n", size);
                            break;
                        case 3:
                            setbuf(stdout, 0);
                            printf("size of all female jews is: %d\n", size);
                            break;
                        default:
                            break;
                    }
                    printMenu();
//                    updatePhoneNum(phonebook, ALPHABET_LENGTH);
                    break;
                case EXIT:
//                    genericfunction(freeIsrael(bintreelol));
                    exit(0);
                default:
                    printf("wrong choice please choose again\n");
                    break;
            }
        } else {
            printf("wrong choice please choose again\n");
            continue;
        }
    }
}
