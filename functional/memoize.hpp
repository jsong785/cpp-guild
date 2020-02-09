#include <map>
#include <tuple>

// got this from Functional Programming in C++, this version handles lambdas however :)
// PS: Does not work well with recursive functions, there are better optimizations to be had for that scenario.

template <typename Signature, typename Func>
class MemoizeHelper {};

template <typename Result, typename ...Args, typename Func>
class MemoizeHelper<Result(Args...), Func>
{
    public:
        MemoizeHelper(Func &&func)
            : m_func{ std::forward<Func>(func) }
        {}

        Result operator()(Args... args)
        {
            auto argsTuple{ std::make_tuple(args...) };
            const auto found{ m_cache.find(argsTuple) };
            if(found != m_cache.end()) {
                return found->second;
            }
            return m_cache.insert(std::make_pair(std::move(argsTuple), m_func(args...))).first->second;
        }

    private:
        Func &&m_func;
        std::map<std::tuple<Args...>, Result> m_cache;
};

template <typename Signature, typename Func>
static auto make_memoized(Func &&func) {
    return MemoizeHelper<Signature, Func>{ std::forward<Func>(func) };
}

template <typename Result, typename ...Args>
static auto make_memoized(Result(*func)(Args...)) {
    return MemoizeHelper<Result(Args...), decltype(func)>{ func };
}
