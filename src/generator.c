#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

char names[24][10] = {
    "Maria", "Nushi", "Mohammed", "Jose", "Wei", "Ahmed", "Yan", "Ali", "John", "David", "Abdul", "Ana", "Ying",
    "Michael", "Juan", "Mary", "Jean", "Robert", "Daniel", "Luis", "Carlos", "James", "Antonio", "Joseph"};

char surnames[37][11] = {
    "Wang", "Smith", "Devi", "Ivanov", "Kim", "Ali", "García", "Müller", "Mohamed", "Tesfaye", "Nguyen", "Ilunga",
    "González", "Deng", "Rodríguez", "Moyo", "Hansen", "Hoxha", "Smirnov", "Kuznetsov", "Popov", "Sokolov",
    "Lebedev", "Kozlov", "Novikov", "Morozov", "Petrov", "Volkov", "Solovyov", "Vasilyev", "Zaytsev", "Pavlov",
    "Semyonov", "Golubev", "Vinogradov", "Bogdanov", "Vorobyov"};

void generatePhone(char *str, int limit)
{
    int index;
    int charNumber = 8;
    for (index = 0; index <= limit; index++)
    {
        switch (index)
        {
        case 0:
            break;
        case 1:
            charNumber = 9;
            break;
        case 2:
            charNumber = index % 3;
            break;
        default:
            charNumber = rand() % 9;
            break;
        }
        str[index] = (index != limit) ? (charNumber) + '0' : '\0';
    }
}

int main()
{
    FILE *file;
    if ((file = fopen(fileName, "w+")) != NULL)
    {
        printf("Started file generation:\n");
        int index;
        fprintf(file, "Phonenumber,Name,Surname\n");
        for (index = 0; index < FILE_SIZE; index++)
        {
            char phone[11];
            generatePhone(phone, 10);
            fprintf(file, "%s, %s, %s\n", phone, names[index % 23], surnames[index % 36]);
        }
        printf("Generation complete.\n");
        fclose(file);
    }

    return 0;
}
