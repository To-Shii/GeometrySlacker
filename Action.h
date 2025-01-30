#pragma once
#include "CoreMinimal.h"
namespace Input
{
	typedef optional<Event> EventInfo;

	enum ControllerButtonsType
	{
		Cross,
		Circle,
		Triangle,
		Square,
		L1,
		R1,
		L2,
		R2,
		LeftStick,
		RightStick,
	};

	enum ControllerAxesType
	{
		LeftStickX,
		LeftStickY,
		RightStickX,
		RightStickY,
	};


	enum ValueType
	{
		Digital, //bool
		Axis,	 //float
		Axis2,	 //Vector2f
	};


	struct ActionData
	{
		ValueType value;
		type_index trigger;
	};

	class Action
	{
		string name;
		ActionData data;
		set<int> inputs;
		function<void()> callback;

	public: 
		void TryToExecute(const EventInfo& _event);
	};
}