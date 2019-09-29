#ifndef TUBELET_H
#define TUBELET_H

#include <boost/geometry.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/register/point.hpp>


namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

/**
 * @brief An observation indicates the probability of something belonging to a given class.
 */
struct observation {
	int ci; /**< Class index */
	double prob; /**< Probability: 0..1 */
};

using observations = std::vector<observation>;

struct tubelet2d
{
	double x,y;
	std::shared_ptr<observations> obs;
};

BOOST_GEOMETRY_REGISTER_POINT_2D(tubelet2d, double, cs::cartesian, x, y)

class tubelets {
public:
	using box2d = bg::model::box<tubelet2d>;
	using rtree = bgi::rtree< tubelet2d, bgi::rstar<16, 4> >;

	/**
	 * @brief Default constructor.
	 */
	tubelets();

	/**
	 * Alternative constructor
	 * @param x0 horizontal origin of viewing frustrum
	 * @param y0 vertical origin of viewing frustrum
	 * @param w width of viewing frustrum
	 * @param h height of viewing frustrum
	 */
	tubelets(double x0, double y0, double w, double h);
	~tubelets();

	/**
	 * @brief Add an observation at a given point.
	 * @param x horizontal absolute position
	 * @param y vertical absolute position
	 * @param ci class index
	 * @param prob probability of class
	 * @min_dist clustering distance
	 */
	void add_observation(double x, double y, int ci, double prob, double min_dist);

	/**
	 * Get nearests tubelets from a given point
	 * @param x horizontal position of target point
	 * @param y vertical position of target point
	 * @param n number of tubelets
	 * @param min_dist clustering distance.
	 */
	std::vector<tubelet2d> get_nearests_from_point(double x, double y,size_t n, double min_dist );

	/**
	 * @brief Update frustrum position
	 * @param dx horizontal translation
	 * @param dy vertical translation
	 */
	void move_frustrum(double dx, double dy);

	/**
	 * @brief Remove tubelets outside of frustrum.
	 */
	void clip();

	/**
	 * @brief Get tree.
	 */
	const rtree& get_tree() const { return this->tree; }

	// Debugging
	void print_all();

	/**
	 * @brief clear tree.
	 */
	void clear();

private:
	rtree tree;
    box2d frustrum;
};


#endif // TUBELET_H
