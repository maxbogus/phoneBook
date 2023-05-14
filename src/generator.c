#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "generator.h"

char names[24][10] = {
    "Maria",
    "Nushi",
    "Mohammed",
    "Jose",
    "Wei",
    "Ahmed",
    "Yan",
    "Ali",
    "John",
    "David",
    "Abdul",
    "Ana",
    "Ying",
    "Michael",
    "Juan",
    "Mary",
    "Jean",
    "Robert",
    "Daniel",
    "Luis",
    "Carlos",
    "James",
    "Antonio",
    "Joseph",
};

char surnames[17][11] = {"Wang",
                         "Smith", "Devi",
                         "Ivanov",
                         "Kim", "Ali",
                         "García",
                         "Müller", "Mohamed",
                         "Tesfaye",
                         "Nguyen", "Ilunga",
                         "González",
                         "Deng", "Rodríguez",
                         "Moyo",
                         "Hansen"};

void generatePhone(char *str, int limit)
{
    int index;
    for (index = 0; index <= limit; index++)
    {
        int charNumber = 8;
        if (index == 0)
        {
        }
        else if (index == 1)
        {
            charNumber = 9;
        }
        else if (index == 2)
        {
            charNumber = index % 3;
        }
        else
        {
            charNumber = rand() % 9;
        }

        str[index] = (charNumber) + '0';
    }
}

int main()
{
    FILE *file;
    if ((file = fopen(fileName, "w+")) != NULL)
    {
        printf("Started file generation:\n");
        int index;
        fprintf(file, "ID,Phonenumber,Name,Surname\n");
        for (index = 0; index < FILE_SIZE; index++)
        {
            char phone[11];
            generatePhone(phone, 11);
            fprintf(file, "%d,%s,%s,%s\n", index, phone, names[index % 23], surnames[index % 16]);
        }
        printf("Generation complete.\n");
        fclose(file);
    }

    return 0;
}
