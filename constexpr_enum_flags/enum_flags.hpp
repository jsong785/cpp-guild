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

        template <typename T>
        friend constexpr bool operator==(const Flags<T>& f1, const Flags<T>& f2) noexcept;

        template <typename T>
        friend constexpr bool operator!=(const Flags<T>& f1, const Flags<T>& f2) noexcept;

        template <typename... Args>
        constexpr auto& Set(Args... args) noexcept {
            this->m_flags |= (static_cast<EnumFlag>(args) | ...);
            return *this;
        }

        template <typename... Args>
        constexpr auto& Unset(Args... args) noexcept {
            this->m_flags &= ~(static_cast<EnumFlag>(args) | ...);
            return *this;
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
    return f1.m_flags == f2.m_flags;
}

template <typename Enum>
constexpr bool operator!=(const Flags<Enum>& f1, const Flags<Enum>& f2) noexcept
{
    return !(f1 == f2);
}

