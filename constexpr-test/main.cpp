#include <iostream>

class Point
{
    public:
        constexpr Point(const int x, const int y) :
            m_x{x},
            m_y{y}
        {}

        constexpr void SetPoints(const int x, const int y)
        {
            m_x = x;
            m_y = y;
        }

        constexpr int GetX() const
        { return m_x; }

        constexpr int GetY() const
        { return m_y; }

    private:
        int m_x{0};
        int m_y{0};
};

template <typename PointType>
constexpr std::remove_reference_t<PointType> TransformSquared(PointType&& pt)
{
    if(std::is_lvalue_reference<PointType>::value)
    {
        std::remove_reference_t<PointType> copy{pt.GetX()*pt.GetX(), pt.GetY()*pt.GetY()};
        return copy;
    }
    std::remove_reference_t<PointType> copy = std::move(pt);
    copy.SetPoints(copy.GetX()*copy.GetX(), copy.GetY()*copy.GetY());
    return copy;
}

int main(const int argc, const char* argv[])
{
    constexpr auto valSquared = TransformSquared(Point{1,2}).GetY();
    std::cout << valSquared << "\n";

    constexpr auto justVal = Point{1, 300}.GetY();
    std::cout << justVal << "\n";

    Point compile{5, 5};
    compile.SetPoints(10, 10);
    const auto transformedCompile = TransformSquared(compile);
    std::cout << transformedCompile.GetX() << "\n";

    return 1;
}
