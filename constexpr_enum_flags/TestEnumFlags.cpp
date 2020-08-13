#include "enum_flags.hpp"

enum class Test
{
    ZERO = 0,
    A = 1 << 0,
    B = 1 << 1,
    C = 1 << 2,
    D = 1 << 3,
    ALL = 0xF
};

// initialization
static_assert(Flags<Test>{Test::A, Test::B} == Flags<Test>{}.Set(Test::A, Test::B));
static_assert(Flags<Test>{Test::A, Test::B} != Flags<Test>{}.Set(Test::A));
static_assert(Flags<Test>{Test::A, Test::B, Test::C, Test::D} == Flags<Test>{}.Set(Test::ALL));

// Test
static_assert(Flags<Test>{Test::A, Test::B}.Test(Test::A));
static_assert(!Flags<Test>{Test::A, Test::B}.Test(Test::C));
static_assert(!Flags<Test>{Test::A, Test::B}.Test(Test::ALL));
static_assert(Flags<Test>{Test::ALL}.Test(Test::ALL));
static_assert(Flags<Test>{Test::ALL}.Test(Test::C));

// Unset
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A) == Flags<Test>{Test::B});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A, Test::B) == Flags<Test>{});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A, Test::B) == Flags<Test>{Test::ZERO});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::ALL) == Flags<Test>{});

// Flip
static_assert(Flags<Test>{Test::A, Test::B}.Flip() != Flags<Test>{Test::A, Test::B});
static_assert(!Flags<Test>{Test::A, Test::B}.Flip().Test(Test::A));
static_assert(!Flags<Test>{Test::A, Test::B}.Flip().Test(Test::B));
static_assert(Flags<Test>{Test::A, Test::B}.Flip().Test(Test::C));

static_assert(Flags<Test>{Test::A, Test::B}.Flip().Flip() == Flags<Test>{Test::A, Test::B});
static_assert(Flags<Test>{Test::A, Test::B}.Flip().Flip().Test(Test::A));
static_assert(Flags<Test>{Test::A, Test::B}.Flip().Flip().Test(Test::B));
static_assert(!Flags<Test>{Test::A, Test::B}.Flip().Flip().Test(Test::C));

int main(const int, const char**)
{
    return 0;
}
