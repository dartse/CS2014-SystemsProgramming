#include <stdio.h>

void testThings1(char *w, char *r)
{
    printf("%d\n", !(*w & 1));
    printf("%d\n", !(*r & 1));
}

void printBin(unsigned num)
{
    unsigned mask = 2147483648;
    for (int i = 0; i < 32; i++)
    {
        if ((num & mask) == 0)
            printf("0");
        else
            printf("1");
        num <<= 1;
    }
    printf("\n");
}

void testThings2()
{
    printBin((int)"“");
    // printBin((int)"ˆ");
    // printBin((int)"s");
    // printBin((int)"x");
    // printf("\n");
    // printBin((int)"ޜ");
    // printBin((int)"=");
}

void testThings3(){
    FILE *readFile = fopen("encode.input", "r");
    char currentChar = fgetc(readFile);
    while (!feof(readFile))
    {
        char buffer[10];
        for (int j = 7; j >= 0; j--)
        {
            buffer[j] = ((currentChar >> j) & 1) + '0';
        }
        buffer[8] = '\0';
        currentChar = fgetc(readFile);
        printf("%s\n", buffer);
    }
}


int main(int argc, char **argv)
{
    // testThings1("w", "r");
    testThings2();
//    testThings3();
}