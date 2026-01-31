#pragma once

typedef struct SnakeNode {
    int x;
    int y;
} SnakeNode;

typedef struct Node {              
    SnakeNode snake_node;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;          
    Node *tail;
} LinkedList;

LinkedList createList(SnakeNode snake_node);
Node *createNode(SnakeNode snake_node);

Node *insertAtTail(LinkedList *list, SnakeNode snake_node);
Node *insertAtHead(LinkedList *list, SnakeNode snake_node);
Node *insertAtNode(LinkedList *list, Node *node, SnakeNode snake_node);

int sizeOfLinkedList(LinkedList *list);
int isEmpty(LinkedList *list);

Node *shiftList(LinkedList *list);
Node *popList(LinkedList *list);
int popNode(LinkedList *list, Node **node);

void freeLinkedList(LinkedList *list);
void printLinkedList(LinkedList *list);

