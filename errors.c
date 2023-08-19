#include "shell.h"

/**
 * _eputs - Prints a string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
    if (str)
        write(2, str, _strlen(str));
}

/**
 * _eputchar - Writes a character to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    return write(2, &c, 1);
}

/**
 * _putfd - Writes a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    return write(fd, &c, 1);
}

/**
 * _putsfd - Prints a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    if (!str)
        return 0;

    int count = 0;
    while (*str)
    {
        if (_putfd(*str, fd) == -1)
            return -1;
        str++;
        count++;
    }
    return count;
}

