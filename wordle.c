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
struct s_words
{
    char **arr;
    int n;
};
typedef struct s_words Words;

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

Words readfile(char *filename, int max)
{
    char buf[8];
    int i;
    FILE *fd;
    char **ret = NULL;
    Words words = {NULL, 0};

    fd = fopen(filename, "r");
    if (!fd)
    {
        perror("Error opening file");
        return words;
    }

    ret = (char **)malloc(max * sizeof(char *));

    if (!ret)
    {
        fclose(fd);
        perror("Error allocating memory");
        return words;
    }

    for (i = 0; i < max; i++)
    {
        ret[i] = (char *)malloc(6 * sizeof(char));
    }

    i = 0;
    while (fgets(buf, 7, fd) && i < max)
    {
        size_t size = strlen(buf);
        if (size > 0 && buf[size - 1] == '\n')
        {
            buf[size - 1] = '\0';
            size--;
        }

        if (size == 5)
        {
            ret[i] = strdup(buf);
            if (!ret[i])
            {
                perror("Error allocating memory for word");
                break;
            }
            i++;
        }
    }

    fclose(fd);

    words.arr = ret;
    words.n = i;

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

void free_words(Words words)
{
    for (int i = 0; i < words.n; i++)
    {
        free(words.arr[i]);
    }
    free(words.arr);
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

    words = readfile("wordlist.txt", 5);
    if (!words.arr)
    {
        printf("%s\n", "Error");
    }
    print_words(words);
    free_words(words);

    return 0;
}