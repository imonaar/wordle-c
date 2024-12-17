/*wordle.txt*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 4

typedef char Result;

void Example_print_result(Result *);
Result cc(char, int, char *);
Result *cw(char *, char *);
bool isin(char, char *);
int main(int, char **);

Result cc(char guess, int idx, char *correct_word)
{
    char correct;
    correct = correct_word[idx];

    if (guess == correct)
    {
        return ResultGreen;
    }
    else if (isin(guess, correct_word))
    {
        return ResultYellow;
    }

    return ResultRed;
}

Result *cw(char *correct, char *guess)
{
    static Result res[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        res[i] = cc(guess[i], i, correct);
    }
    return res;
}

bool isin(char c, char *word)
{
    bool ret;
    int i, size;

    ret = false;
    size = strlen(word);

    for (i = 0; i < size; i++)
    {
        if (word[i] == c)
        {
            ret = true;
            break;
        }
    }
    return ret;
}

void Example_print_result(Result *res)
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
            printf("Unknown: %d\n", res[i]);
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
        fprintf(stderr, "Usage: %s CORRECTWORD GUESSWORD", argv[0]);
        return -1;
    }

    correct = argv[1];
    guess = argv[2];

    res = cw(correct, guess);
    Example_print_result(res);

    return 0;
}