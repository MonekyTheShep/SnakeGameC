# LinkedListC
Linked List implementation in c

## Example Usage
```c
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(void)
{
    LinkedList list;
    list = createList(0);

    for (int i = 1; i < 9; ++i)
    {
        Node *node = insertAtTail(&list, i);
    }  

    printf("Is list empty: %d\n", isEmpty(&list));
    printLinkedList(&list);
    printf("size: %d\n", sizeOfLinkedList(&list));

    printf("%d\n", list.head->data);
    printf("%d\n", list.tail->data);

    freeLinkedList(&list);
}
```
