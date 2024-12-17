## strdup

The `strdup` function is a standard library function in C that duplicates a string by allocating sufficient memory for a new string and copying the contents of the original string into that new memory.

## fgets

- `fgets` reads a line from an input stream into a buffer, stopping when it encounters a newline character, reaches the end of the file, or reads the maximum number of characters specified (leaving space for the null terminator).

- It automatically null-terminates the string, making it suitable for use as a C string.

### Function Signature

```c
char *fgets(char *str, int n, FILE *stream);
```

- **`char *str`**: A pointer to the buffer where the read string will be stored.

- **`int n`**: The maximum number of characters to read, including the null terminator.

- **`FILE *stream`**: A pointer to the input stream from which to read (e.g., a file pointer returned by `fopen`).
