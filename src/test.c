#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

const char *fileName = "testData.csv";
const char FILE_SIZE = 1;

void generateName(char *str, int limit)
{
    int index;
    for (index = 0; index < limit; index++)
    {
        int charNumber = rand() % 24;
        str[index] = (index == 0) ? (charNumber + 'A') : (charNumber + 'a');
    }
}

void generatePhone(char *str, int limit)
{
    int index;
    for (index = 0; index <= limit; index++)
    {
        int charNumber = rand() % 9;
        str[index] = (charNumber) + '0';
    }
}

void createFile()
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

            char name[4] = {};
            generateName(name, 4);

            char surname[5];
            generateName(surname, 5);

            fprintf(file, "%d,%s,%s,%s\n", index, phone, name, surname);
        }
        printf("Generation complete.\n");
        fclose(file);
    }
}

int replaceLine()
{
    return 0;
}

int finsert(FILE *file, const char *buffer)
{

    long int insert_pos = ftell(file);
    if (insert_pos < 0)
        return insert_pos;

    // Grow from the bottom
    int seek_ret = fseek(file, 0, SEEK_END);
    if (seek_ret)
        return seek_ret;
    long int total_left_to_move = ftell(file);
    if (total_left_to_move < 0)
        return total_left_to_move;

    char move_buffer[1024];
    long int ammount_to_grow = strlen(buffer);
    if (ammount_to_grow >= sizeof(move_buffer))
        return -1;

    total_left_to_move -= insert_pos;

    for (;;)
    {
        long int ammount_to_move = sizeof(move_buffer);
        if (total_left_to_move < ammount_to_move)
            ammount_to_move = total_left_to_move;

        long int read_pos = insert_pos + total_left_to_move - ammount_to_move;

        seek_ret = fseek(file, read_pos, SEEK_SET);
        if (seek_ret)
            return seek_ret;
        fread(move_buffer, ammount_to_move, 1, file);
        if (ferror(file))
            return ferror(file);

        seek_ret = fseek(file, read_pos + ammount_to_grow, SEEK_SET);
        if (seek_ret)
            return seek_ret;
        fwrite(move_buffer, ammount_to_move, 1, file);
        if (ferror(file))
            return ferror(file);

        total_left_to_move -= ammount_to_move;

        if (!total_left_to_move)
            break;
    }

    seek_ret = fseek(file, insert_pos, SEEK_SET);
    if (seek_ret)
        return seek_ret;
    fwrite(buffer, ammount_to_grow, 1, file);
    if (ferror(file))
        return ferror(file);

    return 0;
}

void writeToExactPosition()
{
    FILE *file = fopen(fileName, "r+");
    assert(file);

    const char *to_insert = "10,12345678901,MM,NN\n";

    fseek(file, 1, SEEK_SET);
    finsert(file, to_insert);

    assert(ferror(file) == 0);
    fclose(file);
}

int main()
{
    int exitCode = 0;
    writeToExactPosition();
    createFile();

    return exitCode;
}
