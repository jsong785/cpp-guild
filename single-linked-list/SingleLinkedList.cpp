#include "SingleLinkedList.h"

Node* DisconnectNode(Node* disconnect, Node *disconnectParent)
{
    if(disconnect == nullptr)
    {
        return nullptr;
    }
    assert(disconnect != nullptr);

    if(disconnect != nullptr && disconnectParent == nullptr)
    {
        return disconnect;
    }
    assert(disconnect != nullptr && disconnectParent != nullptr);

    disconnectParent->next = disconnect->next;
    return disconnect;
}

Node* DeleteNode(Node* head, std::size_t nFromEnd)
{
    const auto nodes = FindNodePairsFromEnd<std::size_t>(head, nFromEnd);
    Node* newHead = head;
    if(nodes.first == head) {
        newHead = nodes.first->next;
    }

    auto special = DisconnectNode(nodes.first, nodes.second);
    delete special;
    return newHead;
}
