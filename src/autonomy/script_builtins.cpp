//! \file
//! \brief implements the built-in capabilities of the drone language
#include <math.h>

#include <autonomy/script_builtins.hpp>

namespace autonomy { namespace script_builtins {

BOOST_CLASS_EXPORT(script_instruction_base<dup>)
BOOST_CLASS_EXPORT(dup)
unsigned int dup::execute(size_t which_queue, entity::scripted_drone & drone)
{
    int top = drone.pop_stack();
    drone.push_stack(top);
    drone.push_stack(top);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<pop>)
BOOST_CLASS_EXPORT(pop)
unsigned int pop::execute(size_t which_queue, entity::scripted_drone & drone)
{
    drone.pop_stack();
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<add>)
BOOST_CLASS_EXPORT(add)
unsigned int add::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left + right);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<sub>)
BOOST_CLASS_EXPORT(sub)
unsigned int sub::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left - right);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<multiply>)
BOOST_CLASS_EXPORT(multiply)
unsigned int multiply::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left * right);
    return 0;
}

//! execute(size_t which_queue, entity::scripted_drone & drone)
BOOST_CLASS_EXPORT(script_instruction_base<divide>)
BOOST_CLASS_EXPORT(divide)
unsigned int divide::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int right = drone.pop_stack();
	int left = drone.pop_stack();
	drone.push_stack(left / right);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<power>)
BOOST_CLASS_EXPORT(power)
unsigned int power::execute(size_t which_queue, entity::scripted_drone & drone)
{
    int base      = drone.pop_stack();
    int exponent  = drone.pop_stack();
    drone.push_stack(static_cast<int>(pow(static_cast<double>(base),
                     static_cast<double>(exponent))));
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<cond_jump>)
BOOST_CLASS_EXPORT(cond_jump)
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

BOOST_CLASS_EXPORT(script_instruction_base<load>)
BOOST_CLASS_EXPORT(load)
unsigned int load::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int id = drone.pop_stack();
	int val = drone.get_local_var(id);
	drone.push_stack(val);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<store>)
BOOST_CLASS_EXPORT(store)
unsigned int store::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int val = drone.pop_stack();
	int id = drone.pop_stack();
	drone.set_local_var(id,val);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<jump>)
BOOST_CLASS_EXPORT(jump)
unsigned int jump::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int line = drone.pop_stack();
	drone.goto_inst(line);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<rel_jump>)
BOOST_CLASS_EXPORT(rel_jump)
unsigned int rel_jump::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int off = drone.pop_stack();
	drone.move_inst(off);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<cond_rel_jump>)
BOOST_CLASS_EXPORT(cond_rel_jump)
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

BOOST_CLASS_EXPORT(script_instruction_base<equals>)
BOOST_CLASS_EXPORT(equals)
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

BOOST_CLASS_EXPORT(script_instruction_base<less_than>)
BOOST_CLASS_EXPORT(less_than)
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

BOOST_CLASS_EXPORT(script_instruction_base<logical_and>)
BOOST_CLASS_EXPORT(logical_and)
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

BOOST_CLASS_EXPORT(script_instruction_base<logical_or>)
BOOST_CLASS_EXPORT(logical_or)
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

BOOST_CLASS_EXPORT(script_instruction_base<logical_not>)
BOOST_CLASS_EXPORT(logical_not)
unsigned int logical_not::execute(size_t which_queue, entity::scripted_drone & drone)
{
	int val = drone.pop_stack();
	if (val == 0)
		drone.push_stack(1);
	else
		drone.push_stack(0);
    return 0;
}

BOOST_CLASS_EXPORT(script_instruction_base<literal>)
BOOST_CLASS_EXPORT(literal)
unsigned int literal::execute(size_t which_queue, entity::scripted_drone & drone)
{
	drone.push_stack(_val);
    return 0;
}

}}
