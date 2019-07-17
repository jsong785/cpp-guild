#include "catch.hpp"
#include "LinkedList.hpp"
#include <vector>

namespace {
    struct Singly {
        Singly *next{ nullptr };
    };

    struct Doubly {
        Doubly *next{ nullptr };
        Doubly *prev{ nullptr };
    };

    // slow is ok for these unit tests
    template <typename T, unsigned N>
    std::vector<T> CreateSinglyLinkedList(const bool circular) {
        std::vector<T> nodes;
        nodes.resize(N);

        for(auto iter{ nodes.begin() }; iter != nodes.end(); ++iter) {
            T* next{ nullptr };

            auto nextIter{ std::next(iter) };
            if(nextIter != nodes.end()) {
                next = &*nextIter;
            }

            iter->next = next;
        }

        if(circular) {
            nodes.rbegin()->next = &*nodes.begin();
        }

        return nodes;
    }


    template <typename T, unsigned N>
    std::vector<T> CreateDoublyLinkedList(const bool circular) {
        std::vector<T> nodes;
        nodes.resize(N);

        for(auto iter{ nodes.begin() }; iter != nodes.end(); ++iter) {
            T* next{ nullptr };

            auto nextIter{ std::next(iter) };
            if(nextIter != nodes.end()) {
                next = &*nextIter;
            }

            iter->next = next;

            T* prev{ nullptr };
            if(iter != nodes.begin()) {
                prev = &*std::prev(iter);
            }
            iter->prev = prev;
        }

        if(circular) {
            nodes.rbegin()->next = &*nodes.begin();
            nodes.begin()->prev = &*nodes.rbegin();
        }

        return nodes;
    }

    template <typename T, unsigned N>
    const auto SLR{  CreateSinglyLinkedList<T, N> };

    template <typename T, unsigned N>
    const auto DLR{  CreateDoublyLinkedList<T, N> };
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
        auto list { SLR<Singly, 1>(false) };
        auto head{ &list[0] };
        CHECK(ReverseSinglyLinkedListNonCircular(head) == head);
    }

    SECTION("two")
    {
        auto list{ SLR<Singly, 2>(false) };

        auto head{ &list[0] };
        auto tail{ &list[1] };

        CHECK(ReverseSinglyLinkedListNonCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == nullptr);
    }

    SECTION("three")
    {
        auto list{ SLR<Singly, 3>(false) };

        auto head = &list[0];
        auto middle = &list[1];
        auto tail = &list[2];

        CHECK(ReverseSinglyLinkedListNonCircular(head) == tail);

        CHECK(tail->next == middle);
        CHECK(middle->next == head);
        CHECK(head->next == nullptr);
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
        auto list{ SLR<Singly, 1>(true) };
        auto head{ &list[0] };
        CHECK(ReverseSinglyLinkedListCircular(head) == head);
    }

    SECTION("two")
    {
        auto list{ SLR<Singly, 2>(true) };
        auto head{ &list[0] };
        auto tail{ &list[1] };

        CHECK(ReverseSinglyLinkedListCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == tail);
    }

    SECTION("three")
    {
        auto list{ SLR<Singly, 3>(true) };
        auto head{ &list[0] };
        auto middle{ &list[1] };
        auto tail{ &list[2] };

        CHECK(ReverseSinglyLinkedListCircular(head) == tail);

        CHECK(tail->next == middle);
        CHECK(middle->next == head);
        CHECK(head->next == tail);
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
        auto list{ DLR<Doubly, 1>(false) };
        auto head{ &list[0] };
        CHECK(ReverseDoublyLinkedListNonCircular(head) == head);
    }

    SECTION("two")
    {
        auto list{ DLR<Doubly, 2>(false) };
        auto head{ &list[0] };
        auto tail{ &list[1] };
        CHECK(ReverseDoublyLinkedListNonCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == nullptr);

        CHECK(head->prev == tail);
        CHECK(tail->prev == nullptr);
    }

    SECTION("three")
    {
        auto list{ DLR<Doubly, 3>(false) };
        auto head{ &list[0] };
        auto middle{ &list[1] };
        auto tail{ &list[2] };

        CHECK(ReverseDoublyLinkedListNonCircular(head) == tail);

        CHECK(tail->next == middle);
        CHECK(middle->next == head);
        CHECK(head->next == nullptr);

        CHECK(head->prev == middle);
        CHECK(middle->prev == tail);
        CHECK(tail->prev == nullptr);
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
        auto list{ DLR<Doubly, 1>(true) };
        auto head{ &list[0] };

        CHECK(ReverseDoublyLinkedListCircular(head) == head);
        CHECK(head->next == head);
        CHECK(head->prev == head);
    }

    SECTION("two")
    {
        auto list{ DLR<Doubly, 2>(true) };
        auto head{ &list[0] };
        auto tail{ &list[1] };

        CHECK(ReverseDoublyLinkedListCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == tail);

        CHECK(head->prev == tail);
        CHECK(tail->prev == head);
    }

    SECTION("three")
    {
        auto list{ DLR<Doubly, 3>(true) };
        auto head{ &list[0] };
        auto middle{ &list[1] };
        auto tail{ &list[2] };

        CHECK(ReverseDoublyLinkedListCircular(head) == tail);

        CHECK(tail->next == middle);
        CHECK(middle->next == head); CHECK(head->next == tail);

        CHECK(head->prev == middle);
        CHECK(middle->prev == tail);
        CHECK(tail->prev == head);
    }
}

TEST_CASE("Return N from end Singly Linked (non-circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 0) ==  nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 1) ==  nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 2) ==  nullptr);
    }

    SECTION("single")
    {
        auto list{ SLR<Singly, 1>(false) };
        auto head{ &list[0] };

        Singly* parent{ nullptr };
        auto node = GetNFromEndSinglyLinkedListNonCircular(head, 0, &parent);
        CHECK(node == head);
        CHECK(parent == nullptr);

        node = GetNFromEndSinglyLinkedListNonCircular(head, 1, &parent);
        CHECK(node == nullptr);
        CHECK(parent == nullptr);

        node = GetNFromEndSinglyLinkedListNonCircular(head, 2, &parent);
        CHECK(node == nullptr);
        CHECK(parent == nullptr);
    }

    SECTION("two")
    {
        auto list{ SLR<Singly, 2>(false) };
        auto head{ &list[0] };
        auto tail{ &list[1] };

        Singly* parent{ nullptr };
        auto node = GetNFromEndSinglyLinkedListNonCircular(head, 0, &parent);
        CHECK(node == tail);
        CHECK(parent == head);

        node = GetNFromEndSinglyLinkedListNonCircular(head, 1, &parent);
        CHECK(node == head);
        CHECK(parent == nullptr);

        node = GetNFromEndSinglyLinkedListNonCircular(head, 2, &parent);
        CHECK(node == nullptr);
        CHECK(parent == nullptr);
    }

    SECTION("three")
    {
        auto list{ SLR<Singly, 3>(false) };
        auto head{ &list[0] };
        auto middle{ &list[1] };
        auto tail{ &list[2] };

        Singly* parent{ nullptr };
        auto node = GetNFromEndSinglyLinkedListNonCircular(head, 0, &parent);
        CHECK(node == tail);
        CHECK(parent == middle);

        node = GetNFromEndSinglyLinkedListNonCircular(head, 1, &parent);
        CHECK(node == middle);
        CHECK(parent == head);

        node = GetNFromEndSinglyLinkedListNonCircular(head, 2, &parent);
        CHECK(node == head);
        CHECK(parent == nullptr);
    }
}

TEST_CASE("Delete N from end Singly Linked (non-circular)", "[LinkedList]")
{
    using namespace LinkedList;
    SECTION("empty")
    {
        Singly *toDelete{ nullptr };
        CHECK(DeleteNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 0, &toDelete) == nullptr);
        CHECK(toDelete == nullptr);

        CHECK(DeleteNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 1, &toDelete) == nullptr);
        CHECK(toDelete == nullptr);

        CHECK(DeleteNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 2, &toDelete) == nullptr);
        CHECK(toDelete == nullptr);
    }

    SECTION("single")
    {
        {
            auto list{ SLR<Singly, 1>(false) };
            auto head{ &list[0] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 0, &toDelete);
            CHECK(node == nullptr);
            CHECK(toDelete == head);
        }

        {
            auto list{ SLR<Singly, 1>(false) };
            auto head{ &list[0] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 1, &toDelete);
            CHECK(node == head);
            CHECK(toDelete == nullptr);
        }

        {
            auto list{ SLR<Singly, 1>(false) };
            auto head{ &list[0] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 2, &toDelete);
            CHECK(node == head);
            CHECK(toDelete == nullptr);
        }
    }

    SECTION("two")
    {
        {
            auto list{ SLR<Singly, 2>(false) };
            auto head{ &list[0] };
            auto tail{ &list[1] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 0, &toDelete);
            CHECK(node == head);
            CHECK(toDelete == tail);
        }

        {
            auto list{ SLR<Singly, 2>(false) };
            auto head{ &list[0] };
            auto tail{ &list[1] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 1, &toDelete);
            CHECK(node == tail);
            CHECK(toDelete == head);
        }

        {
            auto list{ SLR<Singly, 2>(false) };
            auto head{ &list[0] };
            auto tail{ &list[1] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 2, &toDelete);
            CHECK(node == head);
            CHECK(toDelete == nullptr);
        }
    }

    SECTION("three")
    {
        {
            auto list{ SLR<Singly, 3>(false) };
            auto head{ &list[0] };
            auto middle{ &list[1] };
            auto tail{ &list[2] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 0, &toDelete);
            CHECK(node == head);
            CHECK(toDelete == tail);
        }

        {
            auto list{ SLR<Singly, 3>(false) };
            auto head{ &list[0] };
            auto middle{ &list[1] };
            auto tail{ &list[2] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 1, &toDelete);
            CHECK(node == head);
            CHECK(toDelete == middle);
        }

        {
            auto list{ SLR<Singly, 3>(false) };
            auto head{ &list[0] };
            auto middle{ &list[1] };
            auto tail{ &list[2] };

            Singly *toDelete{ nullptr };
            const auto node = DeleteNFromEndSinglyLinkedListNonCircular(head, 2, &toDelete);
            CHECK(node == middle);
            CHECK(toDelete == head);
        }
    }
}
