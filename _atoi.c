#include "shell.h"

int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int is_delim(char c, const char *delim) // Use const for the delimiter string
{
    while (*delim)
    {
        if (*delim == c)
            return 1;
        delim++;
    }
    return 0;
}

int _isalpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int _atoi(char *s)
{
    int sign = 1, flag = 0, output = 0;

    for (int i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            output = output * 10 + (s[i] - '0'); // Combine operations for result calculation
        }
        else if (flag == 1)
            flag = 2;
    }

    return (sign * output); // Combine sign multiplication
}
