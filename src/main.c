#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"

void getInput(char *buffer, const char *text)
{
    fflush(stdin);
    printf("%s\n", text);
    while (true)
    {
        assert(fgets(buffer, BUFFERSIZE, stdin) != NULL);
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
            break;
        }
    }
}

void addEntry(struct PhoneEntry *entries, int lastFreeIndex)
{
    struct PhoneEntry entry = {};
    getInput(entry.phoneNumber, "Enter phone number:\n");
    getInput(entry.firstName, "Enter name:\n");
    getInput(entry.secondName, "Enter surname:\n");
    printf("%s", "Output:");
    printf("%s %s %s \n", entry.phoneNumber, entry.firstName, entry.secondName);
    entries[lastFreeIndex] = entry;
    printf("Press Any Key to Continue\n");
    getchar();
    fflush(stdin);
}

int getSelection(const char *question)
{
    fflush(stdin);
    int selectedField = 0;
    printf("%s\n", question);
    selectedField = getchar();
    return selectedField - '0';
}

enum AppState
{
    Add,
    Edit,
    Search,
    Export,
    Import,
    View,
    Sort,
    Exit
};

void saveToFile(const struct PhoneEntry *entries, int lastFreeIndex)
{
    FILE *phonebook;
    phonebook = fopen(PHONEBOOK_BASE_NAME, "w");
    if (!phonebook)
        printf("Can't open file\n");
    else
    {
        fprintf(phonebook, "Phonenumber, Name, Surname\n");
        int index;
        for (index = 0; index <= lastFreeIndex; index++)
        {
            struct PhoneEntry entry = entries[index];
            fprintf(phonebook, "%s, %s, %s", entry.phoneNumber,
                    entry.firstName, entry.secondName);
        }
        fclose(phonebook);
    }
}

int loadData(struct PhoneEntry *entries)
{
    FILE *phonebook = fopen(PHONEBOOK_BASE_NAME, "r");
    int index = 0;
    if (!phonebook)
        printf("Can't open file\n");
    else
    {
        char buffer[PHONEBOOK_SIZE];
        int row = 0;
        while (fgets(buffer,
                     PHONEBOOK_SIZE, phonebook))
        {
            char *value = strtok(buffer, ", ");
            index = row - 1;
            if (row != 0)
            {
                int column;
                column = 0;
                while (value)
                {
                    struct PhoneEntry entry;
                    if (column == 0)
                    {
                        strcpy(entry.phoneNumber, value);
                    }

                    // Column 2
                    if (column == 1)
                    {
                        strcpy(entry.firstName, value);
                    }

                    // Column 3
                    if (column == 2)
                    {
                        strcpy(entry.secondName, value);
                        entries[index] = entry;
                        printf("phone: %s firstName: %s surname: %s index = %d\n", entries[index].phoneNumber, entries[index].firstName, entries[index].secondName, index);
                    }
                    value = strtok(NULL, ", ");
                    column++;
                }
            }
            row++;
        }

        fclose(phonebook);
    }
    return index;
}

void showEntries(struct PhoneEntry *entries, int lastFreeIndex)
{
    if (lastFreeIndex > 0)
    {
        int index = 0;
        while (index <= lastFreeIndex)
        {
            printf("phone: %s firstName: %s surname: %s \n", entries[index].phoneNumber, entries[index].firstName, entries[index].secondName);
            index++;
        }
    }
    else
    {
        printf("No entries. \n");
    }
}

void editEntry(struct PhoneEntry *entries, int lastFreeIndex)
{
    struct PhoneEntry entry;
    bool exit = false;
    while (!exit)
    {
        printf("Entries to modify: 0 - %d \n", lastFreeIndex);
        int index = getSelection(SELECT_ENTRY_TO_MODIFY);
        if (0 <= index || index <= lastFreeIndex)
        {
            printf("Current entry:\n");
            entry = entries[index];
            printf("Phone: %s \tName: %s \t Surname: %s.", entry.phoneNumber, entry.firstName, entry.secondName);

            int selection = getSelection(SELECT_FIELD_TO_MODIFY);
            char phoneNumber[15];
            char firstName[15];
            char secondName[15];
            strcpy(phoneNumber, entry.phoneNumber);
            strcpy(firstName, entry.firstName);
            strcpy(secondName, entry.secondName);
            switch (selection)
            {
            case 1:
                printf("Current value: %s\n", entry.phoneNumber);
                getInput(phoneNumber, "Enter new value:");
                break;
            case 2:
                printf("Current value: %s\n", entry.firstName);
                getInput(firstName, "Enter new value:");
                break;
            case 3:
                printf("Current value: %s\n", entry.secondName);
                getInput(secondName, "Enter new value:");
                break;
            };

            int apply = 0;
            apply = getSelection(CONFIRM_MODIFICATION);
            if (apply == 1)
            {
                strcpy(entry.phoneNumber, phoneNumber);
                strcpy(entry.firstName, firstName);
                strcpy(entry.secondName, secondName);
                printf("\nPhone: %s \tName: %s \t Surname: %s.", entry.phoneNumber, entry.firstName, entry.secondName);
                entries[index] = entry;
            }
            exit = true;
        }
    }
}

enum AppState selectState(int input)
{
    enum AppState appState;
    switch (input)
    {
    case 49:
        appState = Add;
        break;
    case 50:
        appState = Edit;
        break;
    case 51:
        appState = Sort;
        break;
    case 52:
        appState = View;
        break;
    case 53:
        appState = Export;
        break;
    case 54:
        appState = Search;
        break;
    case 55:
        appState = Import;
        break;
    default:
        appState = Exit;
    }
    return appState;
}

void printMenu()
{
    // system("clear");
    printf("Welcome to the Phone book app!\n");
    printf("Select mode:\n");
    printf("1 - Add\n");
    printf("2 - Edit\n");
    printf("3 - Sort\n");
    printf("4 - View\n");
    printf("5 - Export\n");
    printf("6 - Search\n");
    printf("7 - Import\n");
    printf("0 - Exit\n");
}

int main()
{
    // TODO: Sort struct
    // TODO: Search struct
    // TODO: allocate file dynamically while loading file

    // generate test data
    int exitCode = 0;
    enum AppState appState = Import;
    struct PhoneEntry entries;
    int lastFreeIndex = 0;

    while (appState != Exit)
    {
        switch (appState)
        {
        case Add:
            addEntry(&entries, lastFreeIndex);
            lastFreeIndex++;
            break;
        case Edit:
            editEntry(&entries, lastFreeIndex);
            break;
        case Sort:
            printf("not implemented \n");
            break;
        case View:
            showEntries(&entries, lastFreeIndex);
            break;
        case Export:
            saveToFile(&entries, lastFreeIndex);
            break;
        case Search:
            printf("not implemented \n");
            break;
        case Import:
            lastFreeIndex = loadData(&entries);
            break;
        case Exit:
            return 0;
            break;
        }
        printMenu();
        int input;
        input = getchar();
        appState = selectState(input);
        fflush(stdin);
    }

    return exitCode;
}
