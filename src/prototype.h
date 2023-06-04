#define BUFFERSIZE 15
#define PHONEBOOK_BASE_NAME "phonebook.csv"

struct PhoneEntry
{
    int key;
    char phoneNumber[BUFFERSIZE];
    char firstName[BUFFERSIZE];
    char secondName[BUFFERSIZE];
};
