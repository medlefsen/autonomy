//! \file
//! \brief A command registry that maps script instructions to their names.
//! 
//! Primary Author:  Aaron Weeden
//! Contributing Author:  Dylan Leeman
//! Most code copied from old autonomy/core/game_state.cpp by Matt Edlefsen

#include <utility>

#include <autonomy/command_registry.hpp>

namespace autonomy
{
	//! Adds a name/instruction pair to the registry 
	void command_registry::add_command(std::string name, boost::shared_ptr< script_instruction > inst)	
	{
		command_map.insert(std::make_pair(name, inst));
	}

#ifdef TESTING
	//! Returns string if add_command works  
	std::string test_command_registry_add_command()
	{
		std::string name = "add_command works.";
		add_command(name, boost::shared_ptr< script_instruction >());
		return command_map[0].name;
	}
#endif

	//! Searches the registry for an instruction given its name
	//! Returns a default-constructed shared_ptr if the command is not registered
	boost::shared_ptr< script_instruction > command_registry::get_command(std::string name) const
	{
        _command_map_t::const_iterator i = command_map.find(name);
		if(i == command_map.end())
		{
			return boost::shared_ptr< script_instruction >();
		}
		else
		{
			return i->second;
		}
	}
	
#ifdef TESTING
	std::string test_command_registry_get_command()
	{
		//!  Command is not in registry
		if(!get_command("Default")==boost::shared_ptr< script_instruction >)
		return "Command was not found when it should have been";
		add_command("Default", boost::shared_ptr< script_instruction >());
		// Here should be test for command in registry
	}
#endif
}
