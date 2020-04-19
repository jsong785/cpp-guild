#pragma once

#include <cctype>
#include <cstring>
#include <optional>
#include <type_traits>
#include <variant>

auto Tokenize(std::string val) {
    return [val = std::move(val), index = std::size_t{ 0 }]() mutable {
        const auto start{ index };
        for(; index < val.size(); ++index){
            if(::isspace(val[index])) {
                break;
            }
        }
        return std::string{ val.c_str() + start, index++ - start };
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

template <typename T, typename DT = std::decay_t<T>>
std::vector<Data<DT>> GetData(std::vector<std::string> tokens) {
    std::vector<Data<DT>> data;
    data.reserve(tokens.size());

    std::transform(tokens.cbegin(), tokens.cend(), std::back_inserter(data), [](const auto& val) -> Data<DT>{
        auto &&op{ GetOperator(val) };
        if(op) {
            return *op;
        }
        if constexpr(std::is_integral_v<DT> && std::is_signed_v<DT>) {
            return static_cast<DT>(std::stoll(val));
        }
        else if(std::is_integral_v<DT> && !std::is_signed_v<DT>) {
            return static_cast<DT>(std::stoull(val));
        }
        else if(std::is_floating_point_v<DT>) {
            return static_cast<DT>(std::stod(val));
        }
        return {};
    });

    return data;
}

template <typename T, typename DT = std::decay_t<T>>
DT DoOperation(const DT a, const DT b, const Operation op) {
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

template <typename T, typename DT = std::decay_t<T>>
std::vector<Data<DT>> Fold(const std::vector<Data<DT>>& data, const Data<DT>& val) {
    return std::visit(
            [&data](auto &&val){
                using DV = std::decay_t<decltype(val)>;
                if constexpr(std::is_same_v<DV, DT>) {
                    auto cpy{ std::move(data) };
                    cpy.emplace_back(val);
                    return cpy;
                }
                else if(std::is_same_v<DV, Operation>){
                    assert(data.size() >= 2);
                    const auto a{ std::get<DT>(*std::next(data.rbegin())) };
                    const auto b{ std::get<DT>(*data.rbegin()) };

                    using DataListType = std::decay_t<decltype(data)>;
                    DataListType copy{ data.cbegin(), std::prev(data.cend(), 2) };
                    copy.emplace_back(DoOperation<DT>(a, b, val));
                    return copy;
                }
                else {
                    return data;
                }
            }
        , val);
}

template <typename T, typename DT=std::decay_t<T>>
DT DoEquation(std::string operation) {
    const auto data{ GetData<DT>( GetTokens(std::move(operation)) ) };
    const auto result{ std::accumulate(data.cbegin(), data.cend(), std::decay_t<decltype(data)>{}, Fold<DT>) };
    assert(!result.empty());
    return std::get<DT>(result[0]);
}

