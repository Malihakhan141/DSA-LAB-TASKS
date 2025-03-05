#include <iostream>
using namespace std;

class ListNode {
public:
    int data;
    ListNode* nextNode;

    ListNode(int val) {
        data = val;
        nextNode = NULL;
    }
};

class LinkedList {
public:
    ListNode* first;

    LinkedList() {
        first = NULL;
    }

    void addToBeginning(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->nextNode = first;
        first = newNode;
    }

    void addToEnd(int val) {
        ListNode* newNode = new ListNode(val);
        if (first == NULL) {
            first = newNode;
            return;
        }
        ListNode* temp = first;
        while (temp->nextNode != NULL) {
            temp = temp->nextNode;
        }
        temp->nextNode = newNode;
    }

    void printList() {
        if (first == NULL) {
            cout << "The list is currently empty!" << endl;
            return;
        }
        ListNode* temp = first;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->nextNode;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList list;
    list.addToBeginning(1);
    list.printList();
    list.addToEnd(4);
    list.printList();
    return 0;
}

