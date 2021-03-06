#include "ReactionWheel.h"
#include "Utils.h"

namespace simulator {

	void ReactionWheel::Init()
	{
		this->_rotAxes.normalize();
		this->_rotImpuls = this->_speed * this->_inertia * this->_rotAxes;
	}

	ReactionWheel::ReactionWheel(double mass, double x, double y, double z, Vector3d rotAxes, double radius)
		: MassPoint(mass, x, y, z)
	{
		this->_inertia = mass * SQR(radius) / 2;
		this->_rotAxes = rotAxes;
		this->_speed = 0;
		this->_frictionCoef = 0;
		Init();
	}

	double ReactionWheel::GetSpeed()
	{
		return this->_speed;
	}

	double ReactionWheel::GetEnergy()
	{
		return this->_inertia * SQR(this->_speed) / 2;
	}

	void ReactionWheel::PowerToWheel(double work)
	{
		work = -work;
		auto kinetic = this->_inertia * SQR(this->_speed) / 2;
		auto rest = kinetic - abs(work);

		if(work > 0 && _speed >= 0)
		{ 
			this->_speed = sqrt(abs(SQR(this->_speed) + 2 * abs(work) / this->_inertia));
			this->Init();
			return;
		}
		if (work < 0 && _speed > 0)
			if (rest > 0)
			{
				this->_speed = sqrt(2 * abs(rest) / this->_inertia);
				this->Init();
				return;
			}
			else
			{
				this->_speed = -sqrt(2 * abs(rest) / this->_inertia);
				this->Init();
				return;
			}
		if(work < 0 && _speed <= 0)
		{ 
			this->_speed = -sqrt(abs(SQR(this->_speed) + 2 * abs(work) / this->_inertia));
			this->Init();
			return;
		}
		if (work > 0 && _speed < 0)
			if (rest > 0)
			{ 
				this->_speed = -sqrt(2 * abs(rest) / this->_inertia);
				this->Init();
				return;
			}
			else
			{ 
				this->_speed = sqrt(2 * abs(rest) / this->_inertia);
				this->Init();
				return;
			}
	}

	void ReactionWheel::SetFrictionCoef(double friction)
	{
		this->_frictionCoef = friction;
	}

	void ReactionWheel::SetRotation(Vector3d axesVector, Point axesPoint, double rotSpeed)
	{
		this->axesVector = axesVector;
		this->axesPoint = Vector3d(axesPoint.X(), axesPoint.Y(), axesPoint.Z());
		this->rotSpeed = rotSpeed;
	}

	Vector3d ReactionWheel::GetMomentumImpuls()
	{
		return this->_rotImpuls;
	}

	ReactionWheel::~ReactionWheel()
	{
	}
	void ReactionWheel::Rotate(double time)
	{
		MassPoint::Rotate(time);

		double angle = this->rotSpeed * time;

		this->_rotAxes = RotateVector(this->_rotAxes, this->axesVector, Point(0, 0, 0), angle);

		//TO DO(include friction)
	}
}