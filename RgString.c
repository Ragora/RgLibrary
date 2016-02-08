/*
    RgString.c
    Copyright (c) 2016 Robert MacGregor

    Self Comments: This is a pretty shoddy
    string library of mine, but it works
    for the current cause.
*/

#include "RgString.h"

char *getSubStr(char *string, unsigned int start, unsigned int end)
{
    unsigned int len = strlen(string);
    if (end > len)
        end = len;
    unsigned int endS;
    if (start != 0)
        endS = (start+end)+1;
    else
        endS = (start+end);
    char *retStr = (char*)malloc(sizeof(char)*(endS+1));
    for (unsigned int i = start; i < endS; i++)
    {
        char tC = string[i];
        if (tC == 0x00)
        {
            retStr[-(start-i)] = tC;
            return retStr;
        }
        else
            retStr[-(start-i)] = string[i];
    }
    retStr[end] = 0x00;
    return retStr;
}

// 0x20
// "This is a test"
char *getWord(char *string, unsigned int word)
{
    if (getWordCount(string) < word)
        return 0;

    if (word == 0)
    {
        int space = strStr(string," ");
        if (space != -1)
            return getSubStr(string,0,space);
        else
            return string;
    }

    unsigned int Count = 0;
    unsigned int len = strlen(string);
    _Bool Letters = 1;
    for (unsigned int i = 0; i < len; i++)
    {
        char cT = string[i];
        if (cT == 0x20 && Letters)
        {
            Letters = 0;
            Count++;
        }
        else if (cT != 0x20 && !Letters)
            Letters = 1;

        if (Count == word)
            return getSubStr(getSubStr(string,i,len),i,strStr(string,0x00));
    }
    if (Letters)
        Count++;
    return strUChar(0x00);
}

//! Doesn't work
char *getField(char *string, unsigned int id, unsigned char marker)
{
    unsigned int len = strlen(string);
    int Count = -1;
    unsigned lstMk = 0;
    for (unsigned int i = 0; i < len; i++)
    {
       // if (Count == id)
         //   return getSubStr(string, lstMk+1, i-2);
        if (string[i] == marker)
        {
            Count++;
            lstMk = i;
        }
    }
    return 0;
}

//! Checks if any characters in allowed is found in string.
/**
 \param string: The string to check.
 \param unallowed: The characters to check for.
 \return Returns a _Bool specifying if anything from unallowed is found in string
*/
_Bool subStrBlack(char *string, char *unallowed)
{
    for (unsigned int i = 0; i < strlen(string); i++)
        for (unsigned int h = 0; h < strlen(unallowed); h++)
            if (string[i] == unallowed[h])
                return 1;
    return 0;
}

//! Strips all characters in strip from string
/** The data returned is malloc'd (should be freed)
 \param string: The string to strip from
 \param strip: The string of characters to strip
 \return Returns a malloc'd string containing the stripped string.
*/
char *stripChars(char *string, char *strip)
{
    unsigned int len = strlen(string);
    unsigned int slen = strlen(strip);
    unsigned int Count = 0;
    unsigned int sC = 0;

    // Calculate the exact size our array should be
    char *retStr = (char*)malloc(sizeof(char)*(len-(strOccurances(string, strip)*slen)));

    for (unsigned int i = 0; i < len; i++)
        if (subStrBlack(getSubStr(string, i, 1), strip))
        {
            sC++;
            continue;
        }
        else
        {
            retStr[i-sC] = string[i];
            Count++;
        }

    retStr[Count+1] = 0x00;
    return retStr;
}

//! Appends app to string. (useless function): Use sprintf instead
/** The data returned is malloc'd (should be freed)
 \param string: The string to have text appended to.
 \param app: The text to append to string
 \return Returns a malloc'd string containing the appended data.
*/
char *strAppend(char *string, char *app)
{
    unsigned int len = strlen(string);
    unsigned int alen = strlen(app);
    unsigned int retStrLen = len+alen;
    char *retStr = (char*)malloc(sizeof(char)*retStrLen);
    memset(retStr, 0, retStrLen);
    for (unsigned int i = 0; i < len; i++)
        retStr[i] = string[i];
    for (unsigned int i = 0; i < alen; i++)
        retStr[i+len] = app[i];
    retStr[retStrLen] = 0x00;
    return retStr;
}

//! Prepends app to string. (useless function): Use sprintf instead
/** The data returned is malloc'd (should be freed)
 \param string: The string to have text prepended to.
 \param app: The text to prepend to string
 \return Returns a malloc'd string containing the prepended data.
*/
char *strPrepend(char *string, char *app)
{
    unsigned int len = strlen(string);
    unsigned int alen = strlen(app);
    unsigned int retStrLen = len+alen;
    char *retStr = (char*)malloc(sizeof(char)*retStrLen);
    for (unsigned int i = 0; i < alen; i++)
        retStr[i] = app[i];
    for (unsigned int i = 0; i < len; i++)
        retStr[i+alen] = string[i];
    retStr[retStrLen] = 0x00;
    return retStr;
}

//! Simply converts Char to a char array. (useless function)
/** The data returned is malloc'd (should be freed)
 \param Char: The unsigned char to put into a char array.
 \return Returns a malloc'd string array containing Char.
*/
char *strUChar(unsigned char Char)
{
   // char *UChar[2] = { Char, 0x00 };
    char *UChar = (char*)malloc(sizeof(char)*2);
    memset(UChar,0,2);
    UChar[0] = Char;
    UChar[1] = 0x00;
    return UChar;
}

//! Inserts 'insert' at position 'pos in 'string'.
/** The string is appended if your insert position is longer than string.
 \param string: The string to insert into.
 \param pos: The position to insert to.
 \param insert: The string to insert.
 \return Returns the modified string.
*/
char *subStrInsert(char *string, unsigned int pos, char *insert)
{
    // Retrieve the length of input string
    unsigned int len = strlen(string);
    // If our position is somewhere after our string, append it
    if (pos > len)
        return strAppend(string, insert);
    else if (pos == 0)
        return strPrepend(string, insert);

    unsigned int ilen = strlen(insert);
    char newStr[(ilen+len)];
    char *halfO = getSubStr(string,0,pos);
    unsigned int h1l = strlen(halfO);
    for (unsigned int i =0; i < h1l; i++)
        newStr[i] = halfO[i];

    for (unsigned int i =0; i < ilen; i++)
        newStr[i+(h1l)] = insert[i];
    char *half2 = getSubStr(string,pos,len);
    unsigned int h2l = strlen(half2);
    for (unsigned int i = 0; i < h2l; i++)
        newStr[i+((h1l+h2l)+2)] = half2[i];
    newStr[strlen(newStr)] = 0x00;

    return newStr;
}

//! Counts the amount of occurances in the string.
/** If there are no specified occurances, 0 is returned.
 \param string: The string to find our occurances in.
 \param search: The specific string to search for.
 \return Returns the count of our occurances. If none exist, 0 is returned.
*/
unsigned int strOccurances(char *string, char*search)
{
    unsigned int Count = 0;
    for (unsigned int i = 0; i < strlen(string); i++)
        if (strcmp(getSubStr(string,i,strlen(search)), search)==0)
            Count++;
    return Count;
}

//! Returns the position of the specified occurance.
/** If you you specify too high of an occurance, -1 is returned.
 \param string: The string to find our occurance in.
 \param search: The specific string to search for.
 \return Returns the position of the requested occurance. -1 is returned if fail.
*/
int getStrOccurance(char *string, char*search, unsigned int occ)
{
    unsigned int Count = 0;
    for (unsigned int i = 0; i < strlen(string); i++)
        if (strcmp(getSubStr(string,i,strlen(search)), search)==0)
        {
            if (Count == occ)
                return i;
            else
                Count++;
        }
    return -1;
}


//! Doesn't work (properly)
char *strReplace(char *string, char *rep, char *repwith)
{
    unsigned int repwLen = strlen(repwith);
    unsigned int len = strlen(string);
    unsigned int replen = strlen(rep);

    // If our repwLen is larger than replen, then we got a really small decimal.
    unsigned long sizeChange;
    if ( replen > repwLen)
        sizeChange = replen/repwLen;
    else
        sizeChange = repwLen/replen;

    unsigned int Size = sizeof(char)*(len+(len*ceil(sizeChange)));
    char *retStr = (char*)malloc(Size);
    memset(retStr,0,strlen(retStr));


    return retStr;
}

//! Doesn't work all that good
unsigned int getWordCount(char *string)
{
    unsigned int Count = 0;
    unsigned int len = strlen(string);
    while (strStr(string," ") != -1)
    {
     //   if (strStr(string, " ") == -1)
      //      return Count
       // cShv += strlen(getSubStr(string,0,strStr(string," ")));
        char *sh = getSubStr(string,0,strStr(string," "));
        unsigned int shLen = strlen(sh);
        string = getSubStr(string,shLen+1,len);
        Count++;
    }

    char Search[1];
    Search[0] = 0x00;

    unsigned int t = strStr(string, Search);
    if (string[t-1] != 0x00 && string[t-1] != 0x20)
        Count++;

    return Count+1;
}

unsigned int getWordCountx(char *string)
{
    unsigned int Count = 0;
    unsigned int len = strlen(string);
    _Bool Letters = 1;
    for (unsigned int i = 0; i < len; i++)
    {
        char cT = string[i];
        if (cT == 0x20 && Letters)
        {
            Letters = 0;
            Count++;
        }
        else if (cT != 0x20 && !Letters)
            Letters = 1;
    }
    if (Letters)
        Count++;
    return Count;
}

int strStr(char *string, char *search)
{
    for (unsigned int i = 0; i < strlen(string); i++)
    {
        char *sTest = getSubStr(string, i, strlen(search));
        if (strcmp(sTest, search) == 0)
            return i;
    }
    return -1;
}

char *strAlloc(unsigned int len)
{
    // Allocate our memory
    char *Ret = (char*)malloc(sizeof(char)*len+1);
    // Make sure it's zeroed
    memset(Ret,0,len+1);
    // Iterate through our memory until we hit the last character (null)
    for (unsigned int i = 0; i < len; i++)
        Ret[i] = 0x20; // Set to space
    // Return the alloc'd string
    return Ret;
}

// Pretty useless function, but eh
char *strRepeat(char *repeat, unsigned int count)
{
    unsigned int len = strlen(repeat);
    char *Retstr = strAlloc(len*count);

    for (unsigned int i = 0; i < count; i++)
    {
      //  printf(strUChar(repeat[i % len]));
        Retstr = strPrepend(repeat, Retstr);
     //   Retstr[i] = repeat[i % len];
    }
    Retstr[len] = 0x00;
    return Retstr;
}

//! Returns the file name from a directory. (if applicable)
/** Simple function.
 \param path: The file to a file.
 \return Returns a char* array containing only the file name (if applicable)
*/
char *getFileName(char *path)
{
    return getSubStr(path, getStrOccurance(path, "/", strOccurances(path,"/")-1)+1, strlen(path));
}

//! Returns the file type from a file/directory.
/** Returns NULL if no file type if applicable.
 \param file: Direct file name or path to file.
 \return Returns a char* array containing the file name (no period).
*/
char *getFileType(char *file)
{
    char *pF = getFileName(file);
    int S = strStr(pF,".");
    if (S == -1)
        return NULL;
    else
        return getSubStr(pF, S+1, strlen(pF));
}

unsigned int strHash(char *text)
{
    unsigned int R = 0;
    unsigned int len = strlen(text);
    for (unsigned int i = 0; i < len; i++)
        R += text[i];
    return ceil(R/len);
}

//! Argument parameter parser
// Returns 2D char* array, where the "X" value is the argument name
// And the "Y" value is the vargument value
ArgumentTable *strParseArgs(char *arguments[], unsigned int count)
{
    // Allocate a blank argument table
    ArgumentTable *Table = (ArgumentTable*)malloc(sizeof(ArgumentTable));
    memset(Table,0,sizeof(ArgumentTable)); // Zero the memory.
    // The memory allocated below is consolidated when args/flag pairs are known
    // Allocate our flags array
    unsigned int FlagCount = 0;
    char **Flags = (char**)malloc(sizeof(char)*pow(count,2));
    memset(Flags,0,sizeof(char)*count*count);
    // Allocate our args array
    unsigned int ArgumentCount = 0;
    char **Arguments = (char**)malloc(sizeof(char)*pow(count,2));
    memset(Arguments,0,sizeof(char)*count*count);

    // Allocate temporary memory to store ignored portions of our string
    unsigned int ignoreAC = 0;
    _Bool *ignoreA = (_Bool*)malloc(sizeof(_Bool)*count);
    memset(ignoreA,0,sizeof(_Bool)*count);

    // Iterate through our supplied arg table now
    for (unsigned int i = 0; i < count; i++)
    {
        // Check to see if we're supposed to ignore this
        for (unsigned int h = 0; h < ignoreAC; h++)
            if (ignoreA[i] == 1) continue; // Skip this argument, it was verified

        if (arguments[i][0] == '-') // We found a flag
        {
            // Check to see if we got an argument for it
            if (i != count-1 && arguments[i+1][0] != '-') // We found an argument
            {
                ignoreA[i+1] = 1;
                Arguments[ArgumentCount] = arguments[i+1];
                ArgumentCount++;
            }
            else
            {
                Arguments[ArgumentCount] = 0x00;
                ArgumentCount++;
            }
            // Since we have a flag, we add this to our array too
            Flags[FlagCount] = getSubStr(arguments[i],1,strlen(arguments[i]));
            FlagCount++;
        }
    }

    // Drop our information into our argument table
    Table->ArgC = ArgumentCount;
    Table->FlagC = FlagCount;
    Table->Arguments = Arguments;
    Table->Flags = Flags;
    free(ignoreA); // Cleanup the temporary ignore array
    return Table; // Return the constructed Table
}
