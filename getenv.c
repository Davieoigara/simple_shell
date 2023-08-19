#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Return: Copy of the environment variables.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        char **env_copy = duplicate_environment(info->env);
        if (env_copy)
        {
            free_string_array(info->environ);
            info->environ = env_copy;
            info->env_changed = 0;
        }
    }
    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: The environment variable to unset.
 * Return: 1 on successful unset, 0 otherwise.
 */
int _unsetenv(info_t *info, const char *var)
{
    if (!info->env || !var)
        return 0;

    int removed = delete_environment_variable(&(info->env), var);
    if (removed)
        info->env_changed = 1;

    return removed;
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable name.
 * @value: The environment variable value.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(info_t *info, const char *var, const char *value)
{
    if (!var || !value)
        return -1;

    char *env_var = create_environment_variable(var, value);
    if (!env_var)
        return -1;

    int updated = update_environment_variable(&(info->env), env_var);

    if (updated)
    {
        info->env_changed = 1;
    }
    else
    {
        add_node_end(&(info->env), env_var);
        free(env_var);
        info->env_changed = 1;
    }

    return 0;
}
