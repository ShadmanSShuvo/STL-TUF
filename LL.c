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
    // declare head, tail, cur and other variables you need
    node *head;
    node *tail;
    node *cur;
    int size;
} linkedList;

void init(linkedList *list)
{
    // implement initialization
    list->head = NULL;
    list->cur = NULL;
    list->tail = NULL;
    list->size = 0;
}

void free_list(linkedList *list)
{
    // implement destruction of list
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
    // implement list printing
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
    // implement insert function
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

int delete_cur(linkedList *list)
{
    // implement deletion of current index function
    if (list->cur == NULL)
        return -1;

    node *temp = list->cur;
    int deleted = temp->element;

    if (list->head == list->tail)
    { // single element
        list->head = list->tail = list->cur = NULL;
    }
    else if (list->cur == list->head)
    { // delete head
        list->head = list->cur->next;
        list->head->prev = NULL;
        list->cur = list->head;
    }
    else if (list->cur == list->tail)
    { // delete tail
        list->tail = list->cur->prev;
        list->tail->next = NULL;
        list->cur = list->tail;
    }
    else
    { // delete middle
        list->cur->prev->next = list->cur->next;
        list->cur->next->prev = list->cur->prev;
        list->cur = list->cur->next;
    }
    free(temp);
    list->size--;
    print(list);
    return deleted;
}

void append(int item, linkedList *list)
{
    // implement append function
    node *newNode = (node *)malloc(sizeof(node));
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

int size(linkedList *list)
{
    // implement size function
    return list->size;
}

void prev(int n, linkedList *list)
{
    // implement prev function
    while (n > 0 && list->cur != NULL && list->cur->prev != NULL)
    {
        list->cur = list->cur->prev;
        n--;
    }
    print(list);
}

void next(int n, linkedList *list)
{
    // implement next function
    while (n > 0 && list->cur != NULL && list->cur->next != NULL)
    {
        list->cur = list->cur->next;
        n--;
    }
    print(list);
}

int is_present(int n, linkedList *list)
{
    // implement presence checking function
    node *temp = list->head;
    while (temp != NULL)
    {
        if (temp->element == n)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void clear(linkedList *list)
{
    // implement list clearing function
    free_list(list);
    init(list);
}

void delete_item(int item, linkedList *list)
{
    // implement item deletion function
    node *temp = list->head;
    while (temp != NULL)
    {
        if (temp->element == item)
        {
            list->cur = temp;
            delete_cur(list);
            return;
        }
        temp = temp->next;
    }
    printf("%d not found\n", item);
}

void swap_ind(int ind1, int ind2, linkedList *list)
{
    // implement swap function
    if (ind1 == ind2)
        return;

    node *n1 = list->head;
    node *n2 = list->head;
    int i = 0;

    while (n1 != NULL && i < ind1)
    {
        n1 = n1->next;
        i++;
    }

    i = 0;
    while (n2 != NULL && i < ind2)
    {
        n2 = n2->next;
        i++;
    }

    if (n1 != NULL && n2 != NULL)
    {
        int temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }
    print(list);
}

// Reverses the linked list and returns the new head
node *reverse(linkedList *list)
{
    // Handle empty list or single element list (no change needed)
    if (list->head == NULL || list->head == list->tail)
        return list->head;

    node *current = list->head;
    node *temp = NULL;

    // Swap next and prev pointers for all nodes
    while (current != NULL)
    {
        // Store next node before we change the pointer
        temp = current->next;

        // Swap the next and prev pointers
        current->next = current->prev;
        current->prev = temp;

        // Move to the next node (which is now stored in prev)
        current = temp;
    }

    // Swap head and tail pointers
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;

    // Update current pointer if needed
    // If current was pointing to head, it should now point to tail and vice versa
    if (list->cur == temp)
    { // cur was at old head
        list->cur = list->head;
    }
    else if (list->cur == list->head)
    { // cur was at old tail
        list->cur = list->tail;
    }

    return list->head;
}

// Finds the middle node of the linked list
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

// Creates a copy of the linked list and returns a new linkedList structure
linkedList *copyList(linkedList *original)
{
    linkedList *copy = (linkedList *)malloc(sizeof(linkedList));
    init(copy);

    node *current = original->head;
    while (current != NULL)
    {
        append(current->element, copy);
        current = current->next;
    }

    return copy;
}

// Checks if a linked list is a palindrome without modifying the original list
int isPalindrome(linkedList *list)
{
    if (list->head == NULL || list->head == list->tail)
        return 1; // Empty list or single element list is a palindrome

    // Create a copy of the list to avoid modifying the original
    linkedList *copy = copyList(list);

    // Find the middle of the copied list
    node *middle = findMiddle(copy);

    // Create a new list for the second half
    linkedList secondHalf;
    init(&secondHalf);

    // Populate the second half list
    node *current = middle;
    while (current != NULL)
    {
        append(current->element, &secondHalf);
        current = current->next;
    }

    // Reverse the second half
    reverse(&secondHalf);

    // Compare the first half with the reversed second half
    node *first = list->head;
    node *second = secondHalf.head;

    while (first != middle && second != NULL)
    {
        if (first->element != second->element)
        {
            free_list(copy);
            free_list(&secondHalf);
            return 0; // Not a palindrome
        }
        first = first->next;
        second = second->next;
    }

    // Clean up
    free_list(copy);
    free_list(&secondHalf);

    return 1; // Is a palindrome
}

void merge_sorted(linkedList *list1, linkedList *list2, linkedList *result)
{
    init(result);
    node *p1 = list1->head, *p2 = list2->head;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->element <= p2->element)
        {
            append(p1->element, result);
            p1 = p1->next;
        }
        else
        {
            append(p2->element, result);
            p2 = p2->next;
        }
    }
    while (p1 != NULL)
    {
        append(p1->element, result);
        p1 = p1->next;
    }
    while (p2 != NULL)
    {
        append(p2->element, result);
        p2 = p2->next;
    }
}

void remove_duplicates(linkedList *list)
{
    if (list->size <= 1)
        return;
    node *current = list->head;
    while (current != NULL && current->next != NULL)
    {
        if (current->element == current->next->element)
        {
            node *temp = current->next;
            current->next = temp->next;
            if (temp->next != NULL)
                temp->next->prev = current;
            else
                list->tail = current;
            if (list->cur == temp)
                list->cur = current;
            free(temp);
            list->size--;
        }
        else
        {
            current = current->next;
        }
    }
    print(list);
}

void rotate_right(linkedList *list, int k)
{
    if (list->size <= 1 || k == 0)
        return;
    k = k % list->size;
    if (k < 0)
        k += list->size;
    list->tail->next = list->head;
    list->head->prev = list->tail;
    node *new_tail = list->tail;
    for (int i = 0; i < k; i++)
    {
        new_tail = new_tail->next;
    }
    list->head = new_tail->next;
    list->tail = new_tail;
    list->head->prev = NULL;
    list->tail->next = NULL;
    list->cur = list->head; // Adjust as needed
    print(list);
}

int hasCycle(linkedList *list)
{
    node *fast = list->head;
    node *slow = list->head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return 1;
    }
    return 0;
}

node *nthFromEnd(linkedList *list, int n)
{
    // Implement here using lead-lag pointers
    node *first = list->head;
    node *second = list->head;
    for (int i = 0; i < n; i++)
    {
        if (first == NULL)
        {
            printf("wrong n\n");
            return NULL;
        }
        first = first->next;
    }
    while (first != NULL)
    {
        first = first->next;
        second = second->next;
    }

    return second;
}

node *removeNthFromEnd(linkedList *list, int n)
{
    if (n > list->size || n <= 0)
    {
        printf("Invalid n\n");
        return NULL;
    }

    // Create a dummy node to simplify edge cases (like deleting head)
    node *dummy = (node *)malloc(sizeof(node));
    dummy->next = list->head;
    dummy->prev = NULL;

    node *first = dummy;
    node *second = dummy;

    // Move first n+1 steps ahead
    for (int i = 0; i <= n; i++)
    {
        if (first == NULL)
        {
            printf("Invalid n\n");
            free(dummy);
            return NULL;
        }
        first = first->next;
    }

    // Move both pointers until first reaches the end
    while (first != NULL)
    {
        first = first->next;
        second = second->next;
    }

    // Delete the node after `second`
    node *toDelete = second->next;
    second->next = toDelete->next;
    if (toDelete->next != NULL)
    {
        toDelete->next->prev = second;
    }
    else
    {
        // Deleting tail
        list->tail = second == dummy ? NULL : second;
    }

    if (second == dummy)
    {
        // Deleted node was head
        list->head = toDelete->next;
    }

    free(toDelete);
    free(dummy);
    list->size--;

    return list->head;
}

/*
node* cse22a(linkedList *list){
    node* mid = findMiddle(list);
    node* midNew = reverse(list);

    node* temp1 = list->head, *temp2 = midNew;
    while (temp1!=NULL && temp2 != NULL)
    {
        node* temp = temp1->next;
        temp1->next = temp2;
        temp2->next = temp;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    temp2->next = NULL;
    return list->head;
}
*/

node* cse22a(linkedList *list) {
    if (list->head == NULL || list->head->next == NULL) {
        return list->head;
    }

    // Find the middle node
    node *mid = findMiddle(list);

    // Split the list into two halves
    linkedList secondHalf;
    init(&secondHalf);
    node *current = mid->next;
    mid->next = NULL; // End of first half
    while (current != NULL) {
        append(current->element, &secondHalf);
        current = current->next;
    }

    // Reverse the second half
    reverse(&secondHalf);

    // Interleave the first half and reversed second half
    node *temp1 = list->head;
    node *temp2 = secondHalf.head;
    while (temp1 != NULL && temp2 != NULL) {
        node *next1 = temp1->next;
        node *next2 = temp2->next;

        temp1->next = temp2;
        temp2->prev = temp1;

        if (next1 != NULL) {
            temp2->next = next1;
            next1->prev = temp2;
        }

        temp1 = next1;
        temp2 = next2;
    }

    // Update tail
    if (temp1 != NULL) {
        list->tail = temp1;
        while (list->tail->next != NULL) {
            list->tail = list->tail->next;
        }
    } else if (temp2 != NULL) {
        list->tail = temp2;
        while (list->tail->next != NULL) {
            list->tail = list->tail->next;
        }
    } else {
        list->tail = list->head;
        while (list->tail->next != NULL) {
            list->tail = list->tail->next;
        }
    }

    // Update cur (optional: set to head or keep as is)
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
    linkedList list;
    init(&list);
    insert(1,&list);
    insert(2,&list);
    insert(3,&list);
    insert(4,&list);
    insert(5,&list);
    insert(6,&list);
    insert(7,&list);
    insert(8,&list);
    node* new = cse22a(&list);
    print(&list);

    free_list(&list);
    free(&list); 
    return 0;
}
