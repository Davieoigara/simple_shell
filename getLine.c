#include "shell.h"

ssize_t input_buf(info_t *info, char **buf, size_t *len) {
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif

        if (r > 0) {
            if ((*buf)[r - 1] == '\n') {
                (*buf)[r - 1] = '\0'; // Remove trailing newline
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
        }
    }
    return r;
}

ssize_t get_input(info_t *info) {
    static char *buf;
    static size_t i = 0, j = 0, len = 0;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);

    if (r == -1) {
        return -1;
    }

    // Rest of the function implementation
}

ssize_t read_buf(info_t *info, char *buf, size_t *i) {
    ssize_t r = 0;

    if (*i) {
        return 0;
    }

    r = read(info->readfd, buf, READ_BUF_SIZE);

    if (r >= 0) {
        *i = r;
    }
    return r;
}

int _getline(info_t *info, char **ptr, size_t *length) {
    static char buf[READ_BUF_SIZE];
    static size_t i = 0, len = 0;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;

    if (p && length) {
        s = *length;
    }

    if (i == len) {
        i = len = 0;
    }

    r = read_buf(info, buf, &len);

    if (r == -1 || (r == 0 && len == 0)) {
        return -1;
    }

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);

    if (!new_p) {
        return (p ? free(p), -1 : -1);
    }

    if (s) {
        _strncat(new_p, buf + i, k - i);
    } else {
        _strncpy(new_p, buf + i, k - i + 1);
    }

    s += k - i;
    i = k;
    p = new_p;

    if (length) {
        *length = s;
    }

    *ptr = p;
    return s;
}

void sigintHandler(__attribute__((unused)) int sig_num) {
    _puts("\n$ ");
    _putchar(BUF_FLUSH);
}
