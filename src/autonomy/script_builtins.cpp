//! \file
//! \brief implements the built-in capabilities of the drone language
#include <math.h>

#include <autonomy/script_builtins.hpp>

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::less_than>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::less_than)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::logical_and>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::logical_and)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::logical_or>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::logical_or)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::logical_not>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::logical_not)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::literal>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::literal)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::dup>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::dup)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::pop>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::pop)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::add>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::add)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::sub>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::sub)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::multiply>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::multiply)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::divide>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::divide)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::power>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::power)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::cond_jump>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::cond_jump)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::load>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::load)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::store>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::store)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::jump>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::jump)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::rel_jump>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::rel_jump)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::cond_rel_jump>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::cond_rel_jump)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::script_builtins::equals>)
BOOST_CLASS_EXPORT(autonomy::script_builtins::equals)

namespace autonomy { namespace script_builtins {

unsigned int dup::execute(size_t which_queue, entity::scripted_drone & drone)
{
    int top = drone.pop_stack();
    drone.push_stack(top);
    drone.push_stack(top);
    return 0;
}

unsigned int pop::execute(size_t which_queue, entity::scripted_drone & drone)
{
    drone.pop_stack();
    return 0;
}

unsigned int add::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left + right);
    return 0;
}

unsigned int sub::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left - right);
    return 0;
}

unsigned int multiply::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left * right);
    return 0;
}

//! execute(size_t which_queue, entity::scripted_drone & drone)
unsigned int divide::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left / right);
    return 0;
}

unsigned int power::execute(size_t which_queue, entity::scripted_drone & drone)
{
    int base      = drone.pop_stack();
    int exponent  = drone.pop_stack();
    drone.push_stack(static_cast<int>(pow(static_cast<double>(base),
                     static_cast<double>(exponent))));
    return 0;
}

unsigned int cond_jump::execute(size_t which_queue, entity::scripted_drone & drone)
{
  int line = drone.pop_stack();
	int cond = drone.pop_stack();
	if (cond != 0)
	{
		drone.goto_inst(line);
	}
    return 0;
}

unsigned int load::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int id = drone.pop_stack();
	int val = drone.get_local_var(id);
	drone.push_stack(val);
    return 0;
}

unsigned int store::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int val = drone.pop_stack();
	int id = drone.pop_stack();
	drone.set_local_var(id,val);
    return 0;
}

unsigned int jump::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int line = drone.pop_stack();
	drone.goto_inst(line);
    return 0;
}

unsigned int rel_jump::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int off = drone.pop_stack();
	drone.move_inst(off);
    return 0;
}

unsigned int cond_rel_jump::execute(size_t which_queue, entity::scripted_drone & drone)
{
    int off = drone.pop_stack();
	int cond = drone.pop_stack();
	if (cond != 0)
	{
		drone.move_inst(off);
	}
    return 0;
}

unsigned int equals::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	if (left == right)
		drone.push_stack(1);
	else 
		drone.push_stack(0);
    return 0;
}

unsigned int less_than::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	if (left < right)
		drone.push_stack(1);
	else 
		drone.push_stack(0);
    return 0;
}

unsigned int logical_and::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	if (left != 0 && right != 0)
		drone.push_stack(1);
	else
		drone.push_stack(0);
    return 0;
}

unsigned int logical_or::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	if (left != 0 || right != 0)
		drone.push_stack(1);
	else
		drone.push_stack(0);
    return 0;
}

unsigned int logical_not::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int val = drone.pop_stack();
	if (val == 0)
		drone.push_stack(1);
	else
		drone.push_stack(0);
    return 0;
}

unsigned int literal::execute(size_t which_queue, entity::scripted_drone & drone)
{
	drone.push_stack(_val);
    return 0;
}

}}
