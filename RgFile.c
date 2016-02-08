/*
    Faibanx Camera
    RgFile.c
    Copyright (c) 2016 Robert MacGregor
*/

#include "RgFile.h"

// Function for appending random data
_Bool RgAppend(const char *file, const char *data)
{
    FILE *File = fopen(file, "a");
    if (File == 0)
    {
        printf("Unable to open file: %s.\n",file);
        return 0;
    }
    else
    {
        fprintf(File, data);
        fclose(File);
        return 1;
    }
    return 0; // Whatever
}

// Function to check for the existence of the file
_Bool RgIsFile(const char *file)
{
    FILE *File = fopen(file, "r");
    if (File == 0)
        return 0;
    else
    {
        fclose(File);
        return 1;
    }
    return 0; // Whatever
}
