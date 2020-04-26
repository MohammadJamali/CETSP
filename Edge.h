#ifndef EDGE_H
#define EDGE_H

#include <cmath>

#include "Coordinate.h"

class Edge
{
	public:
		Edge(): start_point_tag(-1), end_point_tag(-1){}

		Edge(Coordinate first, Coordinate last, unsigned short stag=0, unsigned short etag=0) // Coordinate class initial constructor
		{
			start_point = first; // set start position to given number
			end_point = last; // set end position to given number
			start_point_tag = stag;
			end_point_tag = etag;

			setLen(); // update length of edge
		}

		void setStartPoint(Coordinate v, unsigned short tag) // set the start position
		{
			start_point = v; // set start position to given number
			setStartPointTag(tag);

			setLen(); // update length of edge
		}
		
		void setEndPoint(Coordinate v, unsigned short tag) // set the end position
		{
			end_point = v; // set end position to given number
			setEndPointTag(tag);

			setLen(); // update length of edge
		}

		Coordinate getStartPoint() // get the start position
		{
			return start_point;
		}

		Coordinate getEndPoint() // get the end position
		{
			return end_point;
		}

		double getLen() // get edge len
		{
			return len;
		}

		void setLen(double l) // set edge len
		{
			if (len >= 0) // length cannot be negative
				len = l;
			else
				len = 0;
		}

		friend bool operator ==(Edge f, Edge s)
		{
			// if two edge class are equal to each other
			if (f.getStartPoint() == s.getStartPoint() && 
				f.getEndPoint() == s.getEndPoint() &&
				f.getLen() == s.getLen())
				return true;
			else
				return false;
		}

		int getStartPointTag()
		{
			return start_point_tag;
		}

		int getEndPointTag()
		{
			return end_point_tag;
		}

		void setStartPointTag(int i)
		{
			if (i > 0)
				start_point_tag = i;
		}

		void setEndPointTag(int i)
		{
			if (i > 0)
				end_point_tag = i;
		}

	protected:
		Coordinate start_point, end_point;
		int start_point_tag, end_point_tag;
		double len;

		void setLen() // set lengh of edge
		{
			if (getStartPointTag() != -1 && getEndPointTag() != -1)
				// formule : len = ((x1 - x2)^2 + (y1 - y2)^2)^0.5
				len = sqrt(pow(end_point.getPosX() - start_point.getPosX(), 2) 
						 + pow(end_point.getPosY() - start_point.getPosY(), 2));
		}
};

#endif