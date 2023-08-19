#include "shell.h"

/* 
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    // Loop until the end of the string
    while (*s++)
        i++;

    return (i);
}

/* 
 * _strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
    // Loop until the end of either string is reached
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    // Check if both strings have reached the null terminator
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/* 
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
    {
        if (*needle++ != *haystack++)
            return (NULL);
    }
    return ((char *)haystack);
}

/* 
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    // Move to the end of the destination string
    while (*dest)
        dest++;

    // Copy characters from the source to the end of the destination
    while (*src)
        *dest++ = *src++;

    // Append the null terminator
    *dest = *src;

    return (ret);
}
