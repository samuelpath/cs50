// Instructions: https://docs.cs50.net/2018/x/psets/1/mario/more/mario.html

#include <stdio.h>
#include <cs50.h>

int getHeight(void);
void printDoubleHalfPyramid(int height);
void printLine(int lineIdx, int height);
void printHashSigns(int n);
void printSpaces(int n);

int main(void)
{
    int height = getHeight();
    printDoubleHalfPyramid(height);
}

int getHeight(void)
{
    int height;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    return height;
}

void printDoubleHalfPyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        printLine(i, height);
    }
}

void printLine(int lineIdx, int height)
{
    printSpaces(height - lineIdx);
    printHashSigns(lineIdx);
    printSpaces(2);
    printHashSigns(lineIdx);
    printf("\n");
}

void printHashSigns(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    return;
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}