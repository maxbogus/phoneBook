#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
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
        for (index = 0; index < lastFreeIndex; index++)
        {
            struct PhoneEntry entry = entries[index];
            fprintf(phonebook, "%s, %s, %s\n", entry.phoneNumber,
                    entry.firstName, entry.secondName);
        }
        fclose(phonebook);
    }
}

int loadData(struct PhoneEntry *entries)
{
    FILE *phonebook = fopen(PHONEBOOK_BASE_NAME, "r");
    int result = 0;
    if (!phonebook)
        printf("Can't open file\n");
    else
    {
        char buffer[PHONEBOOK_SIZE];

        int row = 0;
        int column = 0;
        while (fgets(buffer,
                     PHONEBOOK_SIZE, phonebook))
        {
            column = 0;
            row++;
            if (row == 1)
                continue;

            char *value = strtok(buffer, ", ");
            int index = row - 2;
            result = index;
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
        fclose(phonebook);
    }
    return result;
}

void showEntries(struct PhoneEntry *entries, int lastFreeIndex)
{
    int index = 0;
    while (index <= lastFreeIndex)
    {
        printf("phone: %s firstName: %s surname: %s \n", entries[index].phoneNumber, entries[index].firstName, entries[index].secondName);
        index++;
    }
}
bool applyChanges()
{
    char answer[1] = "";
    getInput(answer, "Apply? Yes - 1 | No - Other");
    return strcmp(answer, "1");
}

void editEntry(const struct PhoneEntry *entries, int lastFreeIndex)
{
    struct PhoneEntry entry;
    bool exit = false;
    bool apply = false;

    while (!exit)
    {
        char selectedEntry[1] = "";
        printf("Entries to modify: 0 - %d \n", lastFreeIndex);
        getInput(selectedEntry, "What entry do you want to modify?");
        int index = (int)*selectedEntry - '0';
        if (0 <= index || index <= lastFreeIndex)
        {
            printf("Current entry:");
            entry = entries[index];
            printf("Phone: %s \tName: %s \t Surname: %s.", entry.phoneNumber, entry.firstName, entry.secondName);
            char selectedField[1] = "";
            getInput(selectedField, "What field do you want to modify? 1 - Phone; 2 - Name; 3 - Surname; Other - exit");
            int selection = (int)*selectedField;
            char phoneNumber[15] = "";
            char firstName[15] = "";
            char secondName[15] = "";
            switch (selection)
            {
            case 1:
                printf("Current value: %s", entry.phoneNumber);
                getInput(phoneNumber, "Enter new value:");
                apply = applyChanges();
                if (apply)
                {
                    strcpy(entries[index].phoneNumber, phoneNumber);
                }
                exit = true;
                break;
            case 2:
                printf("Current value: %s", entry.firstName);
                getInput(firstName, "Enter new value:");
                apply = applyChanges();
                if (apply)
                {
                    strcpy(entries[index].firstName, firstName);
                }
                exit = true;
                break;
            case 3:
                printf("Current value: %s", entry.secondName);
                getInput(secondName, "Enter new value:");
                apply = applyChanges();
                if (apply)
                {
                    strcpy(entries[index].secondName, secondName);
                }
                exit = true;
                break;
            default:
                exit = true;
            }
        }
        else
        {
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
    // TODO: Edit struct
    // TODO: Sort struct
    // TODO: Search struct

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
