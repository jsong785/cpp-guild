#pragma once

#include <optional>
#include <type_traits>
#include <variant>

namespace details {
    struct StringTokenizerState {
        const std::string m_val;
        std::string::const_iterator m_iter;
    };

    auto GetTokenizerState(std::string val) {
        StringTokenizerState s{ .m_val = std::move(val) };
        s.m_iter = std::cbegin(s.m_val);
        return s;
    }
}

auto Tokenize(std::string val) {
    return[tok = details::GetTokenizerState(std::move(val))]() mutable {
        const auto start{ tok.m_iter };
        const auto foundSpace{ std::find_if(start, std::cend(tok.m_val), ::isspace) };

        const auto advanceToNextNonspaceChar{
            [&val = tok.m_val](const auto currentIter){
                if(currentIter != std::cend(val)) {
                    return std::find_if(currentIter , std::cend(val), [](const auto c){
                            return !::isspace(c);
                        }) ;
                }
                return currentIter;
            }
        };
        tok.m_iter = advanceToNextNonspaceChar(foundSpace);
        return std::string{ start, foundSpace };
    };
}

std::vector<std::string> GetTokens(std::string val) {
    std::vector<std::string> tokens;
    tokens.reserve(val.size());

    auto tok{ Tokenize(std::move(val)) };
    for(auto s{ tok() }; !s.empty(); s = tok()) {
        tokens.emplace_back(std::move(s));
    }
    return tokens;
}

enum class Operation { Add, Subtract, Multiply, Divide };
std::optional<Operation> GetOperator(const std::string& c) {
    if(c == "+") {
        return Operation::Add;
    }
    if(c == "-") {
        return Operation::Subtract;
    }
    if(c == "*") {
        return Operation::Multiply;
    }
    if(c == "/") {
        return Operation::Divide;
    }
    return {};
}

template <typename T>
using Data = std::variant<std::decay_t<T>, Operation>;

template <typename T>
using DataVector = std::vector<Data<T>>;

template <typename T>
DataVector<T> GetData(std::vector<std::string> tokens) {
    DataVector<T> data;
    data.reserve(tokens.size());

    std::transform(std::cbegin(tokens), std::cend(tokens), std::back_inserter(data), [](const auto& val) -> typename DataVector<T>::value_type {
        auto&& op{ GetOperator(val) };
        if(op) {
            return *op;
        }

        using DecayedType = std::decay_t<T>;
        if constexpr(std::is_integral_v<DecayedType>) {
            if constexpr(std::is_signed_v<DecayedType>) {
                return static_cast<DecayedType>(std::stoll(val));
            }
            else {
                return static_cast<DecayedType>(std::stoull(val));
            }
        }
        else if(std::is_floating_point_v<DecayedType>) {
            return static_cast<DecayedType>(std::stod(val));
        }
        else {
            return {};
        }
    });

    return data;
}

template <typename T>
auto DoOperation(const std::decay_t<T> a, const std::decay_t<T> b, const Operation op) {
    if(op == Operation::Add) {
        return a+b;
    }
    else if(op == Operation::Subtract) {
        return a-b;
    }
    else if(op == Operation::Multiply) {
        return a*b;
    }
    assert(op == Operation::Divide);
    return a/b;
}

template <typename T>
DataVector<T> Fold(DataVector<T>&& data, typename DataVector<T>::value_type&& val) {
    return std::visit(
            [data = std::move(data)](auto &&visitVal){
                using VisitValDecayed = std::decay_t<decltype(visitVal)>;
                using TDecayed = std::decay_t<T>;
                if constexpr(std::is_same_v<VisitValDecayed, TDecayed>) {
                    auto cpy{ std::move(data) };
                    cpy.emplace_back(std::move(visitVal));
                    return cpy;
                }
                else if(std::is_same_v<VisitValDecayed, Operation>){
                    assert(data.size() >= 2);
                    const auto a{ std::get<TDecayed>(*std::next(std::rbegin(data))) };
                    const auto b{ std::get<TDecayed>(*std::rbegin(data)) };

                    using DataListType = std::decay_t<decltype(data)>;
                    DataListType copy{ std::make_move_iterator(std::begin(data)), std::make_move_iterator(std::prev(std::end(data), 2)) };
                    copy.emplace_back(DoOperation<TDecayed>(a, b, visitVal));
                    return copy;
                }
                else {
                    return data;
                }
            }
        , val);
}

template <typename T, typename Iter, typename FoldFunc>
auto DoFastAccumulate(Iter begin, Iter end, T init, FoldFunc fold) {
    for(auto i{ begin }; i != end; ++i) {
        init = fold(std::move(init), std::move(*i));
    }
    return init;
}

template <typename A, typename B>
auto operator|(A&& a, B&& b) -> decltype(std::invoke(b, a)) {
    return std::invoke(std::forward<B>(b), std::forward<A>(a));
}

template <typename A, typename B>
auto operator|(A&& a, B&& b) -> decltype(std::invoke(b, std::begin(a), std::end(a))) {
    return std::invoke(std::forward<B>(b), std::begin(a), std::end(a));
}

template <typename List>
std::optional<typename List::value_type> GetFirstOnly(List l) {
    if(l.size() == 1) {
        return *std::cbegin(l);
    }
    return {};
}

template <typename T, typename D>
std::optional<T> Maybe(std::optional<D> d) {
    if(d) {
        return std::get<T>(*d);
    }
    return {};
}

template <typename T>
auto DoEquation(std::string operation) {
    const auto accumulate{ 
        [](auto&& a, auto&& b){
             return DoFastAccumulate(
                     std::forward<decltype(a)>(a),
                     std::forward<decltype(b)>(b),
                     DataVector<T>{},
                     Fold<T>
                 );
        }
    };
    return GetTokens(std::move(operation)) | 
        GetData<T> | 
        accumulate | 
        GetFirstOnly<DataVector<T>> | 
        Maybe<T, Data<T>>;
}

