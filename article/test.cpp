#include "catch.hpp"

class Arithmetic
{
    public:
        virtual ~Arithmetic() = default;

        virtual double DoOperation() const = 0;
};

class Multiply : public Arithmetic
{
    public:
        Multiply(const double num) : m_number{ num }
        {}

        void MultiplyBy(const double num) {
            m_otherNumber = num;
        }

        double DoOperation() const override {
            return m_otherNumber * m_number;
        }

    private:
        const double m_number{ 0 };
        double m_otherNumber{ 0 };
};

TEST_CASE("test", "[test]")
{
    auto mult = Multiply{ 2.0 };
    mult.MultiplyBy(3.0);
    CHECK(mult.DoOperation() == 6.0);
}

