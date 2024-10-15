#include <iostream>

using namespace std;

/*
  - Build Linked List
  - Build Deque
*/

// Linked List Node
struct ListNode {
  int val;
  ListNode *next;

  // Constructor
  ListNode(int val) : val(val), next(nullptr) {}
};

void print_list(ListNode *root) {
  ListNode *curr = root;

  while (curr != nullptr) {
    cout << curr->val << " -> ";
    curr = curr->next;
  }
  cout << "NULL" << "\n";
}

int main() {

  ListNode *head = new ListNode(-1);
  ListNode *n1 = new ListNode(10);
  ListNode *n2 = new ListNode(20);
  ListNode *n3 = new ListNode(30);
  ListNode *tail = new ListNode(-1);
  head->next = n1;
  n1->next = n2;
  n2->next = n3;
  n3->next = tail;

  print_list(head);

  // Clean up memory
  delete head;
  delete n1;
  delete n2;
  delete n3;
  delete tail;

  return 0;
}
