#pragma once
#include "Action.h"

namespace Input
{

	class ActionMap
	{
		bool isActive;
		string name;
		map<string, Action*> actions;

	public:
		ActionMap();

	public:
		void Update(const EventInfo& _event);
	};
}