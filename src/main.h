#define BUFFERSIZE 15
#define PHONEBOOK_SIZE 1024
#define PHONEBOOK_BASE_NAME "phonebook.csv"

struct PhoneEntry
{
    char phoneNumber[BUFFERSIZE];
    char firstName[BUFFERSIZE];
    char secondName[BUFFERSIZE];
};
