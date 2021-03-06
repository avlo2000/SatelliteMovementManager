#include "Satellite.h"

namespace simulator
{
	void Satellite::Init()
	{
		//start impuls is not included [Imp1 + Imp2 = 0]
		double rotImpX = 0;
		double rotImpY = 0;
		double rotImpZ = 0;

		for (int index = 0; index < _reactionWheels.size(); index++)
		{
			rotImpX -= _reactionWheels[index].GetMomentumImpuls().x();
			rotImpY -= _reactionWheels[index].GetMomentumImpuls().y();
			rotImpZ -= _reactionWheels[index].GetMomentumImpuls().z();
		}


		this->_rotationX.AngleSpeed = rotImpX / this->_inertiaX;
		this->_rotationY.AngleSpeed = rotImpY / this->_inertiaY;
		this->_rotationZ.AngleSpeed = rotImpZ / this->_inertiaZ;
		Wobble();
	}
	void Satellite::Wobble()
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator(seed);

		if (this->_wobbling != 0)
		{
			normal_distribution<double> distribution(0.0, this->_wobbling);

			this->_rotationX.AngleSpeed += distribution(generator);
			this->_rotationY.AngleSpeed += distribution(generator);
			this->_rotationZ.AngleSpeed += distribution(generator);
		}
	}
	Satellite::Satellite(string name, vector<MassPoint>& mPoints, vector<ReactionWheel>& wheels)
		: Object(name, mPoints)
	{
		this->_reactionWheels = wheels;
		this->_wobbling = 0;
		this->_mPoints.insert(this->_mPoints.end(), this->_reactionWheels.begin(), this->_reactionWheels.end());
		Object::Init();
	}

	vector<double> Satellite::GetWheelsEnergies()
	{
		vector<double> res;
		for (auto wheel : this->_reactionWheels)
			res.push_back(wheel.GetEnergy());
		return res;
	}

	double Satellite::GetWheelSpeed(int index) {
		return this->_reactionWheels[index].GetSpeed();
	}

	void Satellite::EnergyToReactionWheel(int index, double work)
	{
		this->_reactionWheels[index].PowerToWheel(work);

		Init();
	}



	void Satellite::SetWobbling(double wobbling)
	{
		this->_wobbling = wobbling;
	}

	void Satellite::Rotate(double time)
	{
		Object::Rotate(time);

		for (auto wheel = this->_reactionWheels.begin(); wheel < this->_reactionWheels.end(); wheel++)
		{
			(*wheel).SetRotation(this->_rotationX.AxisVector, this->_rotationX.AxisPoint, this->_rotationX.AngleSpeed);
			(*wheel).Rotate(time);

			(*wheel).SetRotation(this->_rotationY.AxisVector, this->_rotationY.AxisPoint, this->_rotationY.AngleSpeed);
			(*wheel).Rotate(time);

			(*wheel).SetRotation(this->_rotationZ.AxisVector, this->_rotationZ.AxisPoint, this->_rotationZ.AngleSpeed);
			(*wheel).Rotate(time);
		}
	}

	int Satellite::GetNumOfWheels() {
		return this->_reactionWheels.size();
	}

	Satellite::~Satellite()
	{
	}

	//void Satellite::RegisterControl(IController<Object>* simulator)
	//{
	//	this->_controller->RegisterObject(this);
	//}

	//void Satellite::Control(Vector3d instSpeed, Vector3d rotSpeed)
	//{
	//	this->_controller->ControlRotation(rotSpeed);
	//}

}
