#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 4

typedef char Result;

bool isin(char, char *);
Result cc(char guess, int idx, char *word);
Result *cw(char *, char *);
void Example_print(Result *);
int main(int, char **);

bool isin(char c, char *word)
{
    int size, i;
    bool in;

    in = false;
    size = strlen(word);

    for (i = 0; i < size; i++)
    {
        if (word[i] == c)
        {
            in = true;
            break;
        }
    }
    return in;
}

Result cc(char guess, int idx, char *coreect_word)
{
    char correct;
    correct = coreect_word[idx];

    if (guess == correct)
    {
        return ResultGreen;
    }
    else if (isin(guess, coreect_word))
    {
        return ResultYellow;
    }

    return ResultRed;
}

Result *cw(char *guess, char *correct)
{
    static Result res[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        res[i] = cc(guess[i], i, correct);
    }

    return res;
}

void Example_print(Result *res)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        switch (res[i])
        {
        case ResultGreen:
            printf("%s\n", "Green");
            break;
        case ResultYellow:
            printf("%s\n", "Yellow");
            break;
        case ResultRed:
            printf("%s\n", "Red");
            break;
        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char *correct;
    char *guess;
    Result *res;

    if (argc < 3)
    {
        fprintf(stderr, "Error: %s CORRECTWORD GUESSWORD\n", argv[0]);
        return -1;
    }

    correct = argv[1];
    guess = argv[2];
    res = cw(guess, correct);
    Example_print(res);

    return 0;
}