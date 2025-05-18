#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v) : data(v), next(nullptr) {}
};

Node* reverse(Node* head) {
    Node *prev = nullptr, *curr = head;
    while (curr) swap(curr->next, prev), swap(prev, curr);
    return prev;
}

void printList(Node* head) {
    while (head) {
        cout << head->data << (head->next ? " " : "\n");
        head = head->next;
    }
}

int main() {
    int m;
    cin >> m;
    Node *head = nullptr, *tail = nullptr;
    while (m--) {
        int v;
        cin >> v;
        Node* node = new Node(v);
        if (!head) head = tail = node;
        else tail->next = node, tail = node;
    }

    if (!head || !head->next) return printList(head), 0;

    Node *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next) prev = slow, slow = slow->next, fast = fast->next->next;
    if (prev) prev->next = nullptr;

    Node *l1 = head, *l2 = reverse(slow), *dummy = new Node(0), *curr = dummy;
    while (l1 || l2) {
        if (l1) curr->next = l1, curr = l1, l1 = l1->next;
        if (l2) curr->next = l2, curr = l2, l2 = l2->next;
    }

    printList(dummy->next);

    // Optional: Free memory (not strictly needed in contests)
    while (dummy) {
        Node* tmp = dummy;
        dummy = dummy->next;
        delete tmp;
    }
    return 0;
}