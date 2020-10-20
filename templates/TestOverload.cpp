#include <type_traits>
#include <string>
#include <utility>

enum class Type
{
    move,
    other
};

template <typename Func, typename, typename = std::void_t<>>
struct DoSomething
{
    constexpr auto operator()(Func) const noexcept
    {
        return Type::move;
    }
};

template <typename Func, typename T>
struct DoSomething<Func, T, std::result_of_t<Func(std::add_const_t<std::add_lvalue_reference_t<T>>)>>
{
    constexpr auto operator()(Func) const noexcept
    {
        return Type::other;
    }
};

template <typename T>
class Test
{
    public:
        template <typename Func>
        constexpr auto Do(Func f) {
            return DoSomething<Func, T>{}(std::move(f));
        }
};

static_assert(Test<int>{}.Do([](const int&){}) == Type::other);
static_assert(Test<int>{}.Do([](const int){}) == Type::other);
static_assert(Test<int>{}.Do([](int&&){}) == Type::move);

