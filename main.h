#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/* define buffer */
#define buffer 1024

extern char **environ;

/* path checker function */
int pathExists(char *path);

/* custom _which function  */
char *findFullPath(char *filename, char *path);

/* string lenght function */
int stringLength(char *str);

/* string copy function */
char *stringCopy(char *dest, char *src);

/* concatenate string */
char *stringConcatenate(char *dest, char *src);

/* duplicate string */
char *stringDuplicate(char *str);

/* compare strings */
int stringCompare(char *str1, char *str2);

/* execute command using execve */
int ecmd(int *extstus, char *fpt, char *tokens[])

/* Print prompt and request input*/
int hept(size_t *lgth, char **line);

/* check for builtins */
int chbui(int tnc, char **tkns, int *extstus, char **argv);

/* check if file is executable */
int _ch(char **argv, char **tokens, char **fullpath, int *exit_status);

/* get an environment variable*/
char *getEnvironmentVariable(char *name);

/*compare n characters of strings*/
int compareStrings(char *str1, char *str2, int n);

/* unset environment variable */
int unsetEnvironmentVariable(char *name);

/* Realloc implementation*/
void *reallocateMemory(void *ptr, size_t size);

/*getline implementation*/
ssize_t readLine(char **linePtr, size_t *buffSize, FILE *myFile);

/* convert string to integer */
int convertStringToInt(char *str);

/* error message */
void error_message(char **tokens, char **argv, int *exit_status);

#endif