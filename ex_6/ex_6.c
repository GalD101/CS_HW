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
    printf("please enter child id:\n");
    scanf("%d", &id);
    printf("please insert child name:\n");
    scanf("%s", name);
    printf("please insert child gender:\n");
    scanf(" %c", &gender);

    task = strcmp(name, "Moshe") == 0 ? moshe_task : child_task;

    // we got the data now we shall add the child to the tree
    // first, create a child object
    // we will need to allocate memory

    BinTree *child = (BinTree *) malloc(sizeof(BinTree));
    child->id = id;
    child->name = name;
    child->gender = gender;
    child->age = age;
    child->task = task;
    child->action = NULL;
    child->left = NULL;
    child->right = NULL;
    if (root == NULL) {
        root = createBinTree(child);
    } else {
        addToBinTree(root, createBinTree(child));
    }
}

BinTree *toTheNile() {
    if (root == NULL) {
        return;
    }
    do {
        // https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
        // find the first occurence of a male in the tree
        // do that in any order youd like (in order for example)
        BinTree *man = findMen();
        if (man->id < root->id) {
            root->left = toTheNile(root->left, man->id);
        } else if (man->id > root->id) {
            root->right = toTheNile(root->right, man->id);
        } else {
            if (root->left == NULL) {
                BinTree *temp = root->right;
//                free(root); // this may be problematic
                return temp;
            }
            else if (root->right == NULL) {
                BinTree* temp = root->left;
//                free(root); // this may be problematic
                return temp;
            }

            BinTree* temp = minValueNode(root->right);

            // might need to copy the whol object here
            root->id = temp->id;

            root->right = toTheNile(root->right, temp->id);
            // this is very problematic
        }
        return root;
    } while (man);
}

int main() {
    while (1) {
        printMenu();
        int action;
        scanf("%d", &action);
        if (action >= 1 && action <= 6) {
            switch (action) {
                case BORN_CHILD:
                    addChild();
                    printMenu();
                    break;
                case THROW_INTO_NILE:
//                    deleteContactFromPhonebook(phonebook);
                    printMenu();
                    break;
                case FIND_MOSHE:
//                    findContactByNum(phonebook, ALPHABET_LENGTH);
                    printMenu();
                    break;
                case PRINT_ALL:
//                    findContactByName(phonebook);
                    printMenu();
                    break;
                case SIZE_JEWS:
//                    updatePhoneNum(phonebook, ALPHABET_LENGTH);
                    printMenu();
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
