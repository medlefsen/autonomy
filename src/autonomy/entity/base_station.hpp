#include <autonomy/entity/base_station.fwd.hpp>
#ifndef AUTONOMY_BASE_STATION_HPP
#define AUTONOMY_BASE_STATION_HPP
#include <typeinfo>

#include <autonomy/game.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/entity/drone.hpp>

namespace autonomy {
    namespace entity
    {
        class base_station
            : public drone
        {
            public:
                base_station(entity_id_t uni,
                             game & which_game,
                             int fuel = 0)
                    : drone(uni,fuel), _which_game(&which_game)
                { }
                virtual ~base_station(){}

            private:
                game * _which_game;

                base_station(){}

                virtual void controller();

                friend class boost::serialization::access;
                template < class Archive >
                void serialize ( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(drone);
                    ar & BOOST_SERIALIZATION_NVP(_which_game);
                }
        };
    }
}

#endif
