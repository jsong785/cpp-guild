#pragma once

namespace LinkedList {

template <typename T>
constexpr T* ReverseSinglyLinkedListNonCircular(T* head) {
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
constexpr T* ReverseSinglyLinkedListCircular(T* head) {
    T* cache{ nullptr };
    while(head != nullptr) {
        if(head->next == nullptr) {
            head->next = cache;
            break;
        }

        auto currentHead{ head };
        head = head->next;
        currentHead->next = cache;
        cache = currentHead;
    }
    return cache;
}

template <typename T>
constexpr T* ReverseDoublyLinkedListNonCircular(T* head) {
    T* current{ nullptr };
    while(head != nullptr) {
        current = head;
        head = head->next;
        std::swap(current->next, current->prev);
    }
    return current;
}

template <typename T>
constexpr T* ReverseDoublyLinkedListCircular(T* head) {
    T* current{ nullptr };
    const auto cache{ head };
    while(head != nullptr) {
        current = head;
        head = head->next;

        std::swap(current->next, current->prev);
        if(head == cache) {
            break;
        }
    }
    return current;
}

}
