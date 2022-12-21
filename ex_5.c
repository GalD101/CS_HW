#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define SIZE 11
//#define do a func that does char - 'A'

typedef struct Contact {
    char* firstName;
    char* lastName;
    char* phoneNum;
    struct Contact* next;
} Contact;


int addContactToPhonebook(Contact* phonebook[], int size);
int deleteContactFromPhonebook(Contact* phonebook[]);
void printMenu();
void printPhonebook(Contact* phonebook[], int size);
int findContactByNum(Contact* phonebook[], int size);
Contact* findContactByName(Contact* phonebook[], int size);
int updatePhoneNum(Contact* phonebook, int size);


// TODO: use another function for search fo delete and searchbyname
int deleteContactFromPhonebook(Contact* phonebook[]) {
    printf("Enter a contact name (<first name> <last name>): ");
    char firstName[SIZE];
    char lastName[SIZE];
    scanf("%s %s", firstName, lastName);

    int firstLetterLastNameIndex = lastName[0] - 'A';
    Contact ** listnameMightBein2 = &phonebook[firstLetterLastNameIndex];
    Contact **prev = &phonebook[firstLetterLastNameIndex];
    while ((*listnameMightBein2)->firstName != NULL) {
        if ((strcmp((*listnameMightBein2)->firstName, firstName) == 0) &&
            (strcmp((*listnameMightBein2)->lastName, lastName) == 0)) {
            printf("Are you sure? (y/n) ");
            char confirm;
            while(getchar() != '\n') {
                getchar();
            }
            scanf("%c", &confirm);
            if (confirm != 'y') {
                printf("The deletion of the contact has been canceled.\n");
                return -1;
            }
            // Found a node to delete
            // separate to 3 occurrences; beginning, middle, end (leaf)
            // beginning:
            if ((*prev) == (*listnameMightBein2)) {
                if ((*listnameMightBein2)->next == NULL) {
                    (*listnameMightBein2)->firstName = NULL;
                    (*listnameMightBein2)->lastName = NULL;
                    (*listnameMightBein2)->phoneNum = NULL;
                    (*listnameMightBein2)->next = NULL;
                    printf("The contact has been deleted successfully!\n");
                    return 0;
                }
                **listnameMightBein2 = *(*(listnameMightBein2))->next;
                printf("The contact has been deleted successfully!\n");
                return 0;
            }

            // leaf
            if ((*listnameMightBein2)->next == NULL) {
                (*prev)->next = NULL;
                printf("The contact has been deleted successfully!\n");
                return 0;
            }

            // else, middle:
            Contact * temp = (*listnameMightBein2)->next;
            free ((*prev)->next);
            (*prev)->next = temp;
            return 0;
        }
        prev = listnameMightBein2;
        if ((*listnameMightBein2)->next == NULL) {
            break;
        }
        listnameMightBein2 = &(*listnameMightBein2)->next;
    }
    printf("The deletion of the contact has failed!\n");
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

int addContactToPhonebook(Contact* phonebook[], int size) {

    // Get contact details from user
    printf("Enter a contact details"
           "(<first name> <last name> <phone number>):\n");
    char firstName[SIZE];
    char lastName[SIZE];
    char phoneNum[SIZE];
    scanf("%s %s %s", firstName, lastName, phoneNum);


    for (int i = 0; i < size; ++i) {
        Contact * forloopIndex = phonebook[i];
        while (forloopIndex->firstName != NULL) {
            if (strcmp(forloopIndex->firstName, firstName) == 0
                && strcmp(forloopIndex->lastName, lastName) == 0) {
                printf("The addition of the contact has failed, "
                       "since the contact %s %s already exists!\n", firstName,
                       lastName);
                return 2;
            }
            if (strcmp(forloopIndex->phoneNum, phoneNum) == 0) {
                printf("The addition of the contact has failed, "
                       "since the phone number %s already exists!\n", phoneNum);
                return 3;
            }
            if (forloopIndex->next == NULL) {
                break;
            }
            forloopIndex = forloopIndex->next;
        }

    }

    int pos = lastName[0] - 'A';
    Contact * matchingLastNamelist = phonebook[pos];
    if (matchingLastNamelist->firstName == NULL) {
        matchingLastNamelist->firstName = (char*) malloc(SIZE);
        matchingLastNamelist->lastName = (char*) malloc(SIZE);
        matchingLastNamelist->phoneNum = (char*) malloc(SIZE);

        if (matchingLastNamelist->firstName == NULL ||
            matchingLastNamelist->lastName  == NULL ||
            matchingLastNamelist->phoneNum  == NULL) {
            printf("The addition of the contact has failed!\n");
            return 1;
        }
        // FIRST INSERT
        strcpy(matchingLastNamelist->firstName, firstName);
        strcpy(matchingLastNamelist->lastName, lastName);
        strcpy(matchingLastNamelist->phoneNum, phoneNum);
        matchingLastNamelist->next = NULL;
        printf("The contact has been added successfully!\n");
        return 0;
    }

    Contact * loopIndex = matchingLastNamelist;
    while (loopIndex->firstName != NULL) {
        if (loopIndex->next == NULL) {
            break;
        }
        loopIndex = loopIndex->next;
    }
    loopIndex->next = (Contact*) malloc(sizeof(Contact));
    loopIndex->next->firstName = (char*) malloc(SIZE);
    loopIndex->next->lastName = (char*) malloc(SIZE);
    loopIndex->next->phoneNum = (char*) malloc(SIZE);

    if (loopIndex->next == NULL ||
        loopIndex->next->firstName == NULL ||
        loopIndex->next->lastName  == NULL ||
        loopIndex->next->phoneNum  == NULL) {
        printf("The addition of the contact has failed!\n");
        return 1;
    }

    strcpy(loopIndex->next->firstName, firstName);
    strcpy(loopIndex->next->lastName, lastName);
    strcpy(loopIndex->next->phoneNum, phoneNum);
    loopIndex->next->next = NULL;
    printf("The contact has been added successfully!\n");
    return 0;
}

int findContactByNum(Contact* phonebook[], int size) {
    printf("Enter a phone number: ");
    char phoneNum[SIZE];
    scanf("%s", phoneNum);
    for (int i = 0; i < size; ++i) {
        Contact* current = phonebook[i];
        while (current->firstName != NULL) {
            if (strcmp(current->phoneNum, phoneNum) == 0) {
                printf("The following contact was found: %s %s %s\n",
                       current->firstName,
                       current->lastName,
                       current->phoneNum);
                return 0;
            }
            if (current->next == NULL) {
                break;
            }
            current = current->next;
        }
    }
    printf("No contact with a phone number "
           "%s was found in the phone book\n",phoneNum);
    return 1;
}

Contact* findContactByName(Contact* phonebook[], int size) {
    printf("Enter a contact name (<first name> <last name>): ");
    char firstName[SIZE], lastName[SIZE];
    scanf("%s %s", firstName, lastName);

    int posLastName = lastName[0] - 'A';
    Contact * matchingLastNamelist = phonebook[posLastName];

    while (matchingLastNamelist->firstName != NULL) {
        if (strcmp(matchingLastNamelist->firstName, firstName) == 0 &&
            strcmp(matchingLastNamelist->lastName, lastName) == 0) {
            printf("The following contact was found: %s %s %s\n",
                   matchingLastNamelist->firstName,
                   matchingLastNamelist->lastName,
                   matchingLastNamelist->phoneNum);
            return matchingLastNamelist;
        }
        if (matchingLastNamelist->next == NULL) {
            break;
        }
        matchingLastNamelist = matchingLastNamelist->next;
    }
    printf("No contact with a name %s %s was found in the phone book",
           firstName, lastName);
    return NULL;
}

int updatePhoneNum(Contact* phonebook, int size) {
    Contact* contactToUpdate = findContactByName(phonebook, size);
    if (contactToUpdate == NULL) {
        // The contact doesn't exist abort;
        printf("");
        return 1;
    }

    printf("Enter the new phone number: ");
    char newPhoneNum[SIZE];
    scanf("%s", newPhoneNum);

    strcpy(contactToUpdate->phoneNum, newPhoneNum);
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

    // Initialize phone book and allocate memory
    for (int i = 0; i < 26; ++i) {
        phonebook[i] = (Contact*)malloc(sizeof(Contact*));
        phonebook[i]->firstName = (char*)malloc(sizeof(phonebook[i]->firstName));
        phonebook[i]->lastName = (char*)malloc(sizeof(phonebook[i]->lastName));
        phonebook[i]->phoneNum = (char*)malloc(sizeof(phonebook[i]->phoneNum));
        phonebook[i]->next = (Contact*)malloc(sizeof(phonebook[i]->next));

        if (phonebook[i] == NULL ||
            phonebook[i]->firstName == NULL ||
            phonebook[i]->lastName == NULL ||
            phonebook[i]->phoneNum == NULL ||
            phonebook[i]->next     == NULL) {
            printf("ERROR\n");
            exit(1);
        }
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
                    addContactToPhonebook(phonebook, 26);
                    printMenu();
                    break;
                case DELETE:
                    deleteContactFromPhonebook(phonebook);
                    printMenu();
                    break;
                case FIND_BY_NUM:
                    findContactByNum(phonebook, 26);
                    printMenu();
                    break;
                case FIND_BY_NAME:
                    findContactByName(phonebook, 26);
                    printMenu();
                    break;
                case UPDATE:
                    updatePhoneNum(phonebook, 26);
                    printMenu();
                    break;
                case PRINT:
                    printPhonebook(phonebook, 26);
                    printMenu();
                    break;
                case EXIT:
                    printf("Bye!");
                    // free space here?
                    exit(0);
                    break;
                default:
                    printf("Wrong option, try again: ");
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

