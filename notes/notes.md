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

##strcpy

#### Function Signature

```c
char *strcpy(char *dest, const char *src);
```

- **Purpose**: Copies the entire string from `src` to `dest`, including the null terminator.

- It continues copying characters from `src` to `dest` until it encounters the null terminator in `src`.

- It then appends a null terminator to the end of `dest`.

- **Assumption**: The destination buffer (`dest`) must be large enough to hold the entire source string, including the null terminator. If `dest` is not large enough, it can lead to buffer overflow, which is a common source of security vulnerabilities.

## `strncpy`

#### Function Signature

```c
char *strncpy(char *dest, const char *src, size_t n);
```

- **Purpose**: Copies up to `n` characters from `src` to `dest`.

- It copies characters from `src` to `dest` until it either reaches the null terminator in `src` or copies `n` characters, whichever comes first.

- If the length of `src` is less than `n`, `strncpy` will not null-terminate `dest`. This means that if `src` is shorter than `n`, the remaining characters in `dest` will remain unchanged.

- If `src` is longer than `n`, only the first `n` characters are copied, and `dest` will not be null-terminated unless you explicitly set it.

### Main difference is on null termination & buffer overflow.

**Null Termination**:

- `strcpy` always null-terminates the destination string.

- `strncpy` does not guarantee null termination if the source string is shorter than `n`.

**Buffer Overflow**:

- `strcpy` can lead to buffer overflow if the destination buffer is not large enough.

- `strncpy` allows you to specify the maximum number of characters to copy, which can help prevent buffer overflow, but it can still lead to issues if not used carefully (e.g., forgetting to null-terminate).

**Use Cases**:

- Use `strcpy` when you are sure that the destination buffer is large enough to hold the source string.

- Use `strncpy` when you want to limit the number of characters copied, but be cautious about null termination.
 