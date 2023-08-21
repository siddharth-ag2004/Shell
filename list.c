#include "headers.h"

typedef struct List* ListPtr;

typedef struct List
{
    int data;
    List* next;
}List;

ListPtr createList(int data)
{
    ListPtr list = (ListPtr)malloc(sizeof(List));
    list->data = data;
    list->next = NULL;
    return list;
}

void addNode(ListPtr list, int data)
{
    ListPtr node = createList(data);
    ListPtr temp = list;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}