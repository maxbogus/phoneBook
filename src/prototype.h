#define BUFFERSIZE 15

struct set
{
    int key;
    int data;
};

struct PhoneEntry
{
    int key;
    char phoneNumber[BUFFERSIZE];
    char firstName[BUFFERSIZE];
    char secondName[BUFFERSIZE];
};
