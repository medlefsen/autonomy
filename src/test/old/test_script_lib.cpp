#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#include <autonomy/game.hpp>
#include <autonomy/script_library.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/script_instruction.hpp>

using namespace std;

void print_script( ostream & os, boost::shared_ptr<autonomy::instruction_list> il_ptr )
{
    BOOST_FOREACH( boost::shared_ptr<autonomy::script_instruction> next, *il_ptr )
    {
        os << next->name() << endl;
    }
}

int main()
{
    autonomy::script_library<autonomy::game> sl;
    autonomy::script_object_id_t script_handle(sl.new_script("test"));
    sl.set_script(script_handle, string("int $a; $a := 0;"));
    cout << sl.compile_script(script_handle);

    cout << "Script:  " << sl.fetch_name(script_handle) << endl;
    print_script( cout, sl.fetch_compiled_script( script_handle ) );

    autonomy::script_object_id_t shandle1(sl.new_script());
    cout << "Compiling:  " << sl.fetch_name(shandle1) << endl;
    cout << '\t' << sl.compile_script(shandle1) << endl;

    sl.set_script(shandle1, string("char $a;"));
    cout << "Compiling:  " << sl.fetch_name(shandle1) << endl;
    cout << '\t' << sl.compile_script(shandle1) << endl;

    sl.rename_script(shandle1, "move test");
    sl.set_script(shandle1, string("int $x; int $y; move($x,$y);"));
    cout << "Compiling:  " << sl.fetch_name(shandle1) << endl;
    cout << '\t' << sl.compile_script(shandle1) << endl;

    print_script(cout, sl.fetch_compiled_script(shandle1));
}
