/*
    String.h
    Copyright (c) 2016 Robert MacGregor
*/

#ifndef _INCLUDE_STRING_H_
#define _INCLUDE_STRING_H_

#include <string.h>
#include <stdlib.h>
#include <math.h>

char *getSubStr(char *string, unsigned int start, unsigned int end);
int strStr(char *string, char *search);
//! Simply converts Char to a char array.
/** The data returned is malloc'd (should be freed)
 \param Char: The unsigned char to put into a char array.
 \return Returns a malloc'd string array containing Char.
*/
char *strUChar(unsigned char Char);

// 0x20
// "This is a test"
char *getWord(char *string, unsigned int word);
//! Doesn't work
char *getField(char *string, unsigned int id, unsigned char marker);
//! Checks if any characters in allowed is found in string.
/**
 \param string: The string to check.
 \param unallowed: The characters to check for.
 \return Returns a _Bool specifying if anything from unallowed is found in string
*/
_Bool subStrBlack(char *string, char *unallowed);
//! Counts the amount of occurances in the string.
/** If there are no specified occurances, 0 is returned.
 \param string: The string to find our occurances in.
 \param search: The specific string to search for.
 \return Returns the count of our occurances. If none exist, 0 is returned.
*/
unsigned int strOccurances(char *string, char*search);

//! Strips all characters in strip from string
/** The data returned is malloc'd (should be freed)
 \param string: The string to strip from
 \param strip: The string of characters to strip
 \return Returns a malloc'd string containing the stripped string.
*/
char *stripChars(char *string, char *strip);

//! Appends app to string. (useless function): Use sprintf instead
/** The data returned is malloc'd (should be freed)
 \param string: The string to have text appended to.
 \param app: The text to append to string
 \return Returns a malloc'd string containing the appended data.
*/
char *strAppend(char *string, char *app);

//! Prepends app to string. (useless function): Use sprintf instead
/** The data returned is malloc'd (should be freed)
 \param string: The string to have text prepended to.
 \param app: The text to prepend to string
 \return Returns a malloc'd string containing the prepended data.
*/
char *strPrepend(char *string, char *app);

//! Inserts 'insert' at position 'pos in 'string'.
/** The string is appended if your insert position is longer than string.
 \param string: The string to insert into.
 \param pos: The position to insert to.
 \param insert: The string to insert.
 \return Returns the modified string.
*/
char *subStrInsert(char *string, unsigned int pos, char *insert);
//! Returns the position of the specified occurance.
/** If you you specify too high of an occurance, -1 is returned.
 \param string: The string to find our occurance in.
 \param search: The specific string to search for.
 \return Returns the position of the requested occurance. -1 is returned if fail.
*/
int getStrOccurance(char *string, char*search, unsigned int occ);

//! Doesn't work (properly)
char *strReplace(char *string, char *rep, char *repwith);

//! Doesn't work all that good
unsigned int getWordCount(char *string);

unsigned int getWordCountx(char *string);

char *strAlloc(unsigned int len);

// Pretty useless function, but eh
char *strRepeat(char *repeat, unsigned int count);

//! Returns the file name from a directory. (if applicable)
/** Simple function.
 \param path: The file to a file.
 \return Returns a char* array containing only the file name (if applicable)
*/
char *getFileName(char *path);

//! Returns the file type from a file/directory.
/** Returns NULL if no file type if applicable.
 \param file: Direct file name or path to file.
 \return Returns a char* array containing the file name (no period).
*/
char *getFileType(char *file);
unsigned int strHash(char *text);
// Specific to strParseArgs
typedef struct
{
    unsigned int FlagC, ArgC;
    char **Flags;
    char **Arguments;
} ArgumentTable;

//! Argument parameter parser
// Returns 2D char* array, where the "X" value is the argument name
// And the "Y" value is the vargument value
ArgumentTable *strParseArgs(char *arguments[], unsigned int count);
#endif
