#pragma once

#include <assert.h>
#include <cstdio>
#include <type_traits>
#include <utility>

template <typename Node>
constexpr std::pair<Node*,Node*> FindNodePairsFromEnd(Node *head, std::size_t nFromEnd);

template <typename Node>
constexpr Node* DisconnectNode(Node* disconnect, Node *disconnectParent);

template <typename Node>
constexpr Node* DeleteNode(Node* head, const std::size_t nFromEnd);

#include "SinglyLinkedList.cpp"

