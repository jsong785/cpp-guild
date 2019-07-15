#pragma once

namespace LinkedList {

template <typename T>
constexpr T* GetNFromEndSinglyLinkedListNonCircular(T *head, const unsigned N, T** nFromEndParent=nullptr) {
    auto nFromEnd{ N };
    T* slowParent{ nullptr };
    T* slow{ nullptr };

    T* headCopy{ head };
    while(head != nullptr) {
        // initialize or increment slowParent
        if(slowParent == nullptr && slow != nullptr) {
            slowParent = headCopy;
        }
        else if(slowParent != nullptr) {
            slowParent = slowParent->next;
        }

        // initialize or increment slow
        if(nFromEnd == 0 && slow == nullptr) {
            slow = headCopy;
        }
        else if(slow != nullptr) {
            slow = slow->next;
        }

        // decrement nFromEnd (for above logic)
        if(nFromEnd > 0) {
            --nFromEnd;
        }

        head = head->next;
    }
    if(nFromEndParent != nullptr) {
        *nFromEndParent = slowParent;
    }
    return slow;
}

template <typename T>
constexpr T* DeleteNFromEndSinglyLinkedListNonCircular(T *head, const unsigned N, T** nodeToDelete=nullptr) {
    T* nFromEndNodeParent{ nullptr };
    auto nFromEndNode{ GetNFromEndSinglyLinkedListNonCircular(head, N, &nFromEndNodeParent) };
    if(nFromEndNode != nullptr) {
        if(nFromEndNode == head) {
            head = nFromEndNode->next;
        }
        if(nFromEndNodeParent != nullptr) {
            nFromEndNodeParent->next = nFromEndNode->next;
        }
    }
    if(nodeToDelete != nullptr) {
        *nodeToDelete = nFromEndNode;
    }
    return head;
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
