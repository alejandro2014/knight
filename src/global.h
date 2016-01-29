#ifndef GLOBAL_H
#define GLOBAL_H

#define VERSION_NUMBER "0.3.5"

typedef int bool;
#define true 1
#define false 0

#define MAX_HEIGHT 255
#define MIN_HEIGHT 0

#define LENGTH_MESSAGE 100

#define alloc(Name, Type, NumElems) Type *Name = (Type *) malloc(sizeof(Type) * NumElems); \
        memset(Name, 0, sizeof(Type) * NumElems)

#define allocExist(Name, Type, NumElems) Name = (Type *) malloc(sizeof(Type) * NumElems); \
        memset(Name, 0, sizeof(Type) * NumElems)

#endif
