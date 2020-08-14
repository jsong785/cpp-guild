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

// initialization (enum only)
static_assert(Flags<Test>{Test::A, Test::B} == Flags<Test>{}.Set(Test::A, Test::B));
static_assert(Flags<Test>{Test::A, Test::B} != Flags<Test>{}.Set(Test::A));
static_assert(Flags<Test>{Test::A, Test::B, Test::C, Test::D} == Flags<Test>{}.Set(Test::ALL));

// initialization (flags only)
static_assert(Flags<Test>{Flags<Test>{Test::A}, Flags<Test>{Test::B}} == Flags<Test>{}.Set(Test::A, Test::B));
static_assert(Flags<Test>{Flags<Test>{Test::A}, Flags<Test>{Test::B}} != Flags<Test>{}.Set(Test::A));
static_assert(Flags<Test>{Flags<Test>{Test::A}, Flags<Test>{Test::B}, Flags<Test>{Test::C}, Flags<Test>{Test::D}} == Flags<Test>{}.Set(Test::ALL));

// initialization (mixed)
static_assert(Flags<Test>{Flags<Test>{Test::A}, Test::B} == Flags<Test>{}.Set(Test::A, Test::B));
static_assert(Flags<Test>{Test::A, Flags<Test>{Test::B}} != Flags<Test>{}.Set(Test::A));
static_assert(Flags<Test>{Flags<Test>{Test::A}, Test::B, Flags<Test>{Test::C}, Flags<Test>{Test::D}} == Flags<Test>{}.Set(Test::ALL));

// Test
static_assert(Flags<Test>{Test::A, Test::B}.Test(Test::A));
static_assert(!Flags<Test>{Test::A, Test::B}.Test(Test::C));
static_assert(!Flags<Test>{Test::A, Test::B}.Test(Test::ALL));
static_assert(Flags<Test>{Test::ALL}.Test(Test::ALL));
static_assert(Flags<Test>{Test::ALL}.Test(Test::C));

// Set (enum only)
static_assert(Flags<Test>{Test::A}.Set(Test::A) == Flags<Test>{Test::A});
static_assert(Flags<Test>{}.Set(Test::A, Test::B) == Flags<Test>{Test::A, Test::B});
static_assert(Flags<Test>{}.Set(Test::ZERO) == Flags<Test>{Test::ZERO});
static_assert(Flags<Test>{}.Set(Test::A).Set(Test::B, Test::C, Test::D) == Flags<Test>{Test::ALL});

// Set (flags only)
static_assert(Flags<Test>{Test::A}.Set(Flags<Test>{Test::A}) == Flags<Test>{Test::A});
static_assert(Flags<Test>{}.Set(Flags<Test>{Test::A, Test::B}) == Flags<Test>{Test::A, Test::B});
static_assert(Flags<Test>{}.Set(Flags<Test>{Test::ZERO}) == Flags<Test>{Test::ZERO});
static_assert(Flags<Test>{}.Set(Flags<Test>{Test::A}).Set(Flags<Test>{Test::B, Test::C, Test::D}) == Flags<Test>{Test::ALL});

// Set (mixed)
static_assert(Flags<Test>{}.Set(Flags<Test>{Test::A}).Set(Test::B).Set(Flags<Test>{Test::C, Test::D}) == Flags<Test>{Test::ALL});

// Unset (enum only)
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A) == Flags<Test>{Test::B});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A, Test::B) == Flags<Test>{});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A, Test::B) == Flags<Test>{Test::ZERO});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::ALL) == Flags<Test>{});

// Unset (Flags only)
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Flags<Test>{Test::A}) == Flags<Test>{Test::B});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Flags<Test>{Test::A, Test::B}) == Flags<Test>{});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Flags<Test>{Test::A, Test::B}) == Flags<Test>{Test::ZERO});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Flags<Test>{Test::ALL}) == Flags<Test>{});

// Unset (mixed)
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Flags<Test>{Test::A}, Test::B) == Flags<Test>{Test::ZERO});
static_assert(Flags<Test>{Test::A, Test::B}.Unset(Test::A, Flags<Test>{Test::B}) == Flags<Test>{Test::ZERO});

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
