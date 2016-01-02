#ifndef LOAD_SAVE_H
#define LOAD_SAVE_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "global.h"

void SaveFile (char * FileName);
void LoadFile (char * FileName);
void DoFileOpenSave (bool bSave);
int ReadDir();
void GetCD();
int ChangeDir(char *path);

#endif
