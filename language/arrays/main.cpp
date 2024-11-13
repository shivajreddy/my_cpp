#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    // Constructor
    ListNode(int val = -1, ListNode *next = nullptr) : val(val), next(next) {}
};

void print_linked_list(ListNode *root) {
    while (root != nullptr) {
        cout << root->val << " -> ";
        root = root->next;
    }
    cout << "nullptr\n";
}

void delete_linked_list(ListNode *head) {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

ListNode *create_sample_linked_list() {
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    return head;
}

int main() {

    ListNode *root = create_sample_linked_list();

    print_linked_list(root);

    delete_linked_list(root);

    return 0;
}
