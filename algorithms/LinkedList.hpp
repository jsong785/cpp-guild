#pragma once

#include <utility>

namespace LinkedList {

template <typename T>
constexpr std::pair<T*, T*> GetNFromEndSinglyLinkedListNonCircular(T *head, const unsigned N) {
    auto nFromEnd{ N };
    T* slowParent{ nullptr };
    T* slow{ nullptr };

    T* headCopy{ head };
    while(head != nullptr) {
        if(slow != nullptr) {
            slow = slow->next;
        }
        if(slowParent != nullptr) {
            slowParent = slowParent->next;
        }

        if(slowParent == nullptr && slow != nullptr) {
            slowParent = headCopy;
        }
        if(nFromEnd == 0 && slow == nullptr) {
            slow = headCopy;
        }

        if(nFromEnd > 0) {
            --nFromEnd;
        }

        head = head->next;
    }
    return { slow, slowParent };
}

template <typename T>
constexpr std::pair<T*, T*> DeleteNFromEndSinglyLinkedListNonCircular(T *head, const unsigned N) {
    auto nodes{ GetNFromEndSinglyLinkedListNonCircular(head, N) };
    if(nodes.first != nullptr) {
        if(nodes.first == head) {
            head = nodes.first->next;
        }
        if(nodes.second != nullptr) {
            nodes.second->next = nodes.first->next;
        }
    }
    return { head, nodes.first };
}

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
