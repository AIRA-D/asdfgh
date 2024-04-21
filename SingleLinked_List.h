//
// Created by aira on 21.04.24.
//

#ifndef INC_4444_SINGLELINKED_LIST_H
#define INC_4444_SINGLELINKED_LIST_H


template <class T>
struct Node {
    T data;
    Node* next;
};

template <class T>
class SingleLinkedList {
private:
    Node<T>* head;

public:
    SingleLinkedList() : head(nullptr) {}

    void insert(T value) {
        auto* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void remove(T value) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current != nullptr && current->data != value) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
    }

    bool search(T value) {
        Node<T>* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }

        return false;
    }
};


#endif //INC_4444_SINGLELINKED_LIST_H
