//! \file
//! \brief command registry that maps script instructions to their names
//!
//! Primary Author:  Aaron Weeden
//! Contributing Author:  Dylan Leeman

#ifndef AUTONOMY_COMMAND_REGISTRY_HPP
#define AUTONOMY_COMMAND_REGISTRY_HPP

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include <autonomy/util/serialization.hpp>
#include <autonomy/script_instruction.hpp>

namespace autonomy
{
	class command_registry
	{
          friend class boost::serialization::access;
		public:
            typedef boost::shared_ptr< script_instruction > command_ptr_t;

            void add_command(std::string, command_ptr_t );	
            command_ptr_t get_command(std::string) const;
        private:
            typedef std::map< std::string, command_ptr_t > _command_map_t;
            _command_map_t command_map;

            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {
              ar & BOOST_SERIALIZATION_NVP(command_map);
            }
	};
}
#endif
