#include <iostream>

#include <autonomy/location_module.hpp>

using namespace std;

struct null_parent
{
};

int main()
{
    int a(0);
    int b(1);

    autonomy::location_module<null_parent> loc_mod;
    cout << "Moving a to (0,3):  "
         << loc_mod.move(&a, autonomy::util::coord_pair(0, 3))
         << endl;

    cout << "Moving b to (0,3):  "
         << loc_mod.move(&b, autonomy::util::coord_pair(0, 3))
         << endl;

    cout << "Number of items in view port (0,0) x (3,3):  "
         << loc_mod.view(autonomy::util::coord_pair(0, 0),
                         autonomy::util::coord_pair(3, 3)).size() << endl;

    cout << "Moving b to (-1,-3):  "
         << loc_mod.move(&b, autonomy::util::coord_pair(-1, -3))
         << endl;

    cout << "Number of items in view port (-1,-2) x (3,3):  "
         << loc_mod.view(autonomy::util::coord_pair(-1, -2),
                         autonomy::util::coord_pair(3, 3)).size() << endl;

    cout << "Number of items in view port (-1,-3) x (3,3):  "
         << loc_mod.view(autonomy::util::coord_pair(-1, -3),
                         autonomy::util::coord_pair(3, 3)).size() << endl;

    cout << "A at (0,3)?  "
         << (loc_mod.query(autonomy::util::coord_pair(0, 3))
             == &a) << endl;

    cout << "Removing a." << endl;
    loc_mod.remove(&a);

    cout << "Number of items in view port (-1,-3) x (3,3):  "
         << loc_mod.view(autonomy::util::coord_pair(-1, -3),
                         autonomy::util::coord_pair(3, 3)).size() << endl;

    autonomy::util::coord_pair b_loc(loc_mod.locate(&b));
    cout << "Location of b:  ("
         <<  b_loc.x() << "," << b_loc.y() << ")" << endl;

    return 0;
}
