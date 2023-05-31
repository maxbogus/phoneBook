#include <stdio.h>
#include <string.h>
#include <math.h>

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

int main()
{
    long SIZE = 7;
    char phone[12] = "89162374500";
    char phoneTwo[12] = "89162374501";
    char phoneThree[12] = "89162374449";
    char phoneFour[12] = "89162374502";
    char phoneFive[12] = "89162374503";
    char phoneSix[12] = "89162374448";
    long result = convertPhone(phone);
    long resultTwo = convertPhone(phoneTwo);
    long resultThree = convertPhone(phoneThree);
    long resultFour = convertPhone(phoneFour);
    long resultFive = convertPhone(phoneFive);
    long resultSix = convertPhone(phoneSix);
    printf("%s\t%ld\t%ld\n", phone, result, result % SIZE);
    printf("%s\t%ld\t%ld\n", phoneTwo, resultTwo, resultTwo % SIZE);
    printf("%s\t%ld\t%ld\n", phoneThree, resultThree, resultThree % SIZE);
    printf("%s\t%ld\t%ld\n", phoneFour, resultFour, resultFour % SIZE);
    printf("%s\t%ld\t%ld\n", phoneFive, resultFive, resultFive % SIZE);
    printf("%s\t%ld\t%ld\n", phoneSix, resultSix, resultSix % SIZE);

    return 0;
}
