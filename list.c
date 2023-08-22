#include "headers.h"

ListPtr createList(int data,char* name)
{
    ListPtr list = (ListPtr)malloc(sizeof(List));
    list->data = data;
    list->name = (char*)malloc(sizeof(char)*MAX_TOKEN_LENGTH);
    strcpy(list->name,name);
    list->next = NULL;
    return list;
}

void addNode(ListPtr list, int data,char* name)
{
    ListPtr node = createList(data,name);
    ListPtr temp = list;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}