#ifndef __LIST_H
#define __LIST_H

typedef struct List* ListPtr;

typedef struct List
{
    int data;
    char* name;
    int count;
    struct List* next;
}List;

ListPtr createList(int data,char* name);

void addNode(ListPtr list, int data,char* name);

void removeNode(ListPtr list, int data);

#endif