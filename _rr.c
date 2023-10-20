#include "main.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * Reallocate memory for a pointer.
 *
 * @param ptr: The pointer to reallocate.
 * @param size: The new size for the memory block.
 * @return A new pointer with reallocated memory.
 */
void *reallocateMemory(void *ptr, size_t size)
{
    void *newPtr;
    char *currentPtr;
    char *newCurrentPtr;
    size_t duplicateSize;
    size_t index = 0;

    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    newPtr = malloc(size);

    if (newPtr == NULL)
    {
        return NULL;
    }

    currentPtr = (char *)ptr;
    newCurrentPtr = (char *)newPtr;

    if (size < sizeof(ptr))
    {
        duplicateSize = size;
    }
    else
    {
        duplicateSize = sizeof(ptr);
    }

    for (; index <= duplicateSize; index++)
    {
        newCurrentPtr[index] = currentPtr[index];
    }

    free(ptr);

    return currentPtr;
}

/**
 * Read a line of characters from a file.
 *
 * @param linePtr: A pointer to the line.
 * @param buffSize: The buffer size.
 * @param myFile: The file to read from.
 * @return The number of bytes read or -1 on error.
 */
ssize_t readLine(char **linePtr, size_t *buffSize, FILE *myFile)
{
    ssize_t bytesRead = 0;
    size_t index = 0;
    ssize_t result;
    char *newSizePtr;

    while (1)
    {
        if (index >= *buffSize)
        {
            *buffSize += 8;
            newSizePtr = reallocateMemory(*linePtr, *buffSize);

            if (newSizePtr == NULL)
            {
                perror("Memory allocation error");
                return -1;
            }

            *linePtr = newSizePtr;
        }

        result = read(fileno(myFile), &((*linePtr)[index]), 1);

        if (result == -1)
        {
            perror("Error reading file");
            return -1;
        }
        else if (result == 0)
        {
            break;
        }

        bytesRead++;

        if ((*linePtr)[index] == '\n')
        {
            break;
        }

        index++;
    }

    return bytesRead;
}
