#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

#include "Edge.h"
#include "City.h"
#include "Coordinate.h"

using namespace std;

class Vector
{
	public:
		Vector() { }  // Vector class void constructor
		
		bool addEdge(Edge e) // add edge to our Vector
		{
			int validCoordinatees = 0; // number of valid Coordinatees in this edge

			if (find(edgeList.begin(), edgeList.end(), e) == edgeList.end())
			{
				// add edge to edgeList
				edgeList.push_back(e);
				return true;
			}
			
			return false;
		}

		bool addEdge(City first, City second)
		{
			for (size_t i = 0; i < edgeList.size(); i++)
				if (edgeList.at(i).getStartPoint() == first && edgeList.at(i).getEndPoint() == second)
					return true;

			bool startPoint = false, endPoint = false;
			Coordinate newFirstCoordinate, newSecondCoordinate;

			for (size_t i = 0; i < edgeList.size() && (startPoint == false || endPoint == false); i++)
			{
				if (edgeList.at(i).getStartPointTag() == first.getTag())
				{
					startPoint = true;
					newFirstCoordinate = edgeList.at(i).getStartPoint();
				}
				else if (edgeList.at(i).getEndPointTag() == first.getTag())
				{
					startPoint = true;
					newFirstCoordinate = edgeList.at(i).getEndPoint();
				}
				else if (edgeList.at(i).getEndPointTag() == second.getTag())
				{
					endPoint = true;
					newSecondCoordinate = edgeList.at(i).getEndPoint();
				}
				else if (edgeList.at(i).getStartPointTag() == second.getTag())
				{
					endPoint = true;
					newSecondCoordinate = edgeList.at(i).getStartPoint();
				}
			}

			
			pair<Coordinate, Coordinate> edgeCoordinates;
			
			if (startPoint == false && endPoint == false)
				edgeCoordinates = getEdgeCoordinate(first, second);
			else if (startPoint == false && endPoint == true)
				edgeCoordinates = getEdgeCoordinate(first, *(new City(newSecondCoordinate.getPosX(), newSecondCoordinate.getPosY(), 0, 0)));
			else if (endPoint == false && startPoint == true)
				edgeCoordinates = getEdgeCoordinate(*(new City(newFirstCoordinate.getPosX(), newFirstCoordinate.getPosY(), 0, 0)), second);
			else
				edgeCoordinates = *(new pair<Coordinate, Coordinate>(newFirstCoordinate, newSecondCoordinate));

			Edge objEdge(edgeCoordinates.first, edgeCoordinates.second, first.getTag(), second.getTag());

			edgeList.push_back(objEdge);

			return true;
		}

		long getLen()
		{
			long sum = 0;
			for (size_t i = 0; i < edgeList.size(); i++)
				sum += edgeList.at(i).getLen();
			return sum;
		}

		double teta(Coordinate p1, Coordinate p2, Coordinate c)
		{
			Coordinate leftVal, rightVal;

			leftVal = p2 - p1;
			rightVal = p1 - c;

			double dotProduct = (leftVal.getPosX() * rightVal.getPosX()) + (leftVal.getPosY() * rightVal.getPosY());

			return -(dotProduct / (leftVal.cartesian() *  leftVal.cartesian()));
		}

		bool breakEageForNewCity(City first, City guest, City second)
		{
			for (size_t i = 0; i < edgeList.size(); i++)
			{
				if (edgeList.at(i).getStartPointTag() == first.getTag() && edgeList.at(i).getEndPointTag() == second.getTag())
				{
					Edge objEdgeBetweenFirstAndGuest, objEdgeBetweenGuestAndSecond;

					Coordinate objPickedCoordinate;

					double tetaFS = teta(edgeList.at(i).getStartPoint(), edgeList.at(i).getEndPoint(), guest);

					if (tetaFS <= 0)
						objPickedCoordinate = edgeList.at(i).getStartPoint();
					else if (tetaFS >= 1)
						objPickedCoordinate = edgeList.at(i).getEndPoint();
					else
						objPickedCoordinate = ((1 - tetaFS) * edgeList.at(i).getStartPoint()) + (tetaFS * edgeList.at(i).getEndPoint());

					float m = (guest.getPosY() - objPickedCoordinate.getPosY()) / (guest.getPosX() - objPickedCoordinate.getPosX());

					Coordinate objNewCoordinate;

					if (m == -std::numeric_limits<float>::infinity()){
						objNewCoordinate.setPosX(guest.getPosX());
						objNewCoordinate.setPosY((abs(guest.getPosY()) - abs(guest.getRadius())) * (guest.getPosY() / abs(guest.getPosY())));
					}
					else if (m == std::numeric_limits<float>::infinity())
					{
						objNewCoordinate.setPosX(guest.getPosX());
						objNewCoordinate.setPosY((abs(guest.getPosY()) + abs(guest.getRadius())) * (guest.getPosY() / abs(guest.getPosY())));
					}
					else if (m == 0)
					{
						objNewCoordinate.setPosY(guest.getPosY());
						
						if (guest.getPosX() > objPickedCoordinate.getPosX())
							objNewCoordinate.setPosX(guest.getPosX() - guest.getPosX());
						else
							objNewCoordinate.setPosX(guest.getPosX() + guest.getPosX());
					}
					else
					{
						float Dx = sqrt(guest.getRadius() * guest.getRadius() / (1 + (m * m)));

						if (guest.getPosX() < objPickedCoordinate.getPosX())
							objNewCoordinate.setPosX(guest.getPosX() + Dx);
						else
							objNewCoordinate.setPosX(guest.getPosX() - Dx);

						int PosY = m * (objNewCoordinate.getPosX() - objPickedCoordinate.getPosX()) + objPickedCoordinate.getPosY();

						objNewCoordinate.setPosY(PosY);
					}

					Edge objFG(edgeList.at(i).getStartPoint(), objNewCoordinate);
					objFG.setStartPointTag(first.getTag());
					objFG.setEndPointTag(guest.getTag());

					Edge objGS(objNewCoordinate, edgeList.at(i).getEndPoint());
					objGS.setStartPointTag(guest.getTag());
					objGS.setEndPointTag(second.getTag());

					edgeList.erase(edgeList.begin() + i);
					edgeList.push_back(objFG);
					edgeList.push_back(objGS);

					return true;
				}
			}

			return false;
		}

		bool addCoordinate(City v) // add Coordinate to our Coordinate list
		{
			// if v has not been added yet
			if (find(CoordinateList.begin(), CoordinateList.end(), v) == CoordinateList.end())
			{
				// add Coordinate to CoordinateList
				CoordinateList.push_back(v);
				return true;
			}

			return false;
		}

		bool addIncludedCoordinate(City v) // add Coordinate to our Coordinate list
		{
			// if v has not been added yet
			if (find(IncludedCoordinatesList.begin(), IncludedCoordinatesList.end(), v) 
				== IncludedCoordinatesList.end())
			{
				// add Coordinate to CoordinateList
				IncludedCoordinatesList.push_back(v);
				return true;
			}

			return false;
		}

		bool deleteIncludedCoordinatesList(size_t i) // delete Coordinate by its index
		{
			// if edge index is a valid number
			if (i >= 0 && i < IncludedCoordinatesList.size())
			{
				IncludedCoordinatesList.erase(IncludedCoordinatesList.begin() + i);
				return true;
			}

			return false;
		}

		bool deleteCoordinate(size_t i) // delete Coordinate by its index
		{
			// if edge index is a valid number
			if (i >= 0 && i < CoordinateList.size())
			{
				CoordinateList.erase(CoordinateList.begin() + i);
				return true;
			}

			return false;
		}

		bool deleteEdge(size_t i) // delete edge by its index
		{
			// if edge index is a valid number
			if (i >= 0 && i < edgeList.size())
			{
				edgeList.erase(edgeList.begin() + i);
				return true;
			}

			return false;
		}

		Edge getEdge(size_t i) // get edge by its index
		{
			// if edge index is a valid number
			if (i >= 0 && i < edgeList.size())
				return edgeList.at(i);
			
			return *(new Edge());
		}

		City getIncludedCoordinates(size_t i) // get edge by its index
		{
			// if edge index is a valid number
			if (i >= 0 && i < IncludedCoordinatesList.size())
				return IncludedCoordinatesList.at(i);

			return *(new City(-1));
		}

		const vector<Edge> getEdgeList() // get edges vector
		{
			return (const vector<Edge>)edgeList;
		}

		const vector<City> getIncludedCoordinatesList() // get edges vector
		{
			return (const vector<City>)IncludedCoordinatesList;
		}

		const vector<City> getCoordinateList() // get edges vector
		{
			return (const vector<City>)CoordinateList;
		}

		City getCoordinate(int i) // get Coordinate by its index
		{
			// if we have 
			if (i >= 0 && i < CoordinateList.size())
				return CoordinateList.at(i);

			return *(new City(-1));
		}

		size_t getCoordinateSize() // get the number of Coordinatees
		{
			return CoordinateList.size();
		}

		size_t getIncludedCoordinatesSize() // get the number of Coordinatees
		{
			return IncludedCoordinatesList.size();
		}

		size_t getEdgeSize()  // get the number of edges
		{
			return edgeList.size();
		}


	private:
		vector<City> CoordinateList, IncludedCoordinatesList;
		vector<Edge> edgeList;

		pair<Coordinate, Coordinate> getEdgeCoordinate(City first, City second)
		{
			Coordinate firstCoordinate, secondCoordinate;

			if (first.getPosX() == second.getPosX())
			{
				firstCoordinate.setPosX(first.getPosX());
				secondCoordinate.setPosX(second.getPosX());

				if (first.getPosY() > second.getPosY())
				{
					firstCoordinate.setPosY(first.getPosY() - first.getRadius());
					secondCoordinate.setPosY(second.getPosY() + second.getRadius());
				}
				else
				{
					firstCoordinate.setPosY(first.getPosY() + first.getRadius());
					secondCoordinate.setPosY(second.getPosY() - second.getRadius());
				}
			}
			else if (first.getPosY() == second.getPosY())
			{
				firstCoordinate.setPosY(first.getPosY());
				secondCoordinate.setPosY(second.getPosY());

				if (first.getPosX() > second.getPosX())
				{
					firstCoordinate.setPosX(first.getPosX() - first.getRadius());
					secondCoordinate.setPosX(second.getPosX() + second.getRadius());
				}
				else
				{
					firstCoordinate.setPosX(first.getPosX() + first.getRadius());
					secondCoordinate.setPosX(second.getPosX() - second.getRadius());
				}
			}
			else
			{
				double m = (second.getPosY() - first.getPosY()) / (double)(second.getPosX() - first.getPosX()),
					firstX = sqrt((first.getRadius() * first.getRadius()) / (1 + (m * m))),
					secondX = sqrt((second.getRadius() * second.getRadius()) / (1 + (m * m))),
					firstY = abs(m * firstX), secondY = abs(m * secondX);

				if (second.getPosX() > first.getPosX() && second.getPosY() > first.getPosY())
				{
					firstCoordinate.setPosX(first.getPosX() + firstX);
					firstCoordinate.setPosY(first.getPosY() + firstY);
					secondCoordinate.setPosX(second.getPosX() - secondX);
					secondCoordinate.setPosY(second.getPosY() - secondY);
				}
				else if (second.getPosX() < first.getPosX() && second.getPosY() < first.getPosY())
				{
					firstCoordinate.setPosX(first.getPosX() - firstX);
					firstCoordinate.setPosY(first.getPosY() - firstY);
					secondCoordinate.setPosX(second.getPosX() + secondX);
					secondCoordinate.setPosY(second.getPosY() + secondY);
				}
				else if (second.getPosX() < first.getPosX() && second.getPosY() > first.getPosY())
				{
					firstCoordinate.setPosX(first.getPosX() - firstX);
					firstCoordinate.setPosY(first.getPosY() + firstY);
					secondCoordinate.setPosX(second.getPosX() + secondX);
					secondCoordinate.setPosY(second.getPosY() - secondY);
				}
				else if (second.getPosX() > first.getPosX() && second.getPosY() < first.getPosY())
				{
					firstCoordinate.setPosX(first.getPosX() + firstX);
					firstCoordinate.setPosY(first.getPosY() - firstY);
					secondCoordinate.setPosX(second.getPosX() - secondX);
					secondCoordinate.setPosY(second.getPosY() + secondY);
				}
			}

			return *(new pair<Coordinate, Coordinate>(firstCoordinate, secondCoordinate));
		}
};

#endif	