#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @name: Environment variable name.
 * Return: The value of the variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    while (node)
    {
        char *str = node->str;
        if (_strncmp(str, name, _strlen(name)) == 0 && str[_strlen(name)] == '=')
            return &str[_strlen(name) + 1];
        node = node->next;
    }
    return NULL;
}

/**
 * _mysetenv - Initialize a new environment variable
 *             or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(info, info->argv[1], info->argv[2]) == 0)
    {
        _eputs("Failed to set environment variable\n");
        return 1;
    }
    return 0;
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }
    for (int i = 1; i < info->argc; i++)
    {
        if (_unsetenv(info, info->argv[i]) == 0)
        {
            _eputs("Failed to unset environment variable\n");
            return 1;
        }
    }
    return 0;
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
    info->env = NULL;
    for (char **env = environ; *env != NULL; env++)
        add_node_end(&(info->env), *env, 0);
    return 0;
}
