#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to reverse a linked list
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main() {
    int m;
    cin >> m;
    
    // Read and create linked list L
    Node* L = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < m; i++) {
        int val;
        cin >> val;
        Node* newNode = new Node(val);
        if (!L) {
            L = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    // If list is empty or single node, no change
    if (!L || !L->next) {
        Node* curr = L;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " ";
            curr = curr->next;
        }
        cout << endl;
        return 0;
    }
    
    // Find middle using slow and fast pointers
    Node* slow = L;
    Node* fast = L;
    Node* prev_slow = nullptr;
    while (fast->next && fast->next->next) {
        prev_slow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast->next) {
        prev_slow = slow;
        slow = slow->next;
    }
    
    // Split and reverse second half
    if (prev_slow) prev_slow->next = nullptr;
    Node* second_half = reverseList(slow);
    
    // Merge lists by interleaving
    Node* first_half = L;
    Node* dummy = new Node(0);
    Node* curr = dummy;
    
    while (first_half || second_half) {
        if (first_half) {
            curr->next = first_half;
            curr = first_half;
            first_half = first_half->next;
        }
        if (second_half) {
            curr->next = second_half;
            curr = second_half;
            second_half = second_half->next;
        }
    }
    
    // Print reordered list
    Node* result = dummy->next;
    while (result) {
        cout << result->data;
        if (result->next) cout << " ";
        result = result->next;
    }
    cout << endl;
    
    // Clean up memory
    while (dummy->next) {
        Node* temp = dummy->next;
        dummy->next = temp->next;
        delete temp;
    }
    delete dummy;
    
    return 0;
}