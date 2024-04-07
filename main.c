#include "list.h"
#include "stdio.h"

int readNumber()
{
    int number;
    scanf("%d", &number);
    return number;
}

List read()
{
    List output;
    Create(&output);

    int count = readNumber();

    for (size_t i = 0; i < count; i++)
    {
        Iterator it = Last(&output);
        int num = readNumber();
        Insert(&output, &it, num);
    }

    return output;
}

void printList(List *list, char *separator)
{
    Iterator it = First(list);
    Iterator last = Last(list);

    printf("%d", it.node->data);
    Next(&it);

    while (NotEqual(&it, &last))
    {
        int current = it.node->data;
        printf("%s%d", separator, current);
        Next(&it);
    }
}

Iterator findInsertionSortNode(List *list)
{
    Iterator it = First(list);
    Iterator last = Last(list);
    int previous = it.node->data;

    while (NotEqual(&it, &last))
    {
        int current = it.node->data;
        if (current < previous)
            return it;

        previous = current;

        Next(&it);
    }

    Iterator empty = {NULL};
    return empty;
}

void insertionSort(List *list)
{
#if DEBUG_SORT
    int iteration = 0;
#endif
    Iterator last = Last(list);
    
    while (true)
    {
        Iterator insertNode = findInsertionSortNode(list);
        if (insertNode.node == NULL)
            return;

        int insertNodeValue = insertNode.node->data;

        Iterator targetNode = insertNode;
        Prev(&targetNode);

        Delete(list, &insertNode);

        while (true)
        {
            int current = targetNode.node->data;

            if (current <= insertNodeValue || Equal(&targetNode, &last))
            {
                Next(&targetNode);
                Insert(list, &targetNode, insertNodeValue);
                break;
            }

            Prev(&targetNode);
        }

#if DEBUG_SORT
        if (iteration > 500)
            return;

        printf("Current (%d): ", iteration++);
        printList(list, " ");
        printf("\n");
#endif
    }
}

int main()
{
    List list = read();

    printf("Initial: ");
    printList(&list, " ");
    printf("\n");

    insertionSort(&list);

    printf("Sorted: ");
    printList(&list, " ");
    printf("\n");

    Destroy(&list);

    return 0;
}
