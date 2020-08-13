#include "catch.hpp"

class InkjetPrinter
{
    public:
        bool Print(const char* characters)
        {
            const auto amount = strlen(characters);
            if(amount > m_inkLevel) {
                return false;
            }
            m_inkLevel -= amount;
            return true;
        }

        std::size_t Returnlevel(const std::size_t inkLevel, const std::size_t printAmt) const {
        }

    private:
        std::size_t m_inkLevel{ 100 };
};

class ColorInkjetPrinter : public InkjetPrinter
{
    public:
        virtual bool Print(const char* characters, const bool colorPrint)
        {
        }

    private:
        std::size_t m_colorInkLevel{ 100 };
};

class VeryEfficientColorInkjetPrinter : public ColorInkjetPrinter
{
    bool heon = true;
    virtual bool Print(const char* characters, const bool colorPrint)
    {
    }
}


TEST_CASE("test", "[test]")
{

}

