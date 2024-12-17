/*wordle.txt*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 4

#define MAX_WORDS 5
#define WORD_LENGTH 6

typedef struct
{
    char arr[MAX_WORDS][WORD_LENGTH];
    int n;
} Words;

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

Words readfile(char *filename)
{
    char buf[8];
    FILE *fd;
    Words words = {0};

    fd = fopen(filename, "r");
    if (!fd)
    {
        perror("Error opening file");
        return words;
    }

    while (fgets(buf, sizeof(buf), fd) && words.n < MAX_WORDS)
    {
        size_t size = strlen(buf);
        if (size > 0 && buf[size - 1] == '\n')
        {
            buf[size - 1] = '\0';
        }

        if (size - 1 == 5)
        {
            strncpy(words.arr[words.n], buf, WORD_LENGTH);
            words.arr[words.n][WORD_LENGTH - 1] = '\0';
            words.n++;
        }
    }

    fclose(fd);
    return words;
}

void print_words(Words words)
{
    int i;
    for (i = 0; i < words.n; i++)
    {
        printf("%s\n", words.arr[i]);
    }
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
    Words words;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s CORRECTWORD GUESSWORD", argv[0]);
        return -1;
    }

    correct = argv[1];
    guess = argv[2];

    res = cw(correct, guess);
    Example_print_result(res);

    words = readfile("wordlist.txt");
    print_words(words);
    printf("%d", words.n);

    return 0;
}