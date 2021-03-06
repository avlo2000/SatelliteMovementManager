#pragma once
#include "Point.h"

namespace simulator
{

	class MassPoint : public Point
	{
	private:
		double _mass; // [kg]
	public:
		explicit MassPoint()
			: Point()
		{
			this->_mass = 0;
		}
		explicit MassPoint(double mass, double x, double y, double z)
			: Point(x, y, z)
		{
			this->_mass = mass;
		};
		double GetMass();
		~MassPoint();
	};

}

