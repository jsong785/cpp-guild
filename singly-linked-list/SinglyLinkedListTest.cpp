#include "SinglyLinkedList.hpp"
#include <limits>
#include "catch.hpp"
#include <iostream>

struct NodeMock
{
    ~NodeMock() 
    {
        if(deletedFunc)
        {
            deletedFunc(reinterpret_cast<ptrdiff_t>(this));
        }
    }

    const std::size_t id;
    std::function<void(ptrdiff_t)> deletedFunc;
    NodeMock *next{ nullptr };
};

TEST_CASE("FindNodePairsFromEnd max test", "[.]")
{
    auto head = new NodeMock{ 0 };

    auto last = head;
    const auto max = std::numeric_limits<short>::max();
    for(short i = 1; i <= max; ++i) // create std::size_t max + 1 nodes (0 based index)
    {
        auto current = new NodeMock{ static_cast<std::size_t>(i) };
        last->next = current;
        last = current;
    }

    SECTION("get head (delete head)")
    {
        auto nodes = FindNodePairsFromEnd(head, 0);
        CHECK(nodes.first == head);
        CHECK(nodes.second == nullptr);
    }
}

TEST_CASE("DeleteNFromEnd", "")
{
    ptrdiff_t addrDeleted = 0;
    const auto deleteFunc = [&addrDeleted](ptrdiff_t val) {
        addrDeleted = val;
    };

    SECTION("Delete tail")
    {
        auto head = new NodeMock{0, deleteFunc};
        auto one = new NodeMock{1, deleteFunc};

        head->next = one;

        auto newHead = DeleteNode(head, 0);
        CHECK(addrDeleted == reinterpret_cast<ptrdiff_t>(one));
        CHECK(newHead == head);
    }

    SECTION("Delete head")
    {
        auto head = new NodeMock{0, deleteFunc};
        auto one = new NodeMock{1, deleteFunc};

        head->next = one;

        auto newHead = DeleteNode(head, 1);
        CHECK(addrDeleted == reinterpret_cast<ptrdiff_t>(head));
        CHECK(newHead == one);
    }

    SECTION("Delete two")
    {
        auto head = new NodeMock{0, deleteFunc};
        auto one = new NodeMock{1, deleteFunc};
        auto two = new NodeMock{2, deleteFunc};
        auto three = new NodeMock{3, deleteFunc};

        head->next = one;
        one->next = two;
        two->next = three;

        auto newHead = DeleteNode(head, 1);
        CHECK(addrDeleted == reinterpret_cast<ptrdiff_t>(two));
        CHECK(newHead == head);
    }
}

TEST_CASE("DisconnectNode", "")
{
    SECTION("no nodes")
    {
        CHECK(DisconnectNode<NodeMock>(nullptr, nullptr) == nullptr);
    }

    SECTION("no parent, has node")
    {
        NodeMock node{0};
        CHECK(DisconnectNode<NodeMock>(&node, nullptr) == &node);
    }

    SECTION("has parent, no node")
    {
        NodeMock node{0};
        CHECK(DisconnectNode<NodeMock>(nullptr, &node) == nullptr);
    }

    SECTION("has parent, has node")
    {
        NodeMock parent{0};
        NodeMock node{1};
        node.next = &parent;
        CHECK(DisconnectNode(&node, &parent) == &node);
    }
}

TEST_CASE("FindNodePairsFromEnd", "")
{
    SECTION("no nodes")
    {
        const auto test1 = FindNodePairsFromEnd(static_cast<NodeMock*>(nullptr), 0);
        CHECK(test1.first == nullptr);
        CHECK(test1.second == nullptr);

        const auto test2 = FindNodePairsFromEnd(static_cast<NodeMock*>(nullptr), 1);
        CHECK(test2.first == nullptr);
        CHECK(test2.second == nullptr);

        const auto test3 = FindNodePairsFromEnd(static_cast<NodeMock*>(nullptr), 2);
        CHECK(test3.first == nullptr);
        CHECK(test3.second == nullptr);
    }

    SECTION("one node delete head")
    {
        NodeMock head{ 0 };

        const auto nodes = FindNodePairsFromEnd(&head, 0);
        CHECK(nodes.first == &head);
        CHECK(nodes.second == nullptr); // no parent
    }

    SECTION("one node no delete out of bounds")
    {
        NodeMock head{ 0 };

        const auto test1 = FindNodePairsFromEnd(&head, 1);
        CHECK(test1.first == nullptr);
        CHECK(test1.second == nullptr);

        const auto test2 = FindNodePairsFromEnd(&head, 1);
        CHECK(test2.first == nullptr);
        CHECK(test2.second == nullptr);
    }

    SECTION("two nodes")
    {
        NodeMock head{ 0 };
        NodeMock tail{ 1 };
        head.next = &tail;

        const auto test1 = FindNodePairsFromEnd(&head, 0);
        CHECK(test1.first == &tail);
        CHECK(test1.second == &head);

        const auto test2 = FindNodePairsFromEnd(&head, 1);
        CHECK(test2.first == &head);
        CHECK(test2.second == nullptr);

        const auto test3 = FindNodePairsFromEnd(&head, 100);
        CHECK(test3.first == nullptr);
        CHECK(test3.second == nullptr);
    }
}
