#pragma once

typedef struct Node {              
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;          
    Node *tail;
} LinkedList;

LinkedList createList(int data);
Node *createNode(int data);

Node *insertAtTail(LinkedList *list, int data);
Node *insertAtHead(LinkedList *list, int data);
Node *insertAtNode(LinkedList *list, Node *node, int data);

int sizeOfLinkedList(LinkedList *list);
int isEmpty(LinkedList *list);

Node *shiftList(LinkedList *list);
Node *popList(LinkedList *list);
int popNode(LinkedList *list, Node **node);

void freeLinkedList(LinkedList *list);
void printLinkedList(LinkedList *list);

