#include <iostream>
using namespace std;

class DoubleNode {
public:
    int value;
    DoubleNode* nextNode;
    DoubleNode* prevNode;

    DoubleNode(int v) {
        value = v;
        nextNode =NULL;
        prevNode = NULL;
    }
};

class DoubleLinkedList {
public:
    DoubleNode* firstNode;

    DoubleLinkedList() {
        firstNode = NULL;
    }

    void append(int val) {
        DoubleNode* newNode = new DoubleNode(val);
        if (firstNode == NULL) {
            firstNode = newNode;
        }
        else {
            DoubleNode* temp = firstNode;
            while (temp->nextNode != NULL) {
                temp = temp->nextNode;
            }
            temp->nextNode = newNode;
            newNode->prevNode = temp;
        }
    }

    void showList() {
        DoubleNode* temp = firstNode;
        while (temp != NULL) {
            cout << temp->value << " <-> ";
            temp = temp->nextNode;
        }
        cout << "NULL" << endl;
    }
};

DoubleNode* mergeLists(DoubleNode* list1, DoubleNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    DoubleNode* mergedHead = NULL;
    if (list1->value < list2->value) {
        mergedHead = list1;
        list1 = list1->nextNode;
    }
    else {
        mergedHead = list2;
        list2 = list2->nextNode;
    }

    DoubleNode* temp = mergedHead;
    while (list1 && list2) {
        if (list1->value < list2->value) {
            temp->nextNode = list1;
            list1->prevNode = temp;
            list1 = list1->nextNode;
        }
        else {
            temp->nextNode = list2;
            list2->prevNode = temp;
            list2 = list2->nextNode;
        }
        temp = temp->nextNode;
    }

    if (list1) temp->nextNode = list1, list1->prevNode = temp;
    if (list2) temp->nextNode = list2, list2->prevNode = temp;

    return mergedHead;
}

int main() {
    DoubleLinkedList dll1, dll2;
    dll1.append(1);
    dll1.append(3);
    dll1.append(5);
    dll2.append(2);
    dll2.append(4);
    dll2.append(6);

    cout << "First Doubly Linked List: ";
    dll1.showList();

    cout << "Second Doubly Linked List: ";
    dll2.showList();

    DoubleLinkedList mergedDLL;
    mergedDLL.firstNode = mergeLists(dll1.firstNode, dll2.firstNode);

    cout << "Merged Doubly Linked List: ";
    mergedDLL.showList();

    return 0;
}

