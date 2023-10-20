#include "main.h"

/**
 * Calculate the length of a string.
 *
 * @param str: The input string.
 * @return The length of the string.
 */
int stringLength(char *str)
{
    int length = 0;

    if (str == NULL)
        str = "";

    while (*str != '\0')
    {
        length++;
        str++;
    }

    return length;
}

/**
 * Copy the contents of one string to another.
 *
 * @param dest: The destination string.
 * @param src: The source string.
 * @return The copied string.
 */
char *stringCopy(char *dest, char *src)
{
    int i = 0;

    while (i <= stringLength(src))
    {
        dest[i] = src[i];
        i++;
    }

    return dest;
}

/**
 * Concatenate two strings.
 *
 * @param dest: The destination string.
 * @param src: The source string.
 * @return The concatenated string.
 */
char *stringConcatenate(char *dest, char *src)
{
    int i = 0;
    char *temp = dest;

    while (*temp != '\0')
    {
        temp++;
    }

    while (i < stringLength(src))
    {
        *temp = src[i];
        temp++;
        i++;
    }

    *temp = '\0';
    return dest;
}

/**
 * Duplicate a string and return a pointer to the copy.
 *
 * @param str: The input string.
 * @return A pointer to a newly allocated memory block containing a duplicate of the input string.
 */
char *stringDuplicate(char *str)
{
    char *copy;
    int i = 0;

    if (str == NULL)
    {
        return NULL;
    }

    copy = (char *)malloc(stringLength(str) * sizeof(char) + 1);

    if (copy == NULL)
    {
        return NULL;
    }

    while (i <= (int)stringLength(str))
    {
        copy[i] = str[i];
        i++;
    }

    return copy;
}

/**
 * Compare two strings lexicographically.
 *
 * @param str1: The first string.
 * @param str2: The second string.
 * @return 0 if the strings are equal, a positive value if str1 is greater, and a negative value if str1 is less.
 */
int stringCompare(char *str1, char *str2)
{
    int i = 0;
    int len1, len2;

    if (str1 == NULL)
        str1 = "";

    if (str2 == NULL)
        str2 = "";

    len1 = stringLength(str1);
    len2 = stringLength(str2);

    if (len1 > len2)
        return 1;

    else if (len1 < len2)
        return -1;

    while (i < len1)
    {
        if (str1[i] != str2[i])
        {
            return -1;
        }
        i++;
    }

    return 0;
}
