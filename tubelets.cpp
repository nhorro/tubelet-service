#include "tubelets.h"

#include <iostream>
#include <boost/format.hpp>

tubelets::tubelets(double x0, double y0, double w, double h)
:
	frustrum( tubelet2d{x0, y0}, tubelet2d{x0+w, y0+h} )
{

}

tubelets::~tubelets()
{

}

void tubelets::add_observation(double x, double y, int ci, double prob, double min_dist)
{
	tubelet2d new_point;
	new_point.x = x;
	new_point.y = y;

	std::vector<tubelet2d> tmp =	this->get_nearests_from_point(x,y,1,min_dist);
	if (tmp.size())
	{
		//std::cout << "A point already exists within that range." << std::endl;
		tmp[0].obs->push_back(observation{ci,prob});
	}
	else
	{
		//std::cout << "Point does not exist. Creating one." << std::endl;
		new_point.obs.reset(new observations);
		new_point.obs->push_back(observation{ci,prob});
		tree.insert(new_point);
	}
}

std::vector<tubelet2d> tubelets::get_nearests_from_point(double x, double y, size_t n, double min_dist )
{
	std::vector<tubelet2d> tmp;
	tubelet2d target;
	target.x = x;
	target.y = y;
	this->tree.query(bgi::nearest(target,n), std::back_inserter(tmp));
	if (tmp.size())
	{
		double dist = bg::distance(target, tmp[0]);
		if ( dist > min_dist )
		{
			tmp.clear();
		}
	}
	return tmp;
}

void tubelets::clip()
{
	std::vector<tubelet2d> to_be_removed;
	this->tree.query(!bgi::within(this->frustrum), std::back_inserter(to_be_removed));
    this->tree.remove(to_be_removed.begin(), to_be_removed.end());
}

void tubelets::move_frustrum(double dx, double dy)
{
    boost::geometry::transform(this->frustrum,this->frustrum,
    		boost::geometry::strategy::transform::translate_transformer<double,2,2>(dx,dy));
}

void tubelets::print_all()
{
	size_t index = 0;
	for(auto const& v: tree)
	{
		std::cout << boost::format("p%d: (%f,%f) obs: %d")
			% index % v.x % v.y % v.obs->size() << std::endl;

		// observations
		for(auto o: *(v.obs))
		{
			std::cout << boost::format("  { class: %d, prob: %f } ") % o.ci % o.prob << std::endl;
		}

		index++;
	}
}

