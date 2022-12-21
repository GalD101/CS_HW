#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define SIZE 10

typedef struct Contact {
    char* firstName;
    char* lastName;
    char* phoneNum;
    struct Contact* next;
} Contact;


int addContactToPhonebook(Contact* phonebook[]);
int deleteContactFromPhonebook(Contact* phonebook[]);
int delFromLinkedList(Contact* prev);
void printMenu();
void printPhonebook(Contact* phonebook[], int size);
Contact* findContactByNum();
Contact* findContactByName();
void updatePhoneNum();

int deleteContactFromPhonebook(Contact* phonebook[]) {
    printf("Enter a contact name (<first name> <last name>): ");
    char firstName[SIZE];
    char lastName[SIZE];
    scanf("%s%s", firstName, lastName);

    char firstLetterLastNameIndex = lastName[0] - 'A';
    Contact* workwithme = phonebook[firstLetterLastNameIndex];
    Contact* prev       = workwithme;
    while (workwithme->next != NULL) {
        if (workwithme->lastName == lastName && workwithme->firstName == firstName) {
            // delete the current node (workwithme)
            if (prev == workwithme) {
                // it's the first item we need to delete
                Contact* idk = workwithme->next;
                workwithme->next = NULL;
                workwithme = idk;
                // todo:free up space
            }
            delFromLinkedList(prev);
            return 1;
        }
        workwithme = workwithme->next;
        prev = workwithme;
    }
}

int delFromLinkedList(Contact* prev) {
    Contact* toDelete = prev->next;
    Contact* next     = toDelete->next;

    toDelete->next = NULL;
    prev->next = next;
    // todo:free up memory
}

void printMenu() {
    printf("Welcome to the phone book manager!\n");
    printf("Choose an option:\n");
    printf("1. Add a new contact to the phone book.\n");
    printf("2. Delete a contact from the phone book.\n");
    printf("3. Find a contact in the phone book by phone number.\n");
    printf("4. Find a contact in the phone book by name.\n");
    printf("5. Update phone number for a contact.\n");
    printf("6. Print phone book.\n");
    printf("7. Exit.\n");
}

void printPhonebook(Contact* phonebook[], int size) {
    for (int i = 0; i < size; ++i) {
        Contact loopVar = *phonebook[i];
        Contact anotherOne = *phonebook[i];
        if (loopVar.firstName == NULL) {
            continue;
        }
        int j = 0;
        do {
            ++j;
//            printf("%10s %10s %10s\n",
//                   loopVar.firstName, loopVar.lastName, loopVar.phoneNum);
            if (loopVar.next == NULL) {
                break;
            }
            loopVar = *loopVar.next;
        } while (loopVar.firstName);

        for (int f = 0; f < j; ++f) {
            for (int k = 1; k < j - f; ++k) {
                anotherOne = *anotherOne.next;
            }
            printf("%10s %10s %10s\n",
                   anotherOne.firstName, anotherOne.lastName, anotherOne.phoneNum);
            anotherOne = *phonebook[i];
        }
    }
}

int addContactToPhonebook(Contact* phonebook[]) {

    // Get contact details from user
    printf("Enter a contact details"
           "(<first name> <last name> <phone number>):\n");
    char firstName[SIZE];
    char lastName[SIZE];
    char phoneNum[SIZE];
    scanf("%s %s %s", firstName, lastName, phoneNum);

    int pos = lastName[0] - 'A';
    Contact * matchingLastNamelist = phonebook[pos];
    Contact ** loopIndex = &matchingLastNamelist;
    if (matchingLastNamelist->firstName == NULL) {
        matchingLastNamelist->firstName = (char*) malloc(10);
        matchingLastNamelist->lastName = (char*) malloc(10);
        matchingLastNamelist->phoneNum = (char*) malloc(10);
        // FIRST INSERT
        strcpy(matchingLastNamelist->firstName, firstName);
        strcpy(matchingLastNamelist->lastName, lastName);
        strcpy(matchingLastNamelist->phoneNum, phoneNum);
        matchingLastNamelist->next = NULL;
        return 0;
    }

    while ((*loopIndex)->next != NULL) {
        (*loopIndex) = (*loopIndex)->next;
    }

    (*loopIndex)->next = (Contact*) malloc(sizeof(Contact));
    (*loopIndex)->next->firstName = (char*) malloc(10);
    (*loopIndex)->next->lastName = (char*) malloc(10);
    (*loopIndex)->next->phoneNum = (char*) malloc(10);

    strcpy((*loopIndex)->next->firstName, firstName);
    strcpy((*loopIndex)->next->lastName, lastName);
    strcpy((*loopIndex)->next->phoneNum, phoneNum);
    matchingLastNamelist->next->next = NULL;
    return 0;





}
enum Options {
    ADD = 1,
    DELETE,
    FIND_BY_NUM,
    FIND_BY_NAME,
    UPDATE,
    PRINT,
    EXIT,
};

int main() {
    Contact* phonebook[26];
    for (int i = 0; i < 26; ++i) {
        phonebook[i] = (Contact*)malloc(sizeof(Contact*));
        phonebook[i]->firstName = (char*)malloc(sizeof(phonebook[i]->firstName));
        phonebook[i]->lastName = (char*)malloc(sizeof(phonebook[i]->lastName));
        phonebook[i]->phoneNum = (char*)malloc(sizeof(phonebook[i]->phoneNum));
        phonebook[i]->next = (Contact*)malloc(sizeof(phonebook[i]->next));
        phonebook[i]->firstName = NULL;
        phonebook[i]->lastName  = NULL;
        phonebook[i]->phoneNum  = NULL;
        phonebook[i]->next      = NULL;
    }


    printMenu();
    while (1) {
        int choice;
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 7) {
            switch (choice) {
                case ADD:
                    addContactToPhonebook(phonebook);
                    printMenu();
                    break;
                case DELETE:
                    printMenu();
                    break;
                case FIND_BY_NUM:
                    printMenu();
                    break;
                case FIND_BY_NAME:
                    printMenu();
                    break;
                case UPDATE:
                    printMenu();
                    break;
                case PRINT:
                    printPhonebook(phonebook, 26);
                    printMenu();
                    break;
                case EXIT:
                default:
                    break;
            }
        }
        else {
            printf("Wrong option, try again:");
            continue;
        }
    }
}








////    char str[6] = "";
////    scanf("%[^\n]", str);
////    printf("%s", str);
//    int* mPtr = (int*) malloc(99999999999999);
//    if (mPtr == NULL) { return 1; }
//    return 0;

