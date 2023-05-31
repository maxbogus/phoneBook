#include <stdio.h>

int isPrime(long n)
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

long getNextPrime(long N)
{
    if (N <= 1)
        return 2;

    long prime = N;
    int found = 0;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found)
    {
        prime++;

        if (isPrime(prime))
            found = 1;
    }

    return prime;
}

int main()
{
    int result = 0;
    long number = 0;

    while (result == 0)
    {
        number = getNextPrime(133);
        result = isPrime(number);
    }

    printf("%ld", number);

    return 0;
}
