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

TEST_CASE("Singly Linked (non-circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(ReverseSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr)) ==  nullptr);
    }

    SECTION("single")
    {
        Singly head;
        CHECK(ReverseSinglyLinkedListNonCircular(&head) == &head);
    }

    SECTION("two")
    {
        Singly head;
        Singly tail;

        head.next = &tail;
        CHECK(ReverseSinglyLinkedListNonCircular(&head) == &tail);

        CHECK(tail.next == &head);
        CHECK(head.next == nullptr);
    }

    SECTION("three")
    {
        Singly head;
        Singly middle;
        Singly tail;

        head.next = &middle;
        middle.next = &tail;

        CHECK(ReverseSinglyLinkedListNonCircular(&head) == &tail);

        CHECK(tail.next == &middle);
        CHECK(middle.next == &head);
        CHECK(head.next == nullptr);
    }
}

TEST_CASE("Singly Linked (circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(ReverseSinglyLinkedListCircular(static_cast<Singly*>(nullptr)) ==  nullptr);
    }

    SECTION("single")
    {
        Singly head;
        head.next = &head;
        CHECK(ReverseSinglyLinkedListCircular(&head) == &head);
    }

    SECTION("two")
    {
        Singly head;
        Singly tail;

        head.next = &tail;
        tail.next = &head;
        CHECK(ReverseSinglyLinkedListCircular(&head) == &tail);

        CHECK(tail.next == &head);
        CHECK(head.next == &tail);
    }

    SECTION("three")
    {
        Singly head;
        Singly middle;
        Singly tail;

        head.next = &middle;
        middle.next = &tail;
        tail.next = &head;

        CHECK(ReverseSinglyLinkedListCircular(&head) == &tail);

        CHECK(tail.next == &middle);
        CHECK(middle.next == &head);
        CHECK(head.next == &tail);
    }
}

TEST_CASE("Doubly Linked (non-circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(ReverseDoublyLinkedListNonCircular(static_cast<Doubly*>(nullptr)) ==  nullptr);
    }

    SECTION("single")
    {
        Doubly head;
        CHECK(ReverseDoublyLinkedListNonCircular(&head) == &head);
    }

    SECTION("two")
    {
        Doubly head;
        Doubly tail;

        head.next = &tail;
        tail.prev = &head;
        CHECK(ReverseDoublyLinkedListNonCircular(&head) == &tail);

        CHECK(tail.next == &head);
        CHECK(head.next == nullptr);

        CHECK(head.prev == &tail);
        CHECK(tail.prev == nullptr);
    }

    SECTION("three")
    {
        Doubly head;
        Doubly middle;
        Doubly tail;

        head.next = &middle;
        middle.next = &tail;

        tail.prev = &middle;
        middle.prev = &head;
        CHECK(ReverseDoublyLinkedListNonCircular(&head) == &tail);

        CHECK(tail.next == &middle);
        CHECK(middle.next == &head);
        CHECK(head.next == nullptr);

        CHECK(head.prev == &middle);
        CHECK(middle.prev == &tail);
        CHECK(tail.prev == nullptr);
    }
}

TEST_CASE("Doubly Linked (circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(ReverseDoublyLinkedListCircular(static_cast<Doubly*>(nullptr)) ==  nullptr);
    }

    SECTION("single")
    {
        Doubly head;
        head.next = &head;
        head.prev = &head;

        CHECK(ReverseDoublyLinkedListCircular(&head) == &head);
        CHECK(head.next == &head);
        CHECK(head.prev == &head);
    }

    SECTION("two")
    {
        Doubly head;
        Doubly tail;

        head.next = &tail;
        tail.next = &head;

        tail.prev = &head;
        head.prev = &tail;
        CHECK(ReverseDoublyLinkedListCircular(&head) == &tail);

        CHECK(tail.next == &head);
        CHECK(head.next == &tail);

        CHECK(head.prev == &tail);
        CHECK(tail.prev == &head);
    }

    SECTION("three")
    {
        Doubly head;
        Doubly middle;
        Doubly tail;

        head.next = &middle;
        middle.next = &tail;
        tail.next = &head;

        tail.prev = &middle;
        middle.prev = &head;
        head.prev = &tail;
        CHECK(ReverseDoublyLinkedListCircular(&head) == &tail);

        CHECK(tail.next == &middle);
        CHECK(middle.next == &head);
        CHECK(head.next == &tail);

        CHECK(head.prev == &middle);
        CHECK(middle.prev == &tail);
        CHECK(tail.prev == &head);
    }
}

TEST_CASE("Return N from end Singly Linked (non-circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 0).first ==  nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 1).first ==  nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 2).first ==  nullptr);
    }

    SECTION("single")
    {
        Singly head;
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 0).first == &head);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 0).second == nullptr);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 1).first == nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 1).second == nullptr);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 2).first == nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 2).second == nullptr);
    }

    SECTION("two")
    {
        Singly head;
        Singly tail;

        head.next = &tail;
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 0).first == &tail);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 0).second == &head);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 1).first == &head);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 1).second == nullptr);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 2).first == nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 2).second == nullptr);
    }

    SECTION("three")
    {
        Singly head;
        Singly middle;
        Singly tail;

        head.next = &middle;
        middle.next = &tail;
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 0).first == &tail);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 0).second == &middle);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 1).first == &middle);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 1).second == &head);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 2).first == &head);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(&head, 2).second == nullptr);
    }
}

TEST_CASE("Delete N from end Singly Linked (non-circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(DeleteNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 0).first == nullptr);
        CHECK(DeleteNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 1).first == nullptr);
        CHECK(DeleteNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 2).first == nullptr);
    }

    SECTION("single")
    {
        {
            Singly head;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 0)};
            CHECK(result.first == nullptr);
            CHECK(result.second == &head);
        }

        {
            Singly head;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 1)};
            CHECK(result.first == &head);
            CHECK(result.second == nullptr);
        }

        {
            Singly head;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 2)};
            CHECK(result.first == &head);
            CHECK(result.second == nullptr);
        }
    }

    SECTION("two")
    {
        {
            Singly head;
            Singly tail;
            head.next = &tail;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 0)};
            CHECK(result.first == &head);
            CHECK(result.second == &tail);
        }

        {
            Singly head;
            Singly tail;
            head.next = &tail;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 1)};
            CHECK(result.first == &tail);
            CHECK(result.second == &head);
        }

        {
            Singly head;
            Singly tail;
            head.next = &tail;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 2)};
            CHECK(result.first == &head);
            CHECK(result.second == nullptr);
        }
    }

    SECTION("three")
    {
        {
            Singly head;
            Singly middle;
            Singly tail;

            head.next = &middle;
            middle.next = &tail;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 0)};
            CHECK(result.first == &head);
            CHECK(result.second == &tail);
        }

        {
            Singly head;
            Singly middle;
            Singly tail;

            head.next = &middle;
            middle.next = &tail;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 1)};
            CHECK(result.first == &head);
            CHECK(result.second == &middle);
        }

        {
            Singly head;
            Singly middle;
            Singly tail;

            head.next = &middle;
            middle.next = &tail;

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(&head, 2)};
            CHECK(result.first == &middle);
            CHECK(result.second == &head);
        }
    }
}
