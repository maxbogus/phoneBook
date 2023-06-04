#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "prototype.h"

struct PhoneEntry *phoneBook;
struct PhoneEntry *tempPhoneBook;
int capacity = 10;
int size = 0;
int charLimit = 15;
char emptyString[15] = {'\0'};

int hashFunction(int key)
{
    return (key % capacity);
}

int checkPrime(int n)
{
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;

    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;

    return 1;
}

int getPrime(int n)
{
    if (n % 2 == 0)
    {
        n++;
    }
    while (!checkPrime(n))
    {
        n += 2;
    }
    return n;
}

void insert(int key, char phoneNumber[charLimit], char firstName[charLimit], char secondName[charLimit])
{
    int index = hashFunction(key);
    if (
        strlen(phoneBook[index].phoneNumber) == 0 && strlen(phoneBook[index].firstName) == 0 && strlen(phoneBook[index].secondName) == 0)
    {
        phoneBook[index].key = key;
        strcpy(phoneBook[index].phoneNumber, phoneNumber);
        strcpy(phoneBook[index].firstName, firstName);
        strcpy(phoneBook[index].secondName, secondName);
        size++;
        printf("\n Key (%d) has been inserted \n", key);
    }
    else if (phoneBook[index].key == key)
    {
        strcpy(phoneBook[index].phoneNumber, phoneNumber);
        strcpy(phoneBook[index].firstName, firstName);
        strcpy(phoneBook[index].secondName, secondName);
    }
    else
    {
        printf("\n Collision occured  \n");
    }
}

void remove_element(int key)
{
    int index = hashFunction(key);
    if (
        strlen(phoneBook[index].phoneNumber) == 0 && strlen(phoneBook[index].firstName) == 0 && strlen(phoneBook[index].secondName) == 0)
    {
        printf("\n This key does not exist \n");
    }
    else
    {
        phoneBook[index].key = 0;
        strcpy(phoneBook[index].phoneNumber, emptyString);
        strcpy(phoneBook[index].firstName, emptyString);
        strcpy(phoneBook[index].secondName, emptyString);
        size--;
        printf("\n Key (%d) has been removed \n", key);
    }
}

void display()
{
    int index;
    for (index = 0; index < capacity; index++)
    {
        if (strlen(phoneBook[index].phoneNumber) == 0)
        {
            printf("\n array[%d]: / ", index);
        }
        else
        {
            printf("\n key: %d: %s, %s, %s \t", phoneBook[index].key, phoneBook[index].phoneNumber, phoneBook[index].firstName, phoneBook[index].secondName);
        }
    }
}

void displayBackward()
{
    int index;
    for (index = capacity - 1; index >= 0; index--)
    {
        if (strlen(phoneBook[index].phoneNumber) == 0)
        {
            printf("\n array[%d]: / ", index);
        }
        else
        {
            printf("\n key: %d array[%d]: %s, %s, %s \t", phoneBook[index].key, index, phoneBook[index].phoneNumber, phoneBook[index].firstName, phoneBook[index].secondName);
        }
    }
}

int size_of_hashtable()
{
    return size;
}

void saveToFile()
{
    FILE *phonebook;
    phonebook = fopen(PHONEBOOK_BASE_NAME, "w");
    if (!phonebook)
        printf("Can't open file\n");
    else
    {
        fprintf(phonebook, "Phonenumber, Name, Surname\n");
        int index;
        for (index = 0; index <= size; index++)
        {
            struct PhoneEntry entry = phoneBook[index];
            fprintf(phonebook, "%s, %s, %s", entry.phoneNumber,
                    entry.firstName, entry.secondName);
        }
        fclose(phonebook);
    }
}

long convertPhone(char *phone)
{
    long result = 0;
    int index;

    for (index = 0; index < ((int)strlen(phone)); index++)
    {
        int number = phone[index] - '0';
        long power = (long)pow(10, strlen(phone) - (index + 1));
        long mult = number * power;
        result += mult;
    }

    return result;
}

void init_array()
{
    capacity = size;
    capacity = getPrime(capacity);
    phoneBook = (struct PhoneEntry *)malloc(capacity * sizeof(struct PhoneEntry));
    printf("%d, %d", size, capacity);
    for (int index = 0; index < capacity; index++)
    {
        if (index < size)
        {
            phoneBook[index].key = index;
            strcpy(phoneBook[index].phoneNumber, tempPhoneBook[index].phoneNumber);
            strcpy(phoneBook[index].firstName, tempPhoneBook[index].firstName);
            strcpy(phoneBook[index].secondName, tempPhoneBook[index].secondName);
        }
        else
        {
            phoneBook[index].key = 0;
            strcpy(phoneBook[index].phoneNumber, emptyString);
            strcpy(phoneBook[index].firstName, emptyString);
            strcpy(phoneBook[index].secondName, emptyString);
        }
    }
}

int loadData()
{
    FILE *phonebook = fopen(PHONEBOOK_BASE_NAME, "r");
    int row = 0;
    if (!phonebook)
        printf("Can't open file\n");
    else
    {
        tempPhoneBook = (struct PhoneEntry *)calloc(capacity, sizeof(struct PhoneEntry));
        char buffer[1024];
        while (fgets(buffer,
                     1024, phonebook))
        {
            if (row >= capacity)
            {
                capacity += 1;
                struct PhoneEntry *temp;
                temp = (struct PhoneEntry *)realloc(tempPhoneBook, capacity * sizeof(struct PhoneEntry));
                if (temp != NULL)
                {
                    tempPhoneBook = temp;
                }
                else
                {
                    printf("problem");
                    return -1;
                }
            }
            char *value = strtok(buffer, ", ");
            if (row != 0)
            {
                int column;
                column = 0;
                printf("%s\n", value);
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
                        // long phoneNumber = convertPhone(entry.phoneNumber);
                        int index = row - 1;
                        entry.key = index;
                        tempPhoneBook[index] = entry;
                        printf("phone: %s firstName: %s surname: %s index = %d\n", tempPhoneBook[index].phoneNumber, tempPhoneBook[index].firstName, tempPhoneBook[index].secondName, index);
                    }
                    value = strtok(NULL, ", ");
                    column++;
                }
            }
            row++;
        }

        fclose(phonebook);
    }

    return row - 1;
}

int main()
{
    int choice, key, n;
    char phoneNumber[charLimit], firstName[charLimit], secondName[charLimit];

    int c = 0;
    size = loadData();

    init_array();

    do
    {
        printf("Welcome to the Phone book app!"
               "\n1 - Add|Edit item"
               "\n2 - Delete item"
               "\n3 - Show number of items in hashTable"
               "\n4 - View (Desc)"
               "\n5 - View (Asc)"
               "\n6 - Export"
               "\n7 - Export"
               "\n\n Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key -:\t");
            scanf("%d%*c", &key);
            printf("Enter phoneNumber -:\t");
            scanf("%[^\n]%*c", phoneNumber);
            printf("Enter firstName -:\t");
            scanf("%[^\n]%*c", firstName);
            printf("Enter secondtName -:\t");
            scanf("%[^\n]%*c", secondName);
            insert(key, phoneNumber, firstName, secondName);

            break;
        case 2:
            printf("Enter the key to delete-:");
            scanf("%d", &key);
            remove_element(key);

            break;
        case 3:
            n = size_of_hashtable();
            printf("Size of Hash Table is-:%d\n", n);

            break;
        case 4:
            displayBackward();

            break;
        case 5:
            display();

            break;
        case 6:
            saveToFile();

            break;
        case 7:
            size = loadData();
            init_array();

            break;
        default:
            printf("Invalid Input\n");
        }

        printf("\nDo you want to continue (press 1 for yes): ");
        scanf("%d", &c);

    } while (c == 1);
}
