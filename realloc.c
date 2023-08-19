#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
    char *p = s;

    while (n--)
    {
        *p = b;
        p++;
    }
    
    return s;
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
    if (!pp)
        return;

    char **a = pp;
    while (*pp)
    {
        free(*pp);
        pp++;
    }

    free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p = NULL;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    for (unsigned int i = 0; i < old_size && i < new_size; i++)
        p[i] = ((char *)ptr)[i];

    free(ptr);
    return p;
}
