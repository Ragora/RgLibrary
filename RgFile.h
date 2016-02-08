/*
    Faibanx Camera
    RgFile.h
    Copyright (c) 2016 Robert MacGregor
*/

#ifndef _INCLUDE_RGFILE_H_
#define _INCLUDE_RGFILE_H_

#include <stdio.h>

// Function for appending random data
_Bool RgAppend(const char *file, const char *data);
// Function to check for the existence of the file
_Bool RgIsFile(const char *file);
#endif
