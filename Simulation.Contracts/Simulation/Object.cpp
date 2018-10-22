#pragma once
#include "Object.h"
#include "Utils.h"

namespace Simulator
{

	void Object::Init()
	{
		double mass = 0;
		double xSum = 0;
		double ySum = 0;
		double zSum = 0;
		this->_inertMoment = 0;

		for (auto mPoint : this->_mPoints)
		{
			mass += mPoint.GetMass();
			xSum += mPoint.GetMass() * mPoint.X();
			ySum += mPoint.GetMass() * mPoint.Y();
			zSum += mPoint.GetMass() * mPoint.Z();
		}


		this->_massCentre = MassPoint(mass, xSum / mass, ySum / mass, zSum / mass);

		for (auto mPoint : this->_mPoints)
			this->_inertMoment += mPoint.GetMass() * SqrDistance(this->_massCentre, mPoint);

	}

	Object::Object(vector<MassPoint> mPoints, vector<ForcePoint> fPoints)
	{
		this->_fPoints = fPoints;
		this->_mPoints = mPoints;

		this->Init();
	}

	Object::~Object()
	{
	}

}
