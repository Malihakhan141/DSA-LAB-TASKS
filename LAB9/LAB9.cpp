#include <iostream>
using namespace std;
class Node {
public:
    int value;
    Node* next;
    Node* prev;

    Node(int v) {
        value = v;
        next = prev = NULL;
    }
};
class CircularLinkedList {
public:
    Node* head;
    CircularLinkedList() {
        head = NULL;
    }
    void insert_AT_First(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insert_AT_Last(int val) {
        if (!head) {
            insert_AT_First(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
    }
    void insert_At_Nth(int val, int pos) {
        if (pos == 1 || !head) {
            insert_AT_First(val);
            return;
        }
        Node* temp = head;
        for (int i = 1; i < pos - 1 && temp->next != head; i++) {
            temp = temp->next;
        }
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
    void insert_AT_Center(int val) {
        if (!head || head->next == head) {
            insert_AT_First(val);
            return;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }
        insert_At_Nth(val, (fast->next == head) ? 2 : 3);
    }
    
    void displayForward() {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->value << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(head)" << endl;
    }

    void displayReverse() {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        Node* tail = head->prev;
        Node* temp = tail;
        do {
            cout << temp->value << " <- ";
            temp = temp->prev;
        } while (temp != tail);
        cout << "(head)" << endl;
    }
};
int main() {
    CircularLinkedList cll;
    cll.insert_AT_Last(10);
    cll.insert_AT_Last(20);
    cll.insert_AT_First(5);
    cll.insert_At_Nth(15, 3);
    cll.insert_AT_Center(12);

    cout << "Circular Linked List (Forward): ";
    cll.displayForward();
    cout << "Circular Linked List (Reverse): ";
    cll.displayReverse();
    
    return 0;
}
