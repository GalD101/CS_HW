#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinTree.h"

int main() {
    BinTree *root = NULL;
    int fuckthis = 1;
    while (1) {
        generic_function(root, (void *) (incrementAge));
        generic_function(root, (void *) lookForMoshe);
        if (fuckthis) {
            fuckthis = 0;
        } else {
            printf("\n");
        }
        generic_function((BinTree *) &root, (void *) (deleteDead));
        printf("please choose action:\n");
        printf("(1) A child was born\n");
        printf("(2) Throw into the Nile\n");
        printf("(3) Find Moshe\n");
        printf("(4) Print All\n");
        printf("(5) Size of jews\n");
        printf("(6) Exit\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {

            // Get details from user
            int id;
            char name[11];
            char gender;
            printf("please enter child id:\n");
            scanf("%d", &id);
            printf("please insert child name:\n");
            scanf("%s", name);
            printf("please insert child gender:\n");
            scanf(" %c", &gender);

            root = addChild(root, id, name, -20, gender);
        } else if (choice == 2) {
            generic_function((BinTree *) &root, (void *) (deleteMen));
        } else if (choice == 3) {
            fuckMoshe(&root);
        } else if (choice == 4) {
            generic_function(root, (void *) (printAllChildren));
        } else if (choice == 5) {
            printf("please choose what you want to calculate:\n");
            printf("(1) All jews\n");
            printf("(2) Male\n");
            printf("(3) Female\n");
            int whichSize;
            scanf("%d", &whichSize);
            if (whichSize != 1 && whichSize != 2 && whichSize != 3) {
                printf("wrong order!\n");
                continue;
            }
            int (*sizeOfFunction[])(BinTree *) ={
                    sizeOfJews,
                    sizeOfMale,
                    sizeOfFemale
            };

            int size = generic_int_function
                    (root, (void *) (sizeOfFunction[whichSize - 1]));
            switch (whichSize) {
                case 1:
                    printf("size of all jews is: %d\n", size);
                    break;
                case 2:
                    printf("size of all male jews is: %d\n", size);
                    break;
                case 3:
                    printf("size of all female jews is: %d\n", size);
                    break;
                default:
                    break;
            }
        } else if (choice == 6) {
            generic_function(root, (void *) (freeIsrael));
            exit(0);
        } else {
            printf("wrong choose please choose again\n");
        }
    } // end of while loop
    return 0;
}
