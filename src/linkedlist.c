#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

LinkedList createList(SnakeNode snake_node)
{
    LinkedList list;
    list.head = (Node *)malloc(sizeof(Node));

    if (!list.head) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        return (LinkedList){NULL, NULL};
    }

    list.head->next = NULL;
    list.head->snake_node = snake_node;
    list.tail = list.head;
    return list;
}

Node *createNode(SnakeNode snake_node)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    if (!newNode) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->snake_node = snake_node;

    return newNode;
}

Node *insertAtHead(LinkedList *list, SnakeNode snake_node)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant insert element at head of NULL list.\n");
        return NULL;
    }


    Node *newNode = createNode(snake_node);

    // swap the head with new node

    // make new node point to head
    newNode->next = list->head;
    // replace head with new node
    list->head = newNode;
    return newNode;
}

Node *insertAtTail(LinkedList *list, SnakeNode snake_node)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant insert element at tail of NULL list.\n");
        return NULL;
    }

    Node *newNode = createNode(snake_node);

    // swap the tail with new node

    // make old tail point to new tail
    list->tail->next = newNode;
    // replace old tail with new tail
    list->tail = newNode;
    list->tail->next = NULL;

    return newNode;
}

Node *insertAtNode(LinkedList *list, Node *node, SnakeNode snake_node)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant insert element of NULL list.\n");
        return NULL;
    }

    if (node == NULL) 
    {
        fprintf(stderr, "Cant insert NULL node.\n");
        return NULL;
    }

    Node *newNode;
    if (node == list->head)
    {
        newNode = insertAtHead(list, snake_node);
        return newNode;
    }

    if (node == list->tail)
    {
        newNode = insertAtTail(list, snake_node);
        return newNode;
    }

    newNode = createNode(snake_node);

    // if the node isn't the head
    Node *temp = list->head;
    Node *prev = NULL;
    bool hasNode = false;

    // loop through list until it is the node
    while (temp != node && temp != NULL)
    {
        // set previous to temp so when loop breaks it is the previous node
        prev = temp;

        temp = temp->next;

        if (temp == node) 
        {
            hasNode = true;
        }

    }

    if (prev == NULL)
    {
        fprintf(stderr, "Error occurred inserting node.\n");
        free(newNode);
        return NULL;
    }

    if (!hasNode)
    {
        fprintf(stderr, "Node not found in list.\n");
        free(newNode);
        return NULL;
    }

    // make sure the chain doesnt break
    // previous should point to new node
    prev->next = newNode;

    // the new node should point to the node being inserted at
    newNode->next = node;

    return newNode;
}

int popNode(LinkedList *list, Node **node)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant pop element of NULL list.\n");
        return 0;
    }

    if (node == NULL) 
    {
        fprintf(stderr, "Cant pop NULL node.\n");
        return 0;
    }

    if (list->head->next == NULL)
    {
        fprintf(stderr, "Cant pop head if there are no other elements.\n");
        return 0;
    }

    // if it's the head, set head to element after head
    if (*node == list->head)
    {
        list->head = list->head->next;
        free(*node);
        *node = NULL;
        return 1;
    }

    // if the node isn't the head
    Node *temp = list->head;
    Node *prev = NULL;
    bool hasNode = false;

    // loop through list until it is the node
    while (temp != *node && temp != NULL)
    {
        // set new point to previous
        prev = temp;
        temp = temp->next;

        if (*node == temp)
        {
            hasNode = true;
        }
    }

    if (prev == NULL)
    {
        fprintf(stderr, "Error occurred removing in list.\n");
        return 0;
    }

    if (!hasNode) 
    {
        fprintf(stderr, "Node not found in list.\n");
        return 0;
    }

    // if it's the tail set tail to previous element and remove current tail
    if (*node == list->tail)
    {    
        free(*node);
        *node = NULL;
        list->tail = prev;
        // tail always points to null address
        list->tail->next = NULL;
        return 1;
    }


    // if it's not tail or head
    // point previous node to removed node's next node so chain doesn't break
    prev->next = (*node)->next;
    free(*node);
    *node = NULL;
    return 1;
}

Node *shiftList(LinkedList *list)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant shift head of NULL list.\n");
        return 0;
    }

    if (list->head->next == NULL)
    {
        fprintf(stderr, "Cant shift head without other elements\n");
        return NULL;
    }

    // remove head and replace it with next pointer node.
    Node *prev = list->head;
    list->head = list->head->next;


    prev->next = NULL;
    return prev;
}
//
// Node *popList(LinkedList *list)
// {
//     return NULL;
// }

int sizeOfLinkedList(LinkedList *list)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant size of NULL list.\n");
        return 0;
    }

    Node *temp = list->head;
    int size = 0;

    while (temp != NULL)
    {
        size++;

        temp = temp->next;
    }
    return size;
}

int isEmpty(LinkedList *list)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant check if NULL list empty.\n");
        return 0;
    }

    if (list->head->next == NULL)
    {
        return 1;
    } 
    else 
    {
        return 0;
    }
}

void printLinkedList(LinkedList *list)
{
    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant print NULL list.\n");
        return;
    }

    // Print linked list
    Node *temp = list->head;

    while (temp != NULL)
    {
        printf("(X:%f, Y:%f) -> ", temp->snake_node.x, temp->snake_node.y);
        temp = temp->next;
    }

    printf("\n");
}

LinkedList clearList(LinkedList *list)
{
    LinkedList clearedList = {NULL, NULL};

    if (list->head == NULL || list->tail == NULL)
    {
        fprintf(stderr, "Cant free NULL list.\n");
        return (LinkedList){NULL, NULL};
    }
    // Free allocated memory
    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    return clearedList;
}

void freeLinkedList(LinkedList *list)
{
    // Free allocated memory
    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}
