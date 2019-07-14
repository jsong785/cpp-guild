#include "catch.hpp"
#include "LinkedList.hpp"

namespace {
    struct Singly {
        Singly *next{ nullptr };
    };

    struct Doubly {
        Doubly *next{ nullptr };
        Doubly *prev{ nullptr };
    };
}

TEST_CASE("Singly Linked", "[LinkedList]")
{
    using namespace LinkedList;
}

TEST_CASE("Doubly Linked", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(ReverseDoublyLinkedList(static_cast<Doubly*>(nullptr)) ==  nullptr);
    }

    SECTION("single")
    {
        Doubly head;
        CHECK(ReverseDoublyLinkedList(&head) == &head);
    }

    SECTION("two")
    {
        Doubly head;
        Doubly tail;

        head.next = &tail;
        tail.prev = &head;
        CHECK(ReverseDoublyLinkedList(&head) == &tail);

        CHECK(tail.next == &head);
        CHECK(head.next == nullptr);

        CHECK(head.prev == &tail);
        CHECK(tail.prev == nullptr);
    }
}
