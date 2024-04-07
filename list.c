#include <stdbool.h>
#include <stdlib.h>

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

bool Equal(const Iterator* lhs, const Iterator* rhs)
{
    return lhs->node == rhs->node;
}

bool NotEqual(const Iterator* lhs, const Iterator* rhs)
{
    return !Equal(lhs, rhs);
}

Iterator* Next(Iterator* i)
{
    i->node = i->node->next;
    return i;
}

Iterator* Prev(Iterator* i)
{
    i->node = i->node->prev;
    return i;
}

int Fetch(const Iterator* i)   
{
    return i->node->data;
}

void Store(const Iterator* i, const int t)
{
    i->node->data = t;
}

typedef struct List
{
    Item* head;
    int size;
} List;


void Create(List* l)
{
    l->head = malloc(sizeof(Item));
    l->head->next = l->head->prev = l->head;
    l->size = 0;
}

Iterator First(const List* l)
{
    Iterator res = { l->head->next };
    return res;
}

Iterator Last(const List* l)
{
    Iterator res = { l->head };
    return res;
}

bool Empty(const List* l)
{
    Iterator fst = First(l);
    Iterator lst = Last(l);
    return Equal(&fst, &lst);
}

int Size(const List* l)
{
    return l->size;
}

Iterator Insert(List* l, Iterator* i, const int t)
{
    Iterator res = { malloc(sizeof(struct Item)) };
    if (!res.node)
        return Last(l);
    res.node->data = t;
    res.node->next = i->node;
    res.node->prev = i->node->prev;
    res.node->prev->next = res.node;
    i->node->prev = res.node;
    l->size++;
    return res;
}

Iterator Delete(List* l, Iterator* i)
{
    Iterator res = Last(l);
    if (Equal(i, &res))
        return res;
    res.node = i->node->next;
    res.node->prev = i->node->prev;
    i->node->prev->next = res.node; 
    l->size--;
    free(i->node);
    i->node = 0;
    return res;
}

void Destroy(List* l)
{
    Item* i = l->head->next;
    while(i != l->head)
    {
        Item* pi = i;
        i = i->next;
        free(pi);
    }
    free(l->head);
    l->head = 0;
    l->size = 0;
}