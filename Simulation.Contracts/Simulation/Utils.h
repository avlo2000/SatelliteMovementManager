#pragma once
#include"Point.h"
#define SQR(x) pow(x, 2.0)

namespace Simulator
{
	inline double SqrDistance(Point p1, Point p2)
	{
		return SQR(p1.X() - p2.X()) + SQR(p1.Y() - p2.Y()) + SQR(p1.Z() - p2.Z());
	}

	inline double GetVecLength(Vector3d vec)
	{
		return sqrt(SQR(vec.x()) + SQR(vec.y()) + SQR(vec.z()));
	}

	inline Vector3d PrjVecOnVec(Vector3d prjVec, Vector3d targetVec)
	{
		double prjLen = (prjVec.transpose() * targetVec).sum() / GetVecLength(targetVec);
		double corrCoef = prjLen / GetVecLength(targetVec);
		return Vector3d(corrCoef * targetVec.x(), corrCoef * targetVec.y(), corrCoef * targetVec.z());
	}

	inline Vector3d InstSpeedFromImpuls(double mass, Vector3d currentSpeed, Vector3d force, double time)
	{
		Vector3d resultSpeed = (mass * currentSpeed - force * time) / mass;
		return resultSpeed;
	}

	inline double RotationSpeedFromRotImpuls(double inertMoment, Vector3d moment, double time)
	{
		double rotSpeed = inertMoment * GetVecLength(moment) * time;
		return rotSpeed;
	}

	inline Vector3d GetPerpendicularVec(Vector3d vec1, Vector3d vec2)
	{
		double y = -(vec2.z() / (vec2.y() - ((vec1.y() + vec1.z() / vec1.x()))));
		double x = -((y * vec1.y() + vec1.z()) / vec1.x());
		double z = 1;
		return Vector3d(x, y, z);
	}
}
