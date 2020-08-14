#pragma once

#include <type_traits>

template <typename Enum>
class Flags
{
    public:
        constexpr explicit Flags() noexcept = default;

        template <typename... Args>
        constexpr explicit Flags(Args... args) noexcept {
            Set(args...);
        }

        constexpr bool IsEqual(const Flags& other) const noexcept {
            return this->m_flags == other.m_flags;
        }

        template <typename T>
        friend constexpr bool operator==(const Flags<T>& f1, const Flags<T>& f2) noexcept;

        template <typename T>
        friend constexpr bool operator!=(const Flags<T>& f1, const Flags<T>& f2) noexcept;

        constexpr auto& Set(const Enum e) noexcept {
            this->m_flags |= static_cast<EnumFlag>(e);
            return *this;
        }

        constexpr auto& Set(const Flags f) noexcept {
            this->m_flags |= f.m_flags;
            return *this;
        }

        template <typename... Args>
        constexpr auto& Set(Args... args) noexcept {
            static_assert(((std::is_same_v<Enum, Args> || std::is_same_v<Flags<Enum>, Args>) || ...));
            return (this->Set(args), ...);
        }

        constexpr auto& Unset(const Enum e) noexcept {
            this->m_flags &= ~static_cast<EnumFlag>(e);
            return *this;
        }

        constexpr auto& Unset(const Flags f) noexcept {
            this->m_flags &= ~f.m_flags;
            return *this;
        }

        template <typename... Args>
        constexpr auto& Unset(Args... args) noexcept {
            static_assert(((std::is_same_v<Enum, Args> || std::is_same_v<Flags<Enum>, Args>) || ...));
            return (this->Unset(args), ...);
        }

        constexpr auto& Flip() noexcept {
            this->m_flags = ~this->m_flags;
            return *this;
        }

        constexpr bool Test(const Enum e) const noexcept {
            return (m_flags & static_cast<EnumFlag>(e)) == static_cast<EnumFlag>(e);
        }

    private:
        static_assert(std::is_enum_v<Enum>);
        using EnumFlag = std::underlying_type_t<Enum>;
        EnumFlag m_flags{};
};

template <typename Enum>
constexpr bool operator==(const Flags<Enum>& f1, const Flags<Enum>& f2) noexcept
{
    return f1.IsEqual(f2);
}

template <typename Enum>
constexpr bool operator!=(const Flags<Enum>& f1, const Flags<Enum>& f2) noexcept
{
    return !f1.IsEqual(f2);
}

