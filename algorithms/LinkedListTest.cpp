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

    template <typename T>
    class SinglyLinkedListRaii {
        public:
            SinglyLinkedListRaii(const unsigned amt, const bool circular) :
                m_nodes{Create(amt, circular)} {}
            SinglyLinkedListRaii(const SinglyLinkedListRaii&) = delete;
            SinglyLinkedListRaii(SinglyLinkedListRaii&&) = delete;
            ~SinglyLinkedListRaii() = default;

            SinglyLinkedListRaii& operator=(const SinglyLinkedListRaii&) = delete;
            SinglyLinkedListRaii& operator=(SinglyLinkedListRaii&&) = delete;

            T* operator[](const unsigned n)
            { return &m_nodes[n]; }

        private:
            std::vector<T> Create(const unsigned amt, const bool circular);

            std::vector<T> m_nodes;
    };

    template <typename T>
    class DoublyLinkedListRaii {
        public:
            DoublyLinkedListRaii(const unsigned amt, const bool circular) :
                m_nodes{Create(amt, circular)} {}
            DoublyLinkedListRaii(const DoublyLinkedListRaii&) = delete;
            DoublyLinkedListRaii(DoublyLinkedListRaii&&) = delete;
            ~DoublyLinkedListRaii() = default;

            DoublyLinkedListRaii& operator=(const DoublyLinkedListRaii&) = delete;
            DoublyLinkedListRaii& operator=(DoublyLinkedListRaii&&) = delete;

            T* operator[](const unsigned n)
            { return &m_nodes[n]; }

        private:
            std::vector<T> Create(const unsigned amt, const bool circular);
            
            std::vector<T> m_nodes;
    };

    template <typename T>
    using SLR = SinglyLinkedListRaii<T>;

    template <typename T>
    using DLR = DoublyLinkedListRaii<T>;
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
        SLR<Singly> list{1, false};
        auto head{ list[0] };
        CHECK(ReverseSinglyLinkedListNonCircular(head) == head);
    }

    SECTION("two")
    {
        SLR<Singly> list{2, false};

        auto head = list[0];
        auto tail = list[1];
        CHECK(ReverseSinglyLinkedListNonCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == nullptr);
    }

    SECTION("three")
    {
        SLR<Singly> list{3, false};

        auto head = list[0];
        auto middle = list[1];
        auto tail = list[2];

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
        SLR<Singly> list{1, true};
        auto head{ list[0] };
        CHECK(ReverseSinglyLinkedListCircular(head) == head);
    }

    SECTION("two")
    {
        SLR<Singly> list{2, true};
        auto head{ list[0] };
        auto tail{ list[1] };

        CHECK(ReverseSinglyLinkedListCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == tail);
    }

    SECTION("three")
    {
        SLR<Singly> list{3, true};
        auto head{ list[0] };
        auto middle{ list[1] };
        auto tail{ list[2] };

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
        DLR<Doubly> list{1, false};
        auto head{ list[0] };
        CHECK(ReverseDoublyLinkedListNonCircular(head) == head);
    }

    SECTION("two")
    {
        DLR<Doubly> list{2, false};

        auto head{ list[0] };
        auto tail{ list[1] };
        CHECK(ReverseDoublyLinkedListNonCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == nullptr);

        CHECK(head->prev == tail);
        CHECK(tail->prev == nullptr);
    }

    SECTION("three")
    {
        DLR<Doubly> list{3, false};
        auto head{ list[0] };
        auto middle{ list[1] };
        auto tail{ list[2] };

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
        DLR<Doubly> list{1, true};
        auto head{ list[0] };

        CHECK(ReverseDoublyLinkedListCircular(head) == head);
        CHECK(head->next == head);
        CHECK(head->prev == head);
    }

    SECTION("two")
    {
        DLR<Doubly> list{2, true};
        auto head{ list[0] };
        auto tail{ list[1] };

        CHECK(ReverseDoublyLinkedListCircular(head) == tail);

        CHECK(tail->next == head);
        CHECK(head->next == tail);

        CHECK(head->prev == tail);
        CHECK(tail->prev == head);
    }

    SECTION("three")
    {
        DLR<Doubly> list{3, true};
        auto head{ list[0] };
        auto middle{ list[1] };
        auto tail{ list[2] };

        CHECK(ReverseDoublyLinkedListCircular(head) == tail);

        CHECK(tail->next == middle);
        CHECK(middle->next == head);
        CHECK(head->next == tail);

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
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 0).first ==  nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 1).first ==  nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(static_cast<Singly*>(nullptr), 2).first ==  nullptr);
    }

    SECTION("single")
    {
        SLR<Singly> list{1, false};
        auto head{ list[0] };
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 0).first == head);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 0).second == nullptr);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 1).first == nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 1).second == nullptr);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 2).first == nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 2).second == nullptr);
    }

    SECTION("two")
    {
        SLR<Singly> list{2, false};
        auto head{ list[0] };
        auto tail{ list[1] };

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 0).first == tail);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 0).second == head);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 1).first == head);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 1).second == nullptr);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 2).first == nullptr);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 2).second == nullptr);
    }

    SECTION("three")
    {
        SLR<Singly> list{3, false};
        auto head{ list[0] };
        auto middle{ list[1] };
        auto tail{ list[2] };

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 0).first == tail);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 0).second == middle);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 1).first == middle);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 1).second == head);

        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 2).first == head);
        CHECK(GetNFromEndSinglyLinkedListNonCircular(head, 2).second == nullptr);
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
            SLR<Singly> list{1, false};
            auto head{ list[0] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 0)};
            CHECK(result.first == nullptr);
            CHECK(result.second == head);
        }

        {
            SLR<Singly> list{1, false};
            auto head{ list[0] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 1)};
            CHECK(result.first == head);
            CHECK(result.second == nullptr);
        }

        {
            SLR<Singly> list{1, false};
            auto head{ list[0] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 2)};
            CHECK(result.first == head);
            CHECK(result.second == nullptr);
        }
    }

    SECTION("two")
    {
        {
            SLR<Singly> list{2, false};
            auto head{ list[0] };
            auto tail{ list[1] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 0)};
            CHECK(result.first == head);
            CHECK(result.second == tail);
        }

        {
            SLR<Singly> list{2, false};
            auto head{ list[0] };
            auto tail{ list[1] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 1)};
            CHECK(result.first == tail);
            CHECK(result.second == head);
        }

        {
            SLR<Singly> list{2, false};
            auto head{ list[0] };
            auto tail{ list[1] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 2)};
            CHECK(result.first == head);
            CHECK(result.second == nullptr);
        }
    }

    SECTION("three")
    {
        {
            SLR<Singly> list{3, false};
            auto head{ list[0] };
            auto middle{ list[1] };
            auto tail{ list[2] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 0)};
            CHECK(result.first == head);
            CHECK(result.second == tail);
        }

        {
            SLR<Singly> list{3, false};
            auto head{ list[0] };
            auto middle{ list[1] };
            auto tail{ list[2] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 1)};
            CHECK(result.first == head);
            CHECK(result.second == middle);
        }

        {
            SLR<Singly> list{3, false};
            auto head{ list[0] };
            auto middle{ list[1] };
            auto tail{ list[2] };

            const auto result{ DeleteNFromEndSinglyLinkedListNonCircular(head, 2)};
            CHECK(result.first == middle);
            CHECK(result.second == head);
        }
    }
}

// slow is ok for these unit tests
template <typename T>
std::vector<T> SinglyLinkedListRaii<T>::Create(const unsigned amt, const bool circular) {
    std::vector<T> nodes(amt);
    nodes.resize(amt);

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

template <typename T>
std::vector<T> DoublyLinkedListRaii<T>::Create(const unsigned amt, const bool circular) {
    std::vector<T> nodes(amt);
    nodes.resize(amt);

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
