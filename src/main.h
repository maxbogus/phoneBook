#define BUFFERSIZE 15
#define CONFIRM_MODIFICATION "Yes (1) | No (Other)"
#define PHONEBOOK_BASE_NAME "phonebook.csv"
#define PHONEBOOK_SIZE 1024
#define SELECT_ENTRY_TO_MODIFY "What entry do you want to modify?"
#define SELECT_FIELD_TO_MODIFY "What field do you want to modify? 1 - Phone; 2 - Name; 3 - Surname; Other - exit"

struct PhoneEntry
{
    char phoneNumber[BUFFERSIZE];
    char firstName[BUFFERSIZE];
    char secondName[BUFFERSIZE];
};
