#include <iostream>

#include "tubelets.h"



void test()
{
	tubelets t(0.0,0.0,320.0,200.0);

	// Insert some observations near point P0(120,100)
	t.add_observation(120.0, 100.0, 10, 0.7,10.0);
	t.add_observation(121.0, 101.0, 11, 0.7,10.0);
	t.add_observation(121.0, 101.0, 12, 0.7,10.0);

	// Insert some observations near point P0(150,100)
	t.add_observation(200.0, 101.0, 12, 0.7,10.0);
	t.add_observation(200.0, 101.0, 12, 0.7,10.0);
	t.add_observation(200.0, 101.0, 12, 0.7,10.0);

	// Show all points before clipping
	std::cout << "Before clipping" << std::endl;
	t.print_all();

	// Clip
	t.move_frustrum(150.0, 0.0);
	t.clip();

	// Show all points after clipping
	std::cout << "After clipping" << std::endl;
	t.print_all();
}



int main(int argc, const char* argv[]) 
{
	std::cout << "tubelet-service" << std::endl;

	test();

	return 0;
}
