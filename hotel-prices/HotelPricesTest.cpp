#include "catch.hpp"

template <typename PriceFunc>
class Hotel {
    public:
        constexpr Hotel(const PriceFunc *func, const int bedrooms, const int bathrooms) 
        : m_func(func), m_bedrooms(bedrooms), m_bathrooms(bathrooms) {}
        
        constexpr int get_price() const {
            return m_func(m_bedrooms, m_bathrooms);
        }

    private:
        const PriceFunc *m_func;
        const int m_bedrooms{ 0 };
        const int m_bathrooms{ 0 };
};

constexpr auto RoomCostFunc(const int bedrooms, const int bathrooms) {
    constexpr auto COST_PER_BEDROOM{ 50 };
    constexpr auto COST_PER_BATHROOM{ 100 };
    return COST_PER_BEDROOM*bedrooms + COST_PER_BATHROOM*bathrooms;
};

constexpr auto ApartmentCostFunc(const int bedrooms, const int bathrooms) {
    return RoomCostFunc(bedrooms, bathrooms) + 100;
};

constexpr auto HotelRoom(const int bedrooms, const int bathrooms) {
    return Hotel<decltype(RoomCostFunc)>{&RoomCostFunc, bedrooms, bathrooms};
}

constexpr auto HotelApartment(const int bedrooms, const int bathrooms) {
    return Hotel<decltype(ApartmentCostFunc)>{&ApartmentCostFunc, bedrooms, bathrooms};
}

TEST_CASE("test", "")
{
    constexpr auto rooms{ HotelRoom(3, 1) };
    constexpr auto apartments{ HotelApartment(1, 1) };
    constexpr auto totalPrice{ rooms.get_price() + apartments.get_price() };
    static_assert(totalPrice == 500, "test failure");
}
