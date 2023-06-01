#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototype.h"

struct PhoneEntry *phoneBook;
int capacity = 10;
int size = 0;
int charLimit = 15;

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

void init_array()
{
    capacity = getPrime(capacity);
    phoneBook = (struct PhoneEntry *)malloc(capacity * sizeof(struct PhoneEntry));
    for (int index = 0; index < capacity; index++)
    {
        phoneBook[index].key = 0;
        char emptyString[15] = {'\0'};
        strcpy(phoneBook[index].phoneNumber, emptyString);
        strcpy(phoneBook[index].firstName, emptyString);
        strcpy(phoneBook[index].secondName, emptyString);
    }
}

void insert(int key, char phoneNumber[charLimit], char firstName[charLimit], char secondName[charLimit])
{
    int index = hashFunction(key);
    if (strlen(phoneBook[index].phoneNumber) == 0)
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
    if (strlen(phoneBook[index].phoneNumber) == 0)
    {
        printf("\n This key does not exist \n");
    }
    else
    {
        phoneBook[index].key = 0;
        strcpy(phoneBook[index].phoneNumber, "");
        strcpy(phoneBook[index].firstName, "");
        strcpy(phoneBook[index].secondName, "");
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
            printf("\n key: %d array[%d]: %s, %s, %s \t", phoneBook[index].key, index, phoneBook[index].phoneNumber, phoneBook[index].firstName, phoneBook[index].secondName);
        }
    }
}

int size_of_hashtable()
{
    return size;
}

int main()
{
    int choice, key, n;

    char phoneNumber[charLimit], firstName[charLimit], secondName[charLimit];
    int c = 0;
    init_array();

    do
    {
        printf("Welcome to the Phone book app!"
                "\n1 - Add|Edit item"
                "\n2 - Delete item"
                "\n3 - Show number of items in hashTable"
                "\n4 - View (Desc)"
                "\n5 - Import"
                "\n6 - Export"
                "\n\n Please enter your choice: ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            printf("Enter key -:\t");
            scanf("%d%*c", &key);
            printf("Enter phoneNumber -:\t");
            scanf("%[^\n]%*c",phoneNumber);
            printf("Enter firstName -:\t");
            scanf("%[^\n]%*c",firstName);
            printf("Enter secondtName -:\t");
            scanf("%[^\n]%*c",secondName);
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

            display();

            break;

        case 5:

            display();

            break;

        case 6:

            display();

            break;

        default:

            printf("Invalid Input\n");
        }

        printf("\nDo you want to continue (press 1 for yes): ");
        scanf("%d", &c);

    } while (c == 1);
}
