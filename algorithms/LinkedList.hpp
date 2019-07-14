#pragma once

namespace LinkedList {

template <typename T>
T* ReverseSinglyLinkedListNonCircular(T* head) {
    T* cache{ nullptr };
    while(head != nullptr) {
        auto currentHead{ head };
        head = head->next;
        currentHead->next = cache;
        cache = currentHead;
    }
    return cache;
}

template <typename T>
T* ReverseSinglyLinkedListCircular(T* head) {
    T* headCache{ head };
    T* cache{ nullptr };
    while(head != nullptr) {
        auto currentHead{ head };
        head = head->next;
        currentHead->next = cache;
        cache = currentHead;

        if(currentHead->next == headCache) {
            return currentHead;
        }
    }
    return nullptr;
}

template <typename T>
T* ReverseDoublyLinkedListNonCircular(T* head) {
    while(head != nullptr) {
        auto current{ head };
        head = head->next;

        auto next = current->next;
        auto prev = current->prev;

        current->prev = next;
        current->next = prev;
        
        if(head == nullptr) {
            return current;
        }
    }
    return nullptr;
}

template <typename T>
T* ReverseDoublyLinkedListCircular(T* head) {
    auto headCache{ head };
    while(head != nullptr) {
        auto current{ head };
        head = head->next;

        auto next = current->next;
        auto prev = current->prev;

        current->prev = next;
        current->next = prev;
        if(current->prev == headCache) {
            return current;
        }
    }
    return nullptr;
}

}
