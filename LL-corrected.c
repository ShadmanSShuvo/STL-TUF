#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node *next;
    struct node *prev;
} node;

typedef struct
{
    node *head;
    node *tail;
    node *cur;
    int size;
} linkedList;

// Include other functions (init, free_list, print, insert, etc.) as provided
// Use the corrected versions from the previous response, especially for nthFromEnd

void init(linkedList *list)
{
    list->head = NULL;
    list->cur = NULL;
    list->tail = NULL;
    list->size = 0;
}

void free_list(linkedList *list)
{
    node *current = list->head;
    node *temp;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    list->size = 0;
}

void print(linkedList *list)
{
    if (list->size == 0)
    {
        printf("[ . ]\n");
        return;
    }
    node *temp = list->head;
    printf("[ ");
    while (temp != NULL)
    {
        printf("%d ", temp->element);
        if (temp == list->cur)
            printf("| ");
        else
            printf(" ");
        temp = temp->next;
    }
    printf("]\n");
}

void insert(int item, linkedList *list)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->element = item;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (list->cur == NULL)
    {
        list->head = list->tail = list->cur = newNode;
    }
    else
    {
        newNode->prev = list->cur;
        newNode->next = list->cur->next;

        if (list->cur->next != NULL)
            list->cur->next->prev = newNode;
        else
            list->tail = newNode;

        list->cur->next = newNode;
        list->cur = newNode;
    }

    list->size++;
    print(list);
}

void append(int item, linkedList *list)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->element = item;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL)
        list->tail->next = newNode;
    else
        list->head = newNode;

    list->tail = newNode;
    list->cur = newNode;
    list->size++;
    print(list);
}

node *findMiddle(linkedList *list)
{
    if (list->head == NULL)
        return NULL;

    node *fast = list->head;
    node *slow = list->head;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow;
}

node *reverse(linkedList *list)
{
    if (list->head == NULL || list->head == list->tail)
        return list->head;

    node *current = list->head;
    node *temp = NULL;

    while (current != NULL)
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    temp = list->head;
    list->head = list->tail;
    list->tail = temp;

    if (list->cur == temp)
        list->cur = list->head;
    else if (list->cur == list->head)
        list->cur = list->tail;

    return list->head;
}

node *cse22a(linkedList *list)
{
    if (list->head == NULL || list->head->next == NULL)
    {
        return list->head;
    }

    // Find the middle node
    node *mid = findMiddle(list);

    // Split the list into two halves
    linkedList secondHalf;
    init(&secondHalf);
    node *current = mid->next;
    if (mid->next != NULL)
    {
        mid->next->prev = NULL; // Ensure second half's head has no prev
    }
    mid->next = NULL; // End of first half
    while (current != NULL)
    {
        append(current->element, &secondHalf);
        current = current->next;
    }

    // Reverse the second half
    reverse(&secondHalf);

    // Interleave the first half and reversed second half
    node *temp1 = list->head;
    node *temp2 = secondHalf.head;
    while (temp1 != NULL && temp2 != NULL)
    {
        node *next1 = temp1->next;
        node *next2 = temp2->next;

        temp1->next = temp2;
        temp2->prev = temp1;

        if (next1 != NULL)
        {
            temp2->next = next1;
            next1->prev = temp2;
        }

        temp1 = next1;
        temp2 = next2;
    }

    // Update tail
    if (temp1 != NULL)
    {
        list->tail = temp1;
        while (list->tail->next != NULL)
        {
            list->tail = list->tail->next;
        }
    }
    else if (temp2 != NULL)
    {
        list->tail = temp2;
        while (list->tail->next != NULL)
        {
            list->tail = list->tail->next;
        }
    }
    else
    {
        list->tail = list->head;
        while (list->tail->next != NULL)
        {
            list->tail = list->tail->next;
        }
    }

    // Update cur (set to head for consistency)
    list->cur = list->head;

    // Free the second half’s structure (nodes are now part of the main list)
    secondHalf.head = NULL;
    secondHalf.tail = NULL;
    secondHalf.cur = NULL;
    secondHalf.size = 0;
    free_list(&secondHalf);

    return list->head;
}

int main(int argc, char const *argv[])
{
    linkedList *list = (linkedList *)malloc(sizeof(linkedList));
    if (list == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    init(list);
    insert(1, list); // [ 1 | ]
    insert(2, list); // [ 1 2 | ]
    insert(3, list); // [ 1 2 3 | ]
    insert(4, list); // [ 1 2 3 4 | ]
    insert(5, list); // [ 1 2 3 4 5 | ]
    insert(6, list); // [ 1 2 3 4 5 6 | ]
    insert(7, list); // [ 1 2 3 4 5 6 7 | ]
    insert(8, list); // [ 1 2 3 4 5 6 7 8 | ]
    node *newHead = cse22a(list);
    print(list); // Should print: [ 1 8 2 7 3 6 4 5 | ]
    free_list(list);
    free(list);
    return 0;
}