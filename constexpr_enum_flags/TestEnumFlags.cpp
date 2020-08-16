#include "enum_flags.hpp"
#include <cstdint>

template <typename T>
void TestInitialization()
{
    // initialization (enum only)
    static_assert(Flags<T>{T::A, T::B} == Flags<T>{}.Set(T::A, T::B));
    static_assert(Flags<T>{T::A, T::B} != Flags<T>{}.Set(T::A));
    static_assert(Flags<T>{T::A, T::B, T::C, T::D} == Flags<T>{}.Set(T::ALL));

    // initialization (flags only)
    static_assert(Flags<T>{Flags<T>{T::A}, Flags<T>{T::B}} == Flags<T>{}.Set(T::A, T::B));
    static_assert(Flags<T>{Flags<T>{T::A}, Flags<T>{T::B}} != Flags<T>{}.Set(T::A));
    static_assert(Flags<T>{Flags<T>{T::A}, Flags<T>{T::B}, Flags<T>{T::C}, Flags<T>{T::D}} == Flags<T>{}.Set(T::ALL));

    // initialization (mixed)
    static_assert(Flags<T>{Flags<T>{T::A}, T::B} == Flags<T>{}.Set(T::A, T::B));
    static_assert(Flags<T>{T::A, Flags<T>{T::B}} != Flags<T>{}.Set(T::A));
    static_assert(Flags<T>{Flags<T>{T::A}, T::B, Flags<T>{T::C}, Flags<T>{T::D}} == Flags<T>{}.Set(T::ALL));
}

template <typename T>
void TestTest()
{
    // Test (enum only)
    static_assert(Flags<T>{T::A, T::B}.Test(T::A));
    static_assert(!Flags<T>{T::A, T::B}.Test(T::C));
    static_assert(!Flags<T>{T::A, T::B}.Test(T::ALL));
    static_assert(Flags<T>{T::ALL}.Test(T::ALL));
    static_assert(Flags<T>{T::ALL}.Test(T::C));

    // Test (flags only)
    static_assert(Flags<T>{T::A, T::B}.Test(Flags<T>{T::A}));
    static_assert(!Flags<T>{T::A, T::B}.Test(Flags<T>{T::C}));
    static_assert(!Flags<T>{T::A, T::B}.Test(Flags<T>{T::ALL}));
    static_assert(Flags<T>{T::ALL}.Test(Flags<T>{T::ALL}));
    static_assert(Flags<T>{T::ALL}.Test(Flags<T>{T::C}));
}

template <typename T>
void TestSet()
{
    // Set (enum only)
    static_assert(Flags<T>{T::A}.Set(T::A) == Flags<T>{T::A});
    static_assert(Flags<T>{}.Set(T::A, T::B) == Flags<T>{T::A, T::B});
    static_assert(Flags<T>{}.Set(T::ZERO) == Flags<T>{T::ZERO});
    static_assert(Flags<T>{}.Set(T::A).Set(T::B, T::C, T::D) == Flags<T>{T::ALL});

    // Set (flags only)
    static_assert(Flags<T>{T::A}.Set(Flags<T>{T::A}) == Flags<T>{T::A});
    static_assert(Flags<T>{}.Set(Flags<T>{T::A, T::B}) == Flags<T>{T::A, T::B});
    static_assert(Flags<T>{}.Set(Flags<T>{T::ZERO}) == Flags<T>{T::ZERO});
    static_assert(Flags<T>{}.Set(Flags<T>{T::A}).Set(Flags<T>{T::B, T::C, T::D}) == Flags<T>{T::ALL});

    // Set (mixed)
    static_assert(Flags<T>{}.Set(Flags<T>{T::A}).Set(T::B).Set(Flags<T>{T::C, T::D}) == Flags<T>{T::ALL});
}

template <typename T>
void TestUnset()
{
    // Unset (enum only)
    static_assert(Flags<T>{T::A, T::B}.Unset(T::A) == Flags<T>{T::B});
    static_assert(Flags<T>{T::A, T::B}.Unset(T::A, T::B) == Flags<T>{});
    static_assert(Flags<T>{T::A, T::B}.Unset(T::A, T::B) == Flags<T>{T::ZERO});
    static_assert(Flags<T>{T::A, T::B}.Unset(T::ALL) == Flags<T>{});

    // Unset (Flags only)
    static_assert(Flags<T>{T::A, T::B}.Unset(Flags<T>{T::A}) == Flags<T>{T::B});
    static_assert(Flags<T>{T::A, T::B}.Unset(Flags<T>{T::A, T::B}) == Flags<T>{});
    static_assert(Flags<T>{T::A, T::B}.Unset(Flags<T>{T::A, T::B}) == Flags<T>{T::ZERO});
    static_assert(Flags<T>{T::A, T::B}.Unset(Flags<T>{T::ALL}) == Flags<T>{});

    // Unset (mixed)
    static_assert(Flags<T>{T::A, T::B}.Unset(Flags<T>{T::A}, T::B) == Flags<T>{T::ZERO});
    static_assert(Flags<T>{T::A, T::B}.Unset(T::A, Flags<T>{T::B}) == Flags<T>{T::ZERO});
}

template <typename T>
void TestFlip()
{
    // Flip
    static_assert(Flags<T>{T::A, T::B}.Flip() != Flags<T>{T::A, T::B});
    static_assert(!Flags<T>{T::A, T::B}.Flip().Test(T::A));
    static_assert(!Flags<T>{T::A, T::B}.Flip().Test(T::B));
    static_assert(Flags<T>{T::A, T::B}.Flip().Test(T::C));

    static_assert(Flags<T>{T::A, T::B}.Flip().Flip() == Flags<T>{T::A, T::B});
    static_assert(Flags<T>{T::A, T::B}.Flip().Flip().Test(T::A));
    static_assert(Flags<T>{T::A, T::B}.Flip().Flip().Test(T::B));
    static_assert(!Flags<T>{T::A, T::B}.Flip().Flip().Test(T::C));
}

template <typename T>
void TestOperators()
{
    // operator&
    static_assert((Flags<T>{T::A, T::B} & Flags<T>{T::A, T::B}) == Flags<T>{T::A, T::B});
    static_assert((Flags<T>{T::A} & Flags<T>{T::A, T::B}) == Flags<T>{T::A});
    static_assert((Flags<T>{T::A} & Flags<T>{T::B}) == Flags<T>{});

    // operator |
    static_assert((Flags<T>{T::A, T::B} | Flags<T>{T::A, T::B}) == Flags<T>{T::A, T::B});
    static_assert((Flags<T>{T::A} | Flags<T>{T::A, T::B}) == Flags<T>{T::A, T::B});
    static_assert((Flags<T>{T::A} | Flags<T>{T::B}) == Flags<T>{T::A, T::B});

    // operator ^
    static_assert((Flags<T>{T::A, T::B} ^ Flags<T>{T::A, T::B}) == Flags<T>{});
    static_assert((Flags<T>{T::A} ^ Flags<T>{T::A, T::B}) == Flags<T>{T::B});
    static_assert((Flags<T>{T::A} ^ Flags<T>{T::B}) == Flags<T>{T::A, T::B});
}

inline static void ConstexprTests() {
    enum class TestRegular
    {
        ZERO = 0,
        A = 1 << 0,
        B = 1 << 1,
        C = 1 << 2,
        D = 1 << 3,
        ALL = 0xF
    };

    enum class TestInt8 : int8_t {
        ZERO = 0,
        A = 1 << 0,
        B = 1 << 1,
        C = 1 << 2,
        D = 1 << 3,
        ALL = 0xF
    };

    enum class TestUint8 : uint8_t {
        ZERO = 0,
        A = 1 << 0,
        B = 1 << 1,
        C = 1 << 2,
        D = 1 << 3,
        ALL = 0xF
    };

    TestInitialization<TestRegular>();
    TestTest<TestRegular>();
    TestSet<TestRegular>();
    TestUnset<TestRegular>();
    TestFlip<TestRegular>();
    TestOperators<TestRegular>();

    TestInitialization<TestInt8>();
    TestTest<TestInt8>();
    TestSet<TestInt8>();
    TestUnset<TestInt8>();
    TestFlip<TestInt8>();
    TestOperators<TestInt8>();

    TestInitialization<TestUint8>();
    TestTest<TestUint8>();
    TestSet<TestUint8>();
    TestUnset<TestUint8>();
    TestFlip<TestUint8>();
    TestOperators<TestUint8>();
}


int main(const int, const char**)
{
    return 0;
}
