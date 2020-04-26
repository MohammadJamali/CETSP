#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

using std::istream;
using std::ostream;

class Coordinate
{
	public:
		Coordinate() // Coordinate class void constructor
		{
			pos_x = pos_y = 0; // set position to defult value
		}

		Coordinate(float x, float y) // Coordinate class initial constructor
		{
			pos_x = x; // set position to given number
			pos_y = y; // set position to given number
		}

		float getPosX() // get the position of x
		{
			return pos_x; 
		}

		float getPosY() // get the position of y
		{
			return pos_y;
		}

		void setPosX(float x) // set the position of x
		{
			pos_x = x; // set position to given number
		}

		void setPosY(float y) // set the position of y
		{
			pos_y = y; // set position to given number
		}

		double cartesian()
		{
			return sqrt((pos_x * pos_x) + (pos_y * pos_y));
		}

		// equation operator definition
		friend bool operator ==(Coordinate f, Coordinate s)
		{
			// if two coordinate classes are equal
			if (f.getPosX() == s.getPosX() && f.getPosY() == s.getPosY())
				return true;
			else
				return false;
		}

		// qual operator definition
		void operator =(Coordinate f)
		{
			pos_x = f.getPosX();
			pos_y = f.getPosY();
		}

		// subtraction operator definition
		friend Coordinate operator- (Coordinate f, Coordinate s)
		{
			return *(new Coordinate(f.getPosX() - s.getPosX(), f.getPosY() - s.getPosY()));
		}

		// subtraction operator definition
		friend Coordinate operator* (double i, Coordinate &f)
		{
			Coordinate temp(f);
			temp.pos_x *= i;
			temp.pos_y *= i;

			return temp;
		}

		friend Coordinate operator+ (Coordinate f, Coordinate s)
		{
			return *(new Coordinate(f.getPosX() + s.getPosX(), f.getPosY() + s.getPosY()));
		}

		// input stream operator definition
		friend istream& operator>> (Coordinate &c, istream &in)
		{
			in >> c.pos_x >> c.pos_y;
			return in;
		}

		// output stream operator definition
		friend ostream& operator<< (ostream &out, Coordinate c)
		{
			out << " [" << c.pos_x << ", " << c.pos_y << "] ";
			return out;
		}

	protected:
		float pos_x, pos_y;
};

#endif