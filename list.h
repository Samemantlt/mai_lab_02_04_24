#ifndef _LIST_H_ 
#define _LIST_H_

#include <stdbool.h>

typedef struct Item
{
    struct Item* prev;
    struct Item* next;
    int data;
} Item;

typedef struct Iterator
{
    Item* node;
} Iterator;

typedef struct List
{
    Item* head;
    int size;
} List;

bool Equal(const Iterator* lhs, const Iterator* rhs);
bool NotEqual(const Iterator* lhs, const Iterator* rhs);
Iterator* Next(Iterator* i);
Iterator* Prev(Iterator* i);
int Fetch(const Iterator* i);   
void Store(const Iterator* i, const int t);
void Create(List* l);
Iterator First(const List* l);
Iterator Last(const List* l);
bool Empty(const List* l);
int Size(const List* l);
Iterator Insert(List* l, Iterator* i, const int t);
Iterator Delete(List* l, Iterator* i);
void Destroy(List* l);

#endif