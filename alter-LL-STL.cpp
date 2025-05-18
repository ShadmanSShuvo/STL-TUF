#include <iostream>
#include <memory>
using namespace std;

struct Node {
    int data;
    unique_ptr<Node> next;
    Node(int v) : data(v), next(nullptr) {}
};

void printList(const unique_ptr<Node>& head) {
    for (Node* curr = head.get(); curr; curr = curr->next.get())
        cout << curr->data << (curr->next ? " " : "\n");
}

unique_ptr<Node> reverse(unique_ptr<Node> head) {
    unique_ptr<Node> prev = nullptr;
    while (head) {
        auto next = move(head->next);
        head->next = move(prev);
        prev = move(head);
        head = move(next);
    }
    return prev;
}

int main() {
    int m;
    cin >> m;

    unique_ptr<Node> head = nullptr, *tail = &head;
    while (m--) {
        int val;
        cin >> val;
        *tail = make_unique<Node>(val);
        tail = &(*tail)->next;
    }

    if (!head || !head->next) {
        printList(head);
        return 0;
    }

    // Find middle
    Node *slow = head.get(), *fast = head.get(), *prev = nullptr;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next.get();
        fast = fast->next->next.get();
    }

    // Detach and reverse second half
    unique_ptr<Node> second_half;
    if (prev) {
        Node* curr = head.get();
        while (curr->next.get() != slow) curr = curr->next.get();
        second_half = reverse(move(curr->next));
    }

    // Merge first and reversed second halves
    unique_ptr<Node> result = nullptr, *ptr = &result;
    auto first = move(head);
    while (first || second_half) {
        if (first) {
            *ptr = move(first);
            ptr = &(*ptr)->next;
            first = move(*ptr);
        }
        if (second_half) {
            *ptr = move(second_half);
            ptr = &(*ptr)->next;
            second_half = move(*ptr);
        }
    }

    printList(result);
    return 0;
}