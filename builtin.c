#include "shell.h"

/**
 * _myexit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _myexit(info_t *info)
{
    if (info->argv[1]) /* If there is an exit argument */
    {
        int exitcheck = _erratoi(info->argv[1]);
        if (exitcheck == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: %s\n", info->argv[1]);
            return 1;
        }
        info->err_num = exitcheck;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
    char buffer[1024];
    char *dir;
    int chdir_ret;

    char *s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            dir = _getenv(info, "PWD=");

        chdir_ret = chdir(dir ? dir : "/");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        char *oldpwd = _getenv(info, "OLDPWD=");
        if (!oldpwd)
        {
            _puts(s);
            _putchar('\n');
            return 1;
        }
        _puts(oldpwd), _putchar('\n');
        chdir_ret = chdir(oldpwd ? oldpwd : "/");
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to %s\n", info->argv[1]);
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * _myhelp - Provides help information.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
    char **arg_array = info->argv;
    _puts("help call works. Function not yet implemented\n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return 0;
}

