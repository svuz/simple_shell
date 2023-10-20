#include "main.h"

/**
 * Convert a string to an integer.
 * @param str: The input string.
 * @return The integer value.
 */
int convertStringToInt(char *str)
{
    int result = 0; // Stores the converted integer.
    int isPositive = 1; // Tracks whether the integer is positive.
    int i = 0; // Counter.

    // Check if the character at index 0 is positive or negative.
    if (str[0] == '-')
    {
        isPositive = -1;
        i = 1;
    }

    // Iterate through the string.
    while (str[i] != '\0')
    {
        // Validate if the current character is a digit.
        if (str[i] >= '0' && str[i] <= '9')
        {
            // Convert the character to a digit and update the result.
            result = result * 10 + (str[i] - '0');
            i++;
        }
        else
        {
            // If a non-digit character is encountered, break the loop.
            break;
        }
    }

    return (isPositive * result);
}
