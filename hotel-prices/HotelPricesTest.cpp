#include <iostream>
#include <vector>

using namespace std;

class HotelRoom {
    public:
        HotelRoom(const int bedrooms, const int bathrooms) 
        : m_bedrooms(bedrooms), m_bathrooms(bathrooms) {}

        virtual ~HotelRoom() = default;
        HotelRoom(const HotelRoom&) = default;
        HotelRoom(HotelRoom&&) = default;

        HotelRoom& operator=(const HotelRoom&) = default;
        HotelRoom& operator=(HotelRoom&&) = default;
        
        virtual int get_price() const {
            constexpr auto COST_PER_BEDROOM{ 50 };
            constexpr auto COST_PER_BATHROOM{ 100 };
            return COST_PER_BEDROOM*m_bedrooms + COST_PER_BATHROOM*m_bathrooms;
        }

    private:
        const int m_bedrooms{ 0 };
        const int m_bathrooms{ 0 };
};

class HotelApartment : public HotelRoom {
    public:
        HotelApartment(const int bedrooms, const int bathrooms) 
        : HotelRoom(bedrooms, bathrooms) {}

        virtual ~HotelApartment() = default;
        HotelApartment(const HotelApartment&) = default;
        HotelApartment(HotelApartment&&) = default;

        HotelApartment& operator=(const HotelApartment&) = default;
        HotelApartment& operator=(HotelApartment&&) = default;

        int get_price() const final {
            return HotelRoom::get_price() + 100;
        }
};


