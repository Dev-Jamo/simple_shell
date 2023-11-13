#include "shell_master.h"

/**
 * **strtow - splits a string into words, repeat delimiters are ignored.
 * @str: input string
 * @d: delimiter string
 * Return: a pointer to an array of strings, or NULL on failure.
 */
int is_delim(char c, char *delimiters)
{
    if (!delimiters)
        delimiters = " ";
    
    return strchr(delimiters, c) != NULL;
}

char **strtow(char *str, char *d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == '\0')
        return NULL;
    
    if (!d)
        d = " ";

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || str[i + 1] == '\0'))
            numwords++;
    }

    if (numwords == 0)
        return NULL;

    s = (char **)malloc((numwords + 1) * sizeof(char *));
    if (!s)
        return NULL;

    for (i = 0, j = 0; j < numwords; j++)
    {
        while (is_delim(str[i], d))
            i++;

        k = 0;
        while (!is_delim(str[i + k], d) && str[i + k] != '\0')
            k++;

        s[j] = (char *)malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return NULL;
        }

        for (m = 0; m < k; m++)
            s[j][m] = str[i++];

        s[j][m] = '\0';
    }

    s[j] = NULL;
    return s;
}
