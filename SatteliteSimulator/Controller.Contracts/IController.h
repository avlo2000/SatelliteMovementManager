#pragma once
#include "Object.h"

using namespace simulator;
using namespace std;

namespace contracts {

	template<typename T>
	class IController
	{
	protected:
		T *_obj;
	public:
		virtual void RegisterObject(T *obj)
		{
			_obj = obj;
		};
		virtual T* GetRegistration()
		{
			return _obj;
		};
		virtual void ControlRotation(Vector3d rotSpeed) = 0;
	};

}

