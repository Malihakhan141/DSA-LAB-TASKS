//1. With Array; Push, Pop, Display 
//#include <iostream>
//using namespace std;
//class StackArray {
//private:
//    int topIndex;
//    int stackElements[100];
//    int capacity;
//
//public:
//    StackArray(int maxSize = 100) {
//        topIndex = -1;
//        capacity = maxSize;
//    }
//    void push(int value) {
//        if (topIndex == capacity - 1) {
//            cout << "Stack Overflow\n";
//            return;
//        }
//        stackElements[++topIndex] = value;
//    }
//    void pop() {
//        if (topIndex == -1) {
//            cout << "Stack Underflow\n";
//            return;
//        }
//        topIndex--;
//    }
//    void display() {
//        if (topIndex == -1) {
//            cout << "Stack is empty\n";
//            return;
//        }
//        cout << "Stack (Top -> Bottom): ";
//        for (int i = topIndex; i >= 0; i--) {
//            cout << stackElements[i] << " ";
//        }
//        cout << "\n";
//    }
//};
//int main() {
//    StackArray myStack;
//
//    myStack.push(10);
//    myStack.push(20);
//    myStack.push(30);
//    myStack.display();
//
//    myStack.pop();
//    myStack.display();
//
//    return 0;
//}

//2. With Linkedlist; Push, Pop, Display
//
//#include <iostream>
//using namespace std;
//
//class StackNode {
//public:
//    int value;
//    StackNode* nextNode;
//
//    StackNode(int val) {
//        value = val;
//        nextNode = NULL;
//    }
//};
//class LinkedStack {
//private:
//    StackNode* topNode;
//public:
//    LinkedStack() {
//        topNode = NULL;
//    }
//    void push(int val) {
//        StackNode* newElement = new StackNode(val);
//        newElement->nextNode = topNode;
//        topNode = newElement;
//    }
//    void pop() {
//        if (topNode == NULL) {
//            cout << "Stack Underflow\n";
//            return;
//        }
//        StackNode* tempNode = topNode;
//        topNode = topNode->nextNode;
//        delete tempNode;
//    }
//    void display() {
//        if (topNode == NULL) {
//            cout << "Stack is empty\n";
//            return;
//        }
//        StackNode* current = topNode;
//        cout << "Stack (Top -> Bottom): ";
//        while (current != NULL) {
//            cout << current->value << " ";
//            current = current->nextNode;
//        }
//        cout << "\n";
//    }
//};
//int main() {
//    LinkedStack myStack;
//
//    myStack.push(100);
//    myStack.push(200);
//    myStack.push(300);
//    myStack.display();
//
//    myStack.pop();
//    myStack.display();
//
//    return 0;
//}

