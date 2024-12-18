#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 4

#define MAX_WORDS 5172
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 5

#define ClrGreen "\033[0;32m"
#define ClrYellow "\033[0;33m"
#define ClrRed "\033[0;31m"
#define ClrStop "\033[0m"

typedef char Result;
typedef struct
{
    char arr[MAX_WORDS][WORD_LENGTH + 1]; //+1 for null terminator
    int count;
} Words;

bool continuation;
int rounds;
bool corrects[WORD_LENGTH];
bool win;

void print_result(Result *, char *, char *);
Result evaluate_guess(char, int, const char *);
Result *check_word(const char *, char *);
bool isin(char, const char *);
Words readfile(char *);
char *get_random_word(Words);
void prompt(char *);
char *readline(void);
void gameloop(char *, Words);
void display_prompt(char *);
bool is_valid_word(const char *, Words);
int main(int, char **);

Result evaluate_guess(char guess, int index, const char *target_word)
{
    if (guess == target_word[index])
    {
        corrects[index] = true;
        return ResultGreen;
    }

    return isin(guess, target_word) ? ResultYellow : ResultRed;
}

Result *check_word(const char *target_word, char *guess)
{
    static Result results[WORD_LENGTH];
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        results[i] = evaluate_guess(guess[i], i, target_word);
    }
    return results;
}

bool isin(char c, const char *word)
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
    char buf[WORD_LENGTH + 2]; // +2 for newline and null terminator
    Words word_list = {0};
    FILE *fd = fopen(filename, "r");

    if (!fd)
    {
        perror("Error opening file");
        return word_list;
    }

    while (fgets(buf, sizeof(buf), fd) && word_list.count < MAX_WORDS)
    {
        int length = strlen(buf);
        if (length > 0 && buf[length - 1] == '\n')
        {
            buf[length - 1] = '\0';
        }

        if (length - 1 == WORD_LENGTH)
        {
            strncpy(word_list.arr[word_list.count], buf, WORD_LENGTH);
            word_list.arr[word_list.count][length - 1] = '\0';
            word_list.count++;
        }
    }

    fclose(fd);
    return word_list;
}

char *get_random_word(Words words)
{
    static char res[6];

    if (words.count == 0)
    {
        return NULL;
    }

    int random_index = rand() % words.count;
    strcpy(res, words.arr[random_index]);
    return res;
}

void display_prompt(char *target_word)
{
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        printf("%c", corrects[i] ? target_word[i] : '-');
    }

    printf("\n\n%d> ", MAX_ATTEMPTS - rounds);
    fflush(stdout);
}

bool is_valid_word(const char *word, Words word_list)
{
    for (int i = 0; i < word_list.count; i++)
    {
        if (strcmp(word, word_list.arr[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

char *readline(void)
{
    static char buf[8];
    memset(buf, 0, sizeof(buf)); // Clear the buffer

    if (fgets(buf, sizeof(buf), stdin) == NULL)
    {
        return NULL; // Return NULL on failure
    }

    int size = strlen(buf);
    if (size > 0 && buf[size - 1] == '\n')
    {
        buf[size - 1] = '\0'; // Replace newline with null terminator
    }

    return buf;
}

void gameloop(char *target_word, Words word_list)
{
    display_prompt(target_word);
    char *input = readline();

    if (input == NULL)
    {
        printf("Error reading input.\n");
        return;
    }

    int length = strlen(input);

    if (length != WORD_LENGTH) // Ensure exact length
    {
        printf("Input should be exactly %d letters.\n", WORD_LENGTH);
        return;
    }

    if (!is_valid_word(input, word_list))
    {
        printf("'%s' is not a valid word. Try again.\n", input);
        rounds++;
        return;
    }

    Result *results = check_word(target_word, input);

    int correct_count = 0;
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (corrects[i])
        {
            correct_count++;
        }
    }

    print_result(results, target_word, input);

    if (correct_count == WORD_LENGTH)
    {
        win = true;
        continuation = false;
        return;
    }

    rounds++;
    if (rounds >= MAX_ATTEMPTS)
    {
        win = false;
        continuation = false;
    }
}

void print_result(Result *res, char *correct, char *guess)
{
    int i;

    for (i = 0; i < WORD_LENGTH; i++)
    {
        switch (res[i])
        {
        case ResultGreen:
            printf("%s%c%s", ClrGreen, guess[i], ClrStop);
            break;
        case ResultYellow:
            printf("%s%c%s", ClrYellow, guess[i], ClrStop);
            break;
        case ResultRed:
            printf("%s%c%s", ClrRed, guess[i], ClrStop);
            break;
        default:
            printf("Unknown: %d\n", res[i]);
        }
    }

    printf("\n");
    return;
}

void display_instructions()
{
    printf("Welcome to Wordle!\n\n");
    printf("Your goal is to guess the correct 5-letter word within 5 attempts.\n\n");
    printf("After each guess:\n");
    printf("- Letters that are in the correct position will be highlighted in green.\n");
    printf("- Letters that are in the word but in the wrong position will be highlighted in yellow.\n");
    printf("- Letters that are not in the word will be highlighted in red.\n\n");
    printf("Please enter a valid 5-letter word to begin!\n\n");
    printf("Good luck!\n");
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    rounds = 0;
    Words word_list = readfile("wordlist.txt");
    assert(word_list.count > 0);
    char *correct_word = get_random_word(word_list);
    continuation = true;

    display_instructions();

    while (continuation)
        gameloop(correct_word, word_list);

    printf("The correct word was: '%s'\n", correct_word);
    printf(win ? "Congratulations, you won the game\n" : "You lost. Game over\n");
    return 0;
}