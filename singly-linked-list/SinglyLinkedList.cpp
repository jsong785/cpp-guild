#pragma once

template <typename Node>
constexpr std::pair<Node*, Node*> FindNodePairsFromEnd(Node* head, std::size_t nFromEnd)
{
    if(head == nullptr)
    {
        return { nullptr, nullptr };
    }

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
            if(nFromEnd == 0)
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
constexpr Node* DisconnectNode(Node* disconnect, Node *disconnectParent)
{
    if(disconnect == nullptr)
    {
        return nullptr;
    }
    else if(disconnectParent == nullptr)
    {
        return disconnect;
    }

    disconnectParent->next = disconnect->next;
    return disconnect;
}

template <typename Node>
constexpr Node* DeleteNode(Node* head, const std::size_t nFromEnd)
{
    const auto nodes = FindNodePairsFromEnd(head, nFromEnd);
    Node* newHead = head;
    if(nodes.first == head) 
    {
        newHead = nodes.first->next;
    }

    delete DisconnectNode(nodes.first, nodes.second);
    return newHead;
}
