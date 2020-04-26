#ifndef CITY_H
#define CITY_H

#include "Coordinate.h"

class City : public Coordinate
{
	public:
		City(int _tag) : Coordinate(), tag(_tag){} // City class void constructor

		City(float x, float y, double r, int _tag) : Coordinate(x, y), tag(_tag) // City class initial constructor
		{
			setRadius(r); // set city radius
		}

		double getRadius() // get city radius
		{
			return radius;
		}
		
		void setRadius(double r)  // set city radius
		{
			radius = r; // set city to given number
		}

		// input stream operator definition
		friend istream &operator >>(istream &in, City &c)
		{
			in >> c.pos_x >> c.pos_y >> c.radius;
			return in;
		}

		// output stream operator definition
		friend ostream &operator <<(ostream &out, City c)
		{
			out << " [" << c.pos_x << ", " << c.pos_y << "] Raduis : " << c.radius << " ";
			return out;
		}

		int getTag()
		{
			return tag;
		}

		void setTag(int _tag)
		{
			if (_tag != -1)
				tag = _tag;
		}

	private:
		float radius;
		int tag;
};

#endif