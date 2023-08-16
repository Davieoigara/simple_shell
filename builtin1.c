#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line, preceded
 *              by line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    list_t *node = info->history;
    int line_number = 0;

    while (node)
    {
        _printf("%5d  %s\n", line_number++, node->str);
        node = node->next;
    }
    return 0;
}

/**
 * _unset_alias - Unsets an alias.
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int _unset_alias(info_t *info, char *str)
{
    char *p = _strchr(str, '=');
    if (p)
    {
        *p = '\0';
        int ret = delete_node_by_value(&(info->alias), str);
        *p = '=';
        return ret;
    }
    return 1;
}

/**
 * _set_alias - Sets or updates an alias.
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int _set_alias(info_t *info, char *str)
{
    char *p = _strchr(str, '=');
    if (p)
    {
        *p = '\0';
        _unset_alias(info, str);
        return (add_node_end(&(info->alias), str, 0) == NULL);
    }
    return 1;
}

/**
 * _print_alias - Prints an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int _print_alias(list_t *node)
{
    if (node)
    {
        char *p = _strchr(node->str, '=');
        if (p)
        {
            *p = '\0';
            _printf("%s='%s'\n", node->str, p + 1);
            *p = '=';
            return 0;
        }
    }
    return 1;
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    if (info->argc == 1)
    {
        list_t *node = info->alias;
        while (node)
        {
            _print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (int i = 1; info->argv[i]; i++)
    {
        char *p = _strchr(info->argv[i], '=');
        if (p)
            _set_alias(info, info->argv[i]);
        else
            _print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}
