#pragma once

template <typename T>
class Nested
{
    public:
        template <typename U>
        U IncreaseAndGet() const {
            return static_cast<U>(count++);
        }

    private:
        inline static int count{ 0 };
};
