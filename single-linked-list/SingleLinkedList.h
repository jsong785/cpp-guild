#pragma once

#include <assert.h>
#include <cstdio>
#include <type_traits>
#include <utility>

struct Node
{
    Node(const std::size_t id, Node *next) :
        id(id),
        next(next) {}
    virtual ~Node() = default;
    const std::size_t id{ 0 };
    Node *next;
};

using NodePair = std::pair<Node*, Node*>;

template <typename T>
NodePair FindNodePairsFromEnd(
        Node* head,
        T nFromEnd)
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
        // nFromEnd will round trip from 0
        // for linkedlists behind std::size_t, this
        // method is not correct
        else if(nNode == nullptr && nFromEnd-- == 0)
        {
            nNode = head;
        }

        current = current->next;
    }
    return { nNode, nNodeParent };

}

Node* DisconnectNode(Node* disconnect, Node *disconnectParent);

Node* DeleteNode(Node* head, std::size_t nFromEnd);

