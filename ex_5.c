#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define SIZE 11
#define ALPHABET_LENGTH 26
#define letterIndex(a) (a - 'A')

typedef struct Contact {
    char *firstName;
    char *lastName;
    char *phoneNum;
    struct Contact *next;
} Contact;


void printMenu();

void teardown(Contact *phonebook[]);

int addContactToPhonebook(Contact *phonebook[], int size);

int deleteContactFromPhonebook(Contact *phonebook[]);

int findContactByNum(Contact *phonebook[], int size);

Contact *findContactByName(Contact *phonebook[]);

int updatePhoneNum(Contact *phonebook[], int size);

void printPhonebook(Contact *phonebook[], int size);

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

void teardown(Contact *phonebook[]) {
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        if (phonebook[i] != NULL) {
            while (phonebook[i] != NULL) {
                free(phonebook[i]->firstName);
                free(phonebook[i]->lastName);
                free(phonebook[i]->phoneNum);
                phonebook[i]->firstName = NULL;
                phonebook[i]->lastName = NULL;
                phonebook[i]->phoneNum = NULL;
                Contact * toDelete = phonebook[i];
                phonebook[i] = phonebook[i]->next;
                free(toDelete);
                toDelete = NULL;
            }
        }
    }
}

int addContactToPhonebook(Contact *phonebook[], int size) {

    // Get contact details from user
    printf("Enter a contact details "
           "(<first name> <last name> <phone number>): ");
    char firstName[SIZE];
    char lastName[SIZE];
    char phoneNum[SIZE];
    scanf("%s %s %s", firstName, lastName, phoneNum);

    // Get the list's index in which the new contact should be added
    int indexByLastName = letterIndex(lastName[0]);
    Contact *lastContactInMatchingList = phonebook[indexByLastName];

    // Iterate over the phone book and check for existing name/number
    for (int i = 0; i < size; ++i) {
        Contact *currentList = phonebook[i];

        // loop until we reach the last item in the current list
        // also check if the contact details aren't already in the list
        while (currentList != NULL) {

            // Check if there is an existing contact with the same name
            if (i == indexByLastName) {
                if (strcmp(currentList->firstName, firstName) == 0
                    && strcmp(currentList->lastName, lastName) == 0) {
                    printf("The addition of the contact has failed, "
                           "since the contact %s %s already exists!\n",
                           firstName,
                           lastName);
                    return 2;
                }

                // Save this pointer to use later if details are valid
                lastContactInMatchingList = currentList;
            }

            // Check if there is an existing contact with the same phone number
            if (strcmp(currentList->phoneNum, phoneNum) == 0) {
                printf("The addition of the contact has failed, "
                       "since the phone number %s already exists!\n", phoneNum);
                return 3;
            }

            // Move the pointer to the next Contact in the current list
            currentList = currentList->next;
        } // end of while loop
    }

    // Details are valid, append the new Contact to the phonebook

    // If we have no contacts in the matching list yet
    if (lastContactInMatchingList == NULL) {

        // Allocate memory for the new contact
        lastContactInMatchingList = (Contact *) malloc(sizeof(Contact));
        lastContactInMatchingList->firstName = (char *) malloc(SIZE);
        lastContactInMatchingList->lastName = (char *) malloc(SIZE);
        lastContactInMatchingList->phoneNum = (char *) malloc(SIZE);

        // If there was an error while allocating memory
        if (lastContactInMatchingList->firstName == NULL ||
            lastContactInMatchingList->lastName == NULL ||
            lastContactInMatchingList->phoneNum == NULL) {
            printf("The addition of the contact has failed!\n");

            // Free all memory we tried to allocate
            free(lastContactInMatchingList->firstName);
            free(lastContactInMatchingList->lastName);
            free(lastContactInMatchingList->phoneNum);
            free(lastContactInMatchingList);

            // Set the pointers to NULL (to avoid pointing at garbage values)
            lastContactInMatchingList->firstName = NULL;
            lastContactInMatchingList->lastName = NULL;
            lastContactInMatchingList->phoneNum = NULL;
            lastContactInMatchingList = NULL;
            return 1;
        }

        // Copy the values from the user's input into the new allocated memory
        strcpy(lastContactInMatchingList->firstName, firstName);
        strcpy(lastContactInMatchingList->lastName, lastName);
        strcpy(lastContactInMatchingList->phoneNum, phoneNum);
        lastContactInMatchingList->next = NULL;
        phonebook[indexByLastName] = lastContactInMatchingList;
        printf("The contact has been added successfully!\n");
        return 0;
    }

    // If there is already a contact in the matching list,
    // allocate memory for the new contact which is the next one after the last
    lastContactInMatchingList->next = (Contact *) malloc(sizeof(Contact));
    lastContactInMatchingList->next->firstName = (char *) malloc(SIZE);
    lastContactInMatchingList->next->lastName = (char *) malloc(SIZE);
    lastContactInMatchingList->next->phoneNum = (char *) malloc(SIZE);

    // If there was an error while allocating memory
    if (lastContactInMatchingList->next == NULL ||
        lastContactInMatchingList->next->firstName == NULL ||
        lastContactInMatchingList->next->lastName == NULL ||
        lastContactInMatchingList->next->phoneNum == NULL) {
        printf("The addition of the contact has failed!\n");

        // Free all memory we tried to allocate
        free(lastContactInMatchingList->next->firstName);
        free(lastContactInMatchingList->next->lastName);
        free(lastContactInMatchingList->next->phoneNum);
        free(lastContactInMatchingList->next);

        // Set the pointers to NULL
        // (to avoid pointing at garbage values - "dangling pointers")
        lastContactInMatchingList->next->firstName = NULL;
        lastContactInMatchingList->next->lastName = NULL;
        lastContactInMatchingList->next->phoneNum = NULL;
        lastContactInMatchingList->next = NULL;
        return 1;
    }

    // Copy the values from the user's input into the new allocated memory
    strcpy(lastContactInMatchingList->next->firstName, firstName);
    strcpy(lastContactInMatchingList->next->lastName, lastName);
    strcpy(lastContactInMatchingList->next->phoneNum, phoneNum);
    lastContactInMatchingList->next->next = NULL;
    printf("The contact has been added successfully!\n");
    return 0;
}

int deleteContactFromPhonebook(Contact *phonebook[]) {
    printf("Enter a contact name (<first name> <last name>): ");
    char firstName[SIZE];
    char lastName[SIZE];
    scanf("%s %s", firstName, lastName);

    int firstLetterLastNameIndex = letterIndex(lastName[0]);
    Contact *currentContact = phonebook[firstLetterLastNameIndex];
    Contact *prevContact = phonebook[firstLetterLastNameIndex];

    // Traverse the matching list and look for a match
    while (currentContact != NULL) {
        if ((strcmp(currentContact->firstName, firstName) == 0) &&
            (strcmp(currentContact->lastName, lastName) == 0)) {

            // Found contact to delete
            printf("\nAre you sure? (y/n) ");
            char confirm;
            while (getchar() != '\n') {
                getchar();
            }

            scanf("%c", &confirm);
            if (confirm != 'y' && confirm != 'Y') {
                printf("The deletion of the contact has been canceled.\n");
                return -1;
            }

            // User entered yes. Proceed to delete:

            // The node we wish to delete is the head (first in the list)
            if (prevContact == currentContact) {

                // The node we wish to delete is the only node in the list
                if (currentContact->next == NULL) {

                    // Free the space for the contact we want to delete
                    free(currentContact->firstName);
                    free(currentContact->lastName);
                    free(currentContact->phoneNum);
                    free(currentContact->next);

                    // Set the contact to a nullptr
                    // (to avoid pointing at garbage values - "dangling pointers")
                    currentContact->firstName = NULL;
                    currentContact->lastName = NULL;
                    currentContact->phoneNum = NULL;
                    currentContact->next = NULL;

                    free(currentContact);
                    currentContact = NULL;

                    // Initialize the array ptr
                    // since this was the only item in the list
                    phonebook[firstLetterLastNameIndex] = currentContact;
                } else {

                    // The node we wish to delete is the head (first in the list)
                    // and it is not the only contact in the list
                    currentContact = currentContact->next;
                    free(prevContact);
                    prevContact = NULL;
                    phonebook[firstLetterLastNameIndex] = currentContact;
                }
            }

                // The node we wish to delete is a leaf (last in the list)
            else if (currentContact->next == NULL) {
                free(currentContact->firstName);
                free(currentContact->lastName);
                free(currentContact->phoneNum);

                currentContact->firstName = NULL;
                currentContact->lastName = NULL;
                currentContact->phoneNum = NULL;
                currentContact->next = NULL;

                free(currentContact);
                currentContact = NULL;

                prevContact->next = NULL;
            }

                // middle:
            else {
                prevContact->next = currentContact->next;
                free(currentContact);
                currentContact = NULL;
            }

            printf("The contact has been deleted successfully!\n");
            return 0;
        }

        prevContact = currentContact;
        currentContact = currentContact->next;
    }

    printf("The deletion of the contact has failed!\n");
    return 1;
}

int findContactByNum(Contact *phonebook[], int size) {
    printf("Enter a phone number: ");
    char phoneNum[SIZE];
    scanf("%s", phoneNum);

    // scan for phone number in each entry
    for (int i = 0; i < size; ++i) {
        Contact *currentEntry = phonebook[i];

        while (currentEntry != NULL) {
            if (strcmp(currentEntry->phoneNum, phoneNum) == 0) {
                printf("The following contact was found: %s %s %s\n",
                       currentEntry->firstName,
                       currentEntry->lastName,
                       currentEntry->phoneNum);
                return 0;
            }
            currentEntry = currentEntry->next;
        }
    }
    printf("No contact with a phone number "
           "%s was found in the phone book\n", phoneNum);
    return 1;
}

Contact *findContactByName(Contact *phonebook[]) {
    printf("Enter a contact name (<first name> <last name>): ");
    char firstName[SIZE], lastName[SIZE];
    scanf("%s %s", firstName, lastName);

    int IndexByLastName = letterIndex(lastName[0]);
    Contact *matchingLastNamelist = phonebook[IndexByLastName];

    // Look for the Contact in the matching list
    while (matchingLastNamelist != NULL) {
        if (strcmp(matchingLastNamelist->firstName, firstName) == 0 &&
            strcmp(matchingLastNamelist->lastName, lastName) == 0) {
            printf("The following contact was found: %s %s %s\n",
                   matchingLastNamelist->firstName,
                   matchingLastNamelist->lastName,
                   matchingLastNamelist->phoneNum);
            return matchingLastNamelist;
        }
        matchingLastNamelist = matchingLastNamelist->next;
    }
    printf("No contact with a name %s %s was found in the phone book\n",
           firstName, lastName);
    return NULL;
}

int updatePhoneNum(Contact *phonebook[], int size) {
    Contact *contactToUpdate = findContactByName(phonebook);
    if (contactToUpdate == NULL) {

        // The contact doesn't exist, abort;
        return 1;
    }

    printf("Enter the new phone number: ");
    char newPhoneNum[SIZE];
    scanf("%s", newPhoneNum);

    // Check if the number already exists
    for (int i = 0; i < size; ++i) {
        Contact *currentList = phonebook[i];

        while (currentList != NULL) {

            // Check if there is an existing contact with the same phone number
            if (strcmp(currentList->phoneNum, newPhoneNum) == 0) {
                printf("The update of the contact has failed, "
                       "since the phone number %s already exists!\n",
                       newPhoneNum);
                return 3;
            }

            // Move the pointer to the next Contact in the current list
            currentList = currentList->next;
        }
    }
    strcpy(contactToUpdate->phoneNum, newPhoneNum);
    printf("The contact has been updated successfully!\n");
    return 0;
}

void printPhonebook(Contact *phonebook[], int size) {
    for (int i = 0; i < size; ++i) {
        Contact *currentContact = phonebook[i];
        Contact *objToPrint = phonebook[i];
        if (currentContact == NULL) {

            // current list is Empty, continue to the next one
            continue;
        }

        int numOfContacts = 0;
        do {
            ++numOfContacts;
            currentContact = currentContact->next;
        } while (currentContact != NULL);

        for (int f = 0; f < numOfContacts; ++f) {
            for (int k = 1; k < numOfContacts - f; ++k) {
                objToPrint = objToPrint->next;
            }
            printf("%-10s %-10s %-10s\n",
                   objToPrint->firstName, objToPrint->lastName, objToPrint
                           ->phoneNum);
            objToPrint = phonebook[i];
        }
    }
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
    Contact *phonebook[ALPHABET_LENGTH] = {NULL};
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
                    findContactByName(phonebook);
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
                    teardown(phonebook);
                    exit(0);
                default:
                    printf("Wrong option, try again:\n");
                    break;
            }
        } else {
            printf("Wrong option, try again:\n");
            continue;
        }
    }
}
