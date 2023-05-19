#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

void Insert(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void PrintList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

double CalculateAverage(Node* head) {
    int sum = 0;
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        sum += current->data;
        count++;
        current = current->next;
    }

    if (count > 0) {
        return (double)(sum) / count;
    } else {
        return 0.0;
    }
}

void RearrangeList(Node*& head, Node*& tail) {
    double average = CalculateAverage(head);
    Node* current = head;
    Node* smallerHead = nullptr;
    Node* smallerTail = nullptr;
    Node* largerHead = nullptr;
    Node* largerTail = nullptr;

    while (current != nullptr) {
        Node* next = current->next;
        if (current->data < average) {
            if (smallerHead == nullptr) {
                smallerHead = smallerTail = current;
            } else {
                smallerTail->next = current;
                current->prev = smallerTail;
                smallerTail = current;
            }
        } else {
            if (largerHead == nullptr) {
                largerHead = largerTail = current;
            } else {
                largerTail->next = current;
                current->prev = largerTail;
                largerTail = current;
            }
        }
        current = next;
    }

    if (smallerHead != nullptr) {
        smallerTail->next = largerHead;
        if (largerHead != nullptr) {
            largerHead->prev = smallerTail;
        }
        head = smallerHead;
    } else {
        head = largerHead;
    }

    if (largerHead != nullptr) {
        largerTail->next = nullptr;
        tail = largerTail;
    } else {
        tail = smallerTail;
    }
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    ifstream inputFile("/Users/uliazapletnuk/Desktop/^_^/АП/filesAp12.8/inputs.txt");
    if (inputFile.is_open()) {
        int num;
        while (inputFile >> num) {
            Insert(head, tail, num);
        }
        inputFile.close();
    } else {
        cout << "Unable to open the file." << endl;
        return 1;
    }

    cout << "Список до змін: ";
    PrintList(head);
    cout << "Середнє арифметичне: " << CalculateAverage(head) << endl;

    RearrangeList(head, tail);

    cout << "Список після змін: ";
    PrintList(head);

    return 0;
}
