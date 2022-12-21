#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define SIZE 11
#define ALPHABET_LENGTH 26
#define letterIndex(a) (a - 'A')

typedef struct Contact {
    char* firstName;
    char* lastName;
    char* phoneNum;
    struct Contact* next;
} Contact;


void setup(Contact* phonebook[]);
int addContactToPhonebook(Contact* phonebook[], int size);
int deleteContactFromPhonebook(Contact* phonebook[]);
void printMenu();
void printPhonebook(Contact* phonebook[], int size);
int findContactByNum(Contact* phonebook[], int size);
Contact* findContactByName(Contact* phonebook[], int size);
int updatePhoneNum(Contact* phonebook, int size);

void setup (Contact* phonebook[]) {

    // Initialize phone book and allocate memory
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
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
}

void teardown(Contact* phonebook[]) {
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        free(phonebook[i]->firstName);
        free(phonebook[i]->lastName);
        free(phonebook[i]->phoneNum);
        free(phonebook[i]->next);
        free(phonebook[i]);
    }
}


// TODO: use another function for search for delete and searchbyname
int deleteContactFromPhonebook(Contact* phonebook[]) {
    printf("Enter a contact name (<first name> <last name>): ");
    char firstName[SIZE];
    char lastName[SIZE];
    scanf("%s %s", firstName, lastName);

    int firstLetterLastNameIndex = letterIndex(lastName[0]);
    Contact ** listContactMayBeIn = &phonebook[firstLetterLastNameIndex];
    Contact **prev = &phonebook[firstLetterLastNameIndex];
    while ((*listContactMayBeIn)->firstName != NULL) {
        if ((strcmp((*listContactMayBeIn)->firstName, firstName) == 0) &&
            (strcmp((*listContactMayBeIn)->lastName, lastName) == 0)) {
            printf("Are you sure? (y/n) ");
            char confirm;
            while(getchar() != '\n') {
                getchar();
            }
            scanf("%c", &confirm);
            if (confirm != 'y' && confirm != 'Y') {
                printf("The deletion of the contact has been canceled.\n");
                return -1;
            }

            // If the node is the head (the first item in the list)
            if ((*prev) == (*listContactMayBeIn)) {
                if ((*listContactMayBeIn)->next == NULL) {
                    (*listContactMayBeIn)->firstName = NULL;
                    (*listContactMayBeIn)->lastName = NULL;
                    (*listContactMayBeIn)->phoneNum = NULL;
                    (*listContactMayBeIn)->next = NULL;
                    printf("The contact has been deleted successfully!\n");
                    return 0;
                }
                **listContactMayBeIn = *(*(listContactMayBeIn))->next;
                printf("The contact has been deleted successfully!\n");
                return 0;
            }

            // leaf
            if ((*listContactMayBeIn)->next == NULL) {
                (*prev)->next = NULL;
                printf("The contact has been deleted successfully!\n");
                return 0;
            }

            // else, middle:
            Contact * temp = (*listContactMayBeIn)->next;
            free ((*prev)->next);
            (*prev)->next = temp;
            return 0;
        }
        prev = listContactMayBeIn;
        if ((*listContactMayBeIn)->next == NULL) {
            break;
        }
        listContactMayBeIn = &(*listContactMayBeIn)->next;
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
        Contact currentContact = *phonebook[i];
        Contact anotherOne = *phonebook[i];
        if (currentContact.firstName == NULL) {

            // current list is Empty, continue to the next one
            continue;
        }

        int numOfContacts = 0;
        do {
            ++numOfContacts;
            if (currentContact.next == NULL) {
                break;
            }
            currentContact = *currentContact.next;
        } while (currentContact.firstName != NULL);


        for (int f = 0; f < numOfContacts; ++f) {
            for (int k = 1; k < numOfContacts - f; ++k) {
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
        Contact * currentList = phonebook[i];

        // If name is NULL than I assume the whole struct is empty
        while (currentList->firstName != NULL) {

            // Check if there is an existing contact with the same name
            if (strcmp(currentList->firstName, firstName) == 0
                && strcmp(currentList->lastName, lastName) == 0) {
                printf("The addition of the contact has failed, "
                       "since the contact %s %s already exists!\n", firstName,
                       lastName);
                return 2;
            }

            // Check if there is an existing contact with the same phone number
            if (strcmp(currentList->phoneNum, phoneNum) == 0) {
                printf("The addition of the contact has failed, "
                       "since the phone number %s already exists!\n", phoneNum);
                return 3;
            }

            // break from the loop when reacheing the last Contact
            if (currentList->next == NULL) {
                break;
            }

            // Move the pointer to the next Contact in the current list
            currentList = currentList->next;
        }

    }

    int indexByLastName = lastName[0] - 'A';
    Contact * matchingLastNamelist = phonebook[indexByLastName];

    // If name is NULL than I assume the whole struct is empty
    // If this is NULL, that means this is the first Contact
    // in the matching list
    if (matchingLastNamelist->firstName == NULL) {

        // allocate memory for the new contact
        matchingLastNamelist->firstName = (char*) malloc(SIZE);
        matchingLastNamelist->lastName = (char*) malloc(SIZE);
        matchingLastNamelist->phoneNum = (char*) malloc(SIZE);

        // If there was an error while allocating memory
        if (matchingLastNamelist->firstName == NULL ||
            matchingLastNamelist->lastName  == NULL ||
            matchingLastNamelist->phoneNum  == NULL) {
            printf("The addition of the contact has failed!\n");
            return 1;
        }

        // Copy the values from the user into the new allocated memory
        strcpy(matchingLastNamelist->firstName, firstName);
        strcpy(matchingLastNamelist->lastName, lastName);
        strcpy(matchingLastNamelist->phoneNum, phoneNum);
        matchingLastNamelist->next = NULL;
        printf("The contact has been added successfully!\n");
        return 0;
    }

    Contact * loopIndex = matchingLastNamelist;

    // Traverse the list up until the last element
    while (loopIndex->firstName != NULL) {
        if (loopIndex->next == NULL) {
            break;
        }
        loopIndex = loopIndex->next;
    }

    // allocate memory for the new contact
    loopIndex->next = (Contact*) malloc(sizeof(Contact));
    loopIndex->next->firstName = (char*) malloc(SIZE);
    loopIndex->next->lastName = (char*) malloc(SIZE);
    loopIndex->next->phoneNum = (char*) malloc(SIZE);

    // If there was an error while allocating memory
    if (loopIndex->next == NULL ||
        loopIndex->next->firstName == NULL ||
        loopIndex->next->lastName  == NULL ||
        loopIndex->next->phoneNum  == NULL) {
        printf("The addition of the contact has failed!\n");
        return 1;
    }

    // Copy the values from the user into the new allocated memory
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

    // scan for phone number in each entry
    for (int i = 0; i < size; ++i) {
        Contact* currentEntry = phonebook[i];
        while (currentEntry->firstName != NULL) {
            if (strcmp(currentEntry->phoneNum, phoneNum) == 0) {
                printf("The following contact was found: %s %s %s\n",
                       currentEntry->firstName,
                       currentEntry->lastName,
                       currentEntry->phoneNum);
                return 0;
            }
            if (currentEntry->next == NULL) {
                break;
            }
            currentEntry = currentEntry->next;
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

    int IndexByLastName = letterIndex(lastName[0]);
    Contact * matchingLastNamelist = phonebook[IndexByLastName];

    // Look for the Contact in the matching list
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
    printf("No contact with a name %s %s was found in the phone book\n",
           firstName, lastName);
    return NULL;
}

int updatePhoneNum(Contact* phonebook, int size) {
    Contact* contactToUpdate = findContactByName(phonebook, size);
    if (contactToUpdate == NULL) {

        // The contact doesn't exist, abort;
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
    Contact* phonebook[ALPHABET_LENGTH];
    setup(phonebook);

    printMenu();
    while (1) {
        int choice;
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 7) {
            switch (choice) {
                case ADD:
                    addContactToPhonebook(phonebook, ALPHABET_LENGTH);
                    printMenu();
                    break;
                case DELETE:
                    deleteContactFromPhonebook(phonebook);
                    printMenu();
                    break;
                case FIND_BY_NUM:
                    findContactByNum(phonebook, ALPHABET_LENGTH);
                    printMenu();
                    break;
                case FIND_BY_NAME:
                    findContactByName(phonebook, ALPHABET_LENGTH);
                    printMenu();
                    break;
                case UPDATE:
                    updatePhoneNum(phonebook, ALPHABET_LENGTH);
                    printMenu();
                    break;
                case PRINT:
                    printPhonebook(phonebook, ALPHABET_LENGTH);
                    printMenu();
                    break;
                case EXIT:
                    printf("Bye!");
                    // free space here? YES
                    // teardown();
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

