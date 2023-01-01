#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "BinTree.h"

static BinTree *root = NULL;

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

int addChild() {
    int id;
    char name[11];
    char gender;
    int age = 0;
    void (*task)(void *val);
    void *action;
    printf("please enter child id:\n");
    scanf("%d", &id);
    printf("please insert child name:\n");
    scanf("%s", name);
    printf("please insert child gender:\n");
    scanf(" %c", &gender);

    task = strcmp(name, "Moshe") == 0 ? moshe_task : child_task;
    action = &task;
    // we got the data now we shall add the child to the tree
    // first, create a child object
    // we will need to allocate memory

    BinTree *child = (BinTree *) malloc(sizeof(BinTree));
    child->id = id;
    child->name = name;
    child->gender = gender;
    child->age = age;
    child->task = task;
    child->action = action;
    child->left = NULL;
    child->right = NULL;
    if (root == NULL) {
        root = createBinTree(child);
    } else {
        addToBinTree(root, createBinTree(child));
    }
}

//BinTree *toTheNile() {
//    if (root == NULL) {
//        return NULL;
//    }
//    do {
//        // https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
//        // find the first occurence of a male in the tree
//        // do that in any order youd like (in order for example)
//        BinTree *man = findMen();
//        if (man->id < root->id) {
//            root->left = toTheNile(root->left, man->id);
//        } else if (man->id > root->id) {
//            root->right = toTheNile(root->right, man->id);
//        } else {
//            if (root->left == NULL) {
//                BinTree *temp = root->right;
////                free(root); // this may be problematic
//                return temp;
//            }
//            else if (root->right == NULL) {
//                BinTree* temp = root->left;
////                free(root); // this may be problematic
//                return temp;
//            }
//
//            BinTree* temp = minValueNode(root->right);
//
//            // might need to copy the whol object here
//            root->id = temp->id;
//
//            root->right = toTheNile(root->right, temp->id);
//            // this is very problematic
//        }
//        return root;
//    } while (man);
//}


BinTree* minValueNode(BinTree* node) {
    BinTree * cur = node;

    /* loop down to find the leftmost leaf */
    while (cur && cur->left != NULL)
        cur = cur->left;

    return cur;
}


// TODO: make this not ugly per favor
BinTree* deleteNode(BinTree *child, BinTree *parent) {
    // if node is leaf - easy just set parent to null and free memory
    if (parent->left == child) {
        parent->left = NULL;
//        free(child->name);
        free(child);
        return parent;
    } else if (parent->right == child) {
        parent->right = NULL;
//        free(child->name);
        free(child);
        return parent;
    }

    // NOT LEAF BELOW
    // if node has one son
    // TODO:save conditions in a variable blabla you know what to do
    else if (child->left == NULL && child->right != NULL) {
        BinTree * temp = child->right;
        // delete child
//        free(child->name);
        free(child);
        if (child == parent) {
            // this is root we wish to delete
            BinTree* todel = root;
            root = temp;
            free(todel);
            todel = NULL;
            return root;
        }
        // set parent to point to child
        parent->right = temp;
        return parent;
    }
    else if (child->left != NULL && child->right == NULL) {
        BinTree * temp = child->left;
        // delete child
//        free(child->name);
//        free(child);
        // set parent to point to child
        if (child == parent) {
            // this is root we wish to delete
            BinTree* todel = root;
            root = temp;
            free(todel);
            todel = NULL;
            return root;
        }
        parent->left = temp;
        return root;
    }

    else if (child->left != NULL && child->right != NULL) {
        // complex handle later
        BinTree* temp = minValueNode(child->right);

        // Copy the inorder
        // successor's content to this node
        child->id = temp->id;
        child->id = temp->id;
        strcpy(child->name, temp->name);
        child->age = temp->age; // maybe initialize this to 0
        child->gender = temp->gender;
        child->task = temp->task;
        child->action = temp->action;

        // Delete the inorder successor
        child->right = deleteNode(child->right, temp);
        return root;
    }

}

// NOTE: I am not a feminist (lol)
void findAndKillAllMen(BinTree *child, BinTree *parent) {
    if (child == NULL) {
        return;
    }

    if (child->gender == 'M' && strcmp(child->name, "Moshe") != 0) {
        // can also check that moshe is a male (in case there is a Moshe girl)
        // delete here
        child = deleteNode(child, parent);
    }

    findAndKillAllMen(child->left, child);
    findAndKillAllMen(child->right, child);
}

void printOrderMenu() {
    printf("please choose order\n"
           "(1) preorder\n"
           "(2) inorder\n"
           "(3) postorder\n");
}

void findMoshe() {
    printOrderMenu();
    char order;
    scanf("%d", &order);
    void (*orderFunction[])(BinTree*) = {preorder, inorder, postorder};
    (*orderFunction[order - 1])(root);

}

int main() {
    printMenu();
    while (1) {
        int action;
        scanf("%d", &action);
        if (action >= 1 && action <= 6) {
            switch (action) {
                case BORN_CHILD:
                    addChild();
                    printMenu();
                    break;
                case THROW_INTO_NILE:
                    findAndKillAllMen(root, root);
                    printMenu();
                    break;
                case FIND_MOSHE:
                    // whoever wrote this exercise is a fucking idiot
                    findMoshe();
                    printMenu();
                    break;
                case PRINT_ALL:

                    printMenu();
//                    findContactByName(phonebook);
                    break;
                case SIZE_JEWS:
                    printMenu();
//                    updatePhoneNum(phonebook, ALPHABET_LENGTH);
                    break;
                case EXIT:
//                    genericfunction(freeIsrael(bintreelol));
                    exit(0);
                default:
                    printf("wrong choose please choose again\n");
                    break;
            }
        } else {
            printf("wrong choice please choose again\n");
            continue;
        }
    }
}
