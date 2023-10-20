#include "main.h"

/**
 * Checks if a file path exists.
 *
 * @param path: The path to check.
 * @return 1 if the path exists, 0 if it doesn't.
 */
int pathExists(char *path)
{
    struct stat fileStat;
    return (stat(path, &fileStat) == 0);
}

/**
 * Find the full path to a file.
 *
 * @param filename: The file name to locate.
 * @param path: A colon-separated list of directories to search in.
 * @return The full path if found, NULL if not found.
 */
char *findFullPath(char *filename, char *path)
{
    char *pathCopy;
    char *pathTokens[1024];
    char *fullPath;
    int i = 0;

    if (path == NULL)
    {
        return NULL;
    }

    pathCopy = strdup(path);

    // Tokenize the path.
    i = 0;
    pathTokens[i] = strtok(pathCopy, ":");

    while (pathTokens[i] != NULL)
    {
        fullPath = malloc(strlen(pathTokens[i]) + strlen(filename) + 2);
        strcpy(fullPath, pathTokens[i]);
        strcat(fullPath, "/");
        strcat(fullPath, filename);

        if (pathExists(fullPath))
        {
            free(pathCopy);
            return fullPath;
        }

        free(fullPath);
        i++;
        pathTokens[i] = strtok(NULL, ":");
    }

    free(pathCopy);
    return NULL;
}

/**
 * Compare the first n characters of two strings.
 *
 * @param str1: The first string.
 * @param str2: The second string.
 * @param n: The number of characters to compare.
 * @return 0 if the strings are equal, -1 otherwise.
 */
int compareStrings(char *str1, char *str2, int n)
{
    int i = 0;

    while (i < n)
    {
        if (str1[i] != str2[i])
            return -1;
        i++;
    }
    return 0;
}

/**
 * Get the value of an environment variable by name.
 *
 * @param name: The name of the environment variable.
 * @return The value of the environment variable, or NULL if not found.
 */
char *getEnvironmentVariable(char *name)
{
    int nameLength = strlen(name);
    int i;

    for (i = 0; environ[i] != NULL; i++)
    {
        if (compareStrings(name, environ[i], nameLength) == 0 && environ[i][nameLength] == '=')
        {
            return environ[i] + nameLength + 1;
        }
    }

    return NULL;
}

/**
 * Remove an environment variable.
 *
 * @param name: The name of the variable to remove.
 * @return 0 on success, -1 on failure.
 */
int unsetEnvironmentVariable(char *name)
{
    char **env = environ;
    int len, nameLength;
    int environCount = 0, i = 0, j;
    char **newArray;

    if (name == NULL)
        return -1;

    while (*env != NULL)
    {
        environCount++;
        env++;
    }

    newArray = malloc((environCount + 1) * sizeof(char *));

    if (newArray == NULL)
        return -1;

    env = environ;
    nameLength = strlen(name);

    while (*env != NULL)
    {
        if (compareStrings(name, *env, nameLength) != 0 || (*env)[nameLength] != '=')
        {
            len = strlen(*env);
            newArray[i] = malloc((len + 1) * sizeof(char));

            if (newArray[i] == NULL)
            {
                for (j = 0; j < i; j++)
                {
                    free(newArray[j]);
                }
                free(newArray);
                return -1;
            }

            strcpy(newArray[i], *env);
            i++;
        }
        env++;
    }

    newArray[i] = NULL;
    environ = newArray;
    return 0;
}
