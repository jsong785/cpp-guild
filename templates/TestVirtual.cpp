#include "catch.hpp"

class A {
    public:
        virtual int GetInteger() const {
            return 1;
        }
};

template <typename T>
class B : public A {
    public:
        int GetInteger() const override {
            return 2;
        }
};

class C : public B<int> {
    public:
        int GetInteger() const final {
            return 3;
        }

        template <typename T>
        class Inner {
            int Whatever() const {
                return 1;
            }
        };
};

TEST_CASE("Inhibit virtual", "[virtual]")
{
    C c{};
    const A& vVar{ c };

    CHECK(vVar.GetInteger() == 3);
    CHECK(vVar.A::GetInteger() == 1);
}

