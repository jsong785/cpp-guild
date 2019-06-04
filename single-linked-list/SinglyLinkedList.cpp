#pragma once

template <typename Node, typename Iterable>
std::pair<Node*, Node*> FindNodePairsFromEnd(Node* head, Iterable nFromEnd, const Iterable begin)
{
    if(head == nullptr)
    {
        return { nullptr, nullptr };
    }
    assert(head != nullptr);

    Node* nNode = nullptr;
    Node* nNodeParent = nullptr;
    auto current = head;
    while(current != nullptr)
    {
        if(nNode != nullptr && nNodeParent == nullptr)
        {
            nNodeParent = head;
        }
        else if(nNodeParent != nullptr)
        {
            nNodeParent = nNodeParent->next;
        }

        if(nNode != nullptr)
        {
            nNode = nNode->next;
        }
        else if(nNode == nullptr)
        {
            if(nFromEnd == begin)
            {
                nNode = head;
            }
            else
            {
                --nFromEnd;
            }
        }

        current = current->next;
    }
    return { nNode, nNodeParent };
}

template <typename Node>
Node* DisconnectNode(Node* disconnect, Node *disconnectParent)
{
    if(disconnect == nullptr)
    {
        return nullptr;
    }
    else if(disconnectParent == nullptr)
    {
        return disconnect;
    }
    assert(disconnect != nullptr);
    assert(disconnectParent != nullptr);

    disconnectParent->next = disconnect->next;
    return disconnect;
}

template <typename Node, typename Iterable>
Node* DeleteNode(Node* head, Iterable nFromEnd, const Iterable begin)
{
    const auto nodes = FindNodePairsFromEnd(head, nFromEnd, begin);
    Node* newHead = head;
    if(nodes.first == head) {
        newHead = nodes.first->next;
    }

    delete DisconnectNode(nodes.first, nodes.second);
    return newHead;
}
