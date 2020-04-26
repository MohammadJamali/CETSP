#ifndef CETSP_H
#define CETSP_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

#include "Vector.h"
#include "Coordinate.h"
#include "City.h"

#define index unsigned

using namespace std;

bool sortFunction(pair< index, float > i, pair< index, float > j)
{
	return (i.second > j.second);
}

class CETSP
{
	public:
		CETSP(vector<City> _pv, index startP) : vecCityList(_pv), startPoint(startP)
		{
			cout << " Close enough traveling salesman problem is ready to solve ..." << endl << endl;
		}

		/*
			Algorithm :
            1) found the relax solution ( at first find three nodes that they had farthest distance from each other ) for tree node
            2) if sum of distance in relax solution is less than lower bound goto 3 else return
            3) define V as set of uncoverd vertixes
                I)      for each remainded city do step II
                II)     for all edges in the partial solution
                III)    define θ and compute − ( p2 − p1 )⊤( p1 − c ) / || p2 − p1 || for witch p1p2 is an edge and c is vertix
                IV)   find minimum d defined as distance between c and all p1p2 s in partial solution
                V)    if d is less then or equal to radius of c then c is covered
                VI)   if goto II if any edge reminded else goto VII
                VII)  if goto I if any vertix reminded else goto 4
            4) compute gamma for all k in V and select a vertex which has greater gamma for next loop
		*/
		string solve() // return : list of tour vertex coordinate
		{
			cout << endl << " Solving ..." << endl << " Generating first three nodes ..." << endl;
			vector<index> firstThreeNodes = getStartTriangle(startPoint, vecCityList);

			cout << " Generating solving tree ..." << endl;

			Vector problemVector;

			for each (City var in vecCityList)
				problemVector.addCoordinate(var);

			for each (index var in firstThreeNodes)
				problemVector.addIncludedCoordinate(vecCityList.at(var));

			for (size_t i = 0; i < firstThreeNodes.size() - 1; i++)
				problemVector.addEdge(vecCityList.at(firstThreeNodes.at(i)),
				vecCityList.at(firstThreeNodes.at(i+1)));

			solve_helper(problemVector);

			return recoreds;
		}

	private:
		vector<City> vecCityList;

		string recoreds;
		int upper_bound = INT_MAX;

		index startPoint;

		void solve_helper(Vector problemNodeVector)
		{
			if (upper_bound < problemNodeVector.getLen())
				return;

			vector<index> unCoverdCities;

			for (size_t i = 0; i < problemNodeVector.getCoordinateSize(); i++){
				bool included = false;
				for each (City c in problemNodeVector.getIncludedCoordinatesList())
				{
					if (c == problemNodeVector.getCoordinate(i)){
						included = true;
						break;
					}
				}
				if (!included)
					if (!isCityCoverd(problemNodeVector.getCoordinate(i), problemNodeVector))
						unCoverdCities.push_back(i);
			}

			if (unCoverdCities.size() == 0)
			{
				setRecord(problemNodeVector);
				return;
			}
			
			// compute gamma for all k in V and select a vertix whitch has greater gamma for next loop
			vector< pair< index, float > > gammaList;
			for (size_t i = 0; i < unCoverdCities.size(); i++)
				gammaList.push_back(*(new pair<index, float>(unCoverdCities.at(i),
				gammaK(unCoverdCities.at(i), problemNodeVector))));

			std::sort(gammaList.begin(), gammaList.end(), sortFunction);

			for (size_t i = 0; i < gammaList.size(); i++)
			{
				for (size_t j = 0; j < problemNodeVector.getEdgeSize(); j++)
				{
					Vector newProblemVector;

					for each (City var in problemNodeVector.getCoordinateList())
						newProblemVector.addCoordinate(var);

					for each (Edge var in problemNodeVector.getEdgeList())
						newProblemVector.addEdge(var);

					for each (City var in problemNodeVector.getIncludedCoordinatesList())
						newProblemVector.addIncludedCoordinate(var);
					newProblemVector.addIncludedCoordinate(problemNodeVector.getCoordinate(gammaList.at(i).first));

					if (newProblemVector.breakEageForNewCity(
						problemNodeVector.getCoordinate(problemNodeVector.getEdge(j).getStartPointTag()),
						problemNodeVector.getCoordinate(gammaList.at(i).first),
						problemNodeVector.getCoordinate(problemNodeVector.getEdge(j).getEndPointTag())))
						solve_helper(newProblemVector);

				}
			}
		}

		void setRecord(Vector problemNodeVector)
		{	
			upper_bound = problemNodeVector.getLen();
			index state = startPoint;

			recoreds.clear();
			for (size_t c = 0; c < problemNodeVector.getEdgeSize(); c++)
			{
				for (size_t i = 0; i < problemNodeVector.getEdgeSize(); i++)
				{
					if (((Edge)problemNodeVector.getEdgeList().at(i)).getStartPointTag() == state)
					{
						recoreds.append("[" + to_string(problemNodeVector.getEdge(i).getStartPoint().getPosX())
							+ " , " + to_string(problemNodeVector.getEdge(i).getStartPoint().getPosY())
							+ "] [" + to_string(problemNodeVector.getEdge(i).getEndPoint().getPosX())
							+ " , " + to_string(problemNodeVector.getEdge(i).getEndPoint().getPosY()) + "] \t ("
							+ to_string(problemNodeVector.getEdge(i).getStartPointTag()) + " - "
							+ to_string(problemNodeVector.getEdge(i).getEndPointTag()) + " )\n");


						state = ((Edge)problemNodeVector.getEdgeList().at(i)).getEndPointTag();
						break;
					}
				}
			}
		}


		vector<index> getStartTriangle(int firstNodeIndex, vector<City> cityList)
		{
			vector<index> result; // result of function : Start Triangle Nodes
			float max_distance = FLT_MIN;
			index desiredNodeIndex = firstNodeIndex; // desired : max distance
			index temp = desiredNodeIndex;

			result.push_back(desiredNodeIndex); // save the first node index

			for (index triangleNodes = 0; triangleNodes < 2; triangleNodes++) // for 2 remining
			{
				for (index i = 0; i < cityList.size(); i++)
				{
					if (i == desiredNodeIndex || i == firstNodeIndex)
						continue; // one node should not check with it selfs

					Edge objEdge(cityList.at(desiredNodeIndex), cityList.at(i)); // create new edge

					// check its distance with last max distance
					if (objEdge.getLen() - cityList.at(desiredNodeIndex).getRadius() -
						cityList.at(i).getRadius() > max_distance)
					{
						temp = i; // remember best choice until now
						max_distance = objEdge.getLen() 
							- cityList.at(desiredNodeIndex).getRadius() 
							- cityList.at(i).getRadius(); // remember its distance
					}
				}

				desiredNodeIndex = temp; // desired node has been found successfully
				result.push_back(desiredNodeIndex); // save desired node index
				max_distance = FLT_MIN;
			}

			result.push_back(firstNodeIndex); // save the first node index agian

			return result;
		}

		double minDistance(Coordinate c, Edge e)
		{
			double _teta = teta(e.getStartPoint(), e.getEndPoint(), c);

			if (_teta >= 1)
				return (e.getEndPoint() - c).cartesian();
			else if (_teta < 1 && _teta > 0)
				return ((((1 - _teta) * e.getStartPoint()) + (_teta * e.getEndPoint())) - c).cartesian();
			else
				return (e.getStartPoint() - c).cartesian();
		}

		bool isCityCoverd(City objCity ,Vector probVec)
		{
			for each (Edge edge in probVec.getEdgeList())
				if (minDistance(objCity, edge) <= objCity.getRadius())
					return true;

			return false;
		}

		pair<index, index> closestNeighborsIndex(int k, Vector probVec)
		{
			int firstClosestIndex = 0, secondClosestIndex = 0, 
				firstClosestDistance = INT_MAX, secondClosestDistance = INT_MAX;

			for (size_t i = 0; i < probVec.getIncludedCoordinatesSize(); i++)
			{
				int distance = (new Edge(probVec.getCoordinate(k), 
					probVec.getIncludedCoordinates(i)))->getLen();

				if (distance < firstClosestDistance)
				{
					firstClosestDistance = distance;
					firstClosestIndex = probVec.getIncludedCoordinates(i).getTag();
				}
				else if (distance < secondClosestDistance)
				{
					secondClosestDistance = distance;
					secondClosestIndex = probVec.getIncludedCoordinates(i).getTag();
				}
			}

			return *(new pair<index, index>(firstClosestIndex, secondClosestIndex));
		}

		float gammaK(int k, Vector probVec)
		{
			pair<index, index> closestNeighborsIndexs = closestNeighborsIndex(k, probVec);

			float gammaK = (new Edge(probVec.getCoordinate(k), 
				probVec.getCoordinate(closestNeighborsIndexs.first)))->getLen()
				+ (new Edge(probVec.getCoordinate(k), 
				probVec.getCoordinate(closestNeighborsIndexs.second)))->getLen()
				- (new Edge(probVec.getCoordinate(closestNeighborsIndexs.first), 
				probVec.getCoordinate(closestNeighborsIndexs.second)))->getLen();

			return gammaK;
		}

		/*
		this function will calculate this formula :

		θ∗ = − ( p2 − p1 )⊤( p1 − c ) / || p2 − p1 ||

		where ⊤ is the dot product and || is cartesian
		*/
		double teta(Coordinate p1, Coordinate p2, Coordinate c)
		{
			Coordinate leftVal, rightVal;

			leftVal = p2 - p1;
			rightVal = p1 - c;

			double dotProduct = (leftVal.getPosX() * rightVal.getPosX()) + 
				(leftVal.getPosY() * rightVal.getPosY());

			return -(dotProduct / (leftVal.cartesian() *  leftVal.cartesian()));
		}

		__declspec(deprecated) bool isCityCoveredWithEdge(City &objCity, Edge &objEdge)
		{
			// Linear equations : y - y' = m(x - x')

			int m = 0;

			if ((objEdge.getStartPoint().getPosX() - objEdge.getEndPoint().getPosX()) != 0)
			{
				m = (objEdge.getStartPoint().getPosY() - objEdge.getEndPoint().getPosY()) /
					(objEdge.getStartPoint().getPosX() - objEdge.getEndPoint().getPosX());
			}
			else if (objEdge.getStartPoint().getPosY() - objEdge.getEndPoint().getPosY() == 0)
				m = 0;
			else
				m = INFINITY;

			/*	Circle equation : (y - y')^2 + (x - x')^2 = R^2
			Intersection equation : Circle equation = Linear equations

			... some mach works => result :

			x^2(m^2 + 1) + x(2d -2mc - 2(m^2)b) + ( ((m^2)(b^2))  + a^2 + d^2 + c^2 + 2mbc - 2mab - 2ac - R^2 ) = 0

			try to solve and find x :

			a = start point y0 for line
			b = start point x0 for line
			c = center point y0 for circle
			d = center point x0 for circle

			da = (m^2 + 1)
			db = (2d -2mc - 2(m^2)b)
			dc = ((m^2)(b^2))  + a^2 + d^2 + c^2 + 2mbc - 2mab - 2ac - R^2

			delta = db^2 - 4da*dc

			if( delta >= 0 )
			it has intersection (true)
			else
			it hasn't intersection (false)
			*/

			if (m != INFINITY)
			{
				float a = objEdge.getStartPoint().getPosY(), b = objEdge.getStartPoint().getPosX();
				float c = objCity.getPosY(), d = objCity.getPosX();

				float da = (m * m) + 1;
				float db = (2 * d) - (2 * m  *c) - (2 * b * (m * m));
				float dc = ((m * m) * (b * b)) + (a * a) + (d * d) + (c * c) + (2 * m * b * c)
					- (2 * m * a * b) - (2 * a * c) - (objCity.getRadius() * objCity.getRadius());

				float delta = (db * db) - (4 * da * dc);

				if (delta >= 0)
					return true;
				else
					return false;
			}
			else
			{
				float circuleEquation = powf(objCity.getPosX() - objEdge.getStartPoint().getPosX(), 2) +
					powf(objCity.getPosY() - objEdge.getStartPoint().getPosY(), 2) - powf(objCity.getRadius(), 2);

				if (circuleEquation == 0)
					return true;
				else
					return false;
			}
		}

};

#endif
