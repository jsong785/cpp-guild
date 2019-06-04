#pragma once

#include <assert.h>
#include <cstdio>
#include <type_traits>
#include <utility>

template <typename Node, typename Iterable>
std::pair<Node*,Node*> FindNodePairsFromEnd(Node head, Iterable nFromEnd, const Iterable begin);

template <typename Node>
Node* DisconnectNode(Node* disconnect, Node *disconnectParent);

template <typename Node, typename Iterable>
Node* DeleteNode(Node* head, Iterable nFromEnd, const Iterable begin);

#include "SinglyLinkedList.cpp"

