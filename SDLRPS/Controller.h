#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "StandardIncludes.h"

struct ControllerInfo
{
	SDL_JoystickID ID = -1;
	SDL_GameController* Contoller = nullptr;
	string Name;

	vector<SDL_GameControllerButton> Buttons;

	Position LeftAxis = {};
	Position RightAxis = {};

	string ToString()
	{
		string ButtonsString = "Buttons Down: ";
		for (unsigned int count = 0; count < Buttons.size(); count++)
		{
			ButtonsString += to_string(Buttons[count]) + "; ";
		}
		ButtonsString += " [LX: " + to_string(LeftAxis.X) + ", LY: " + to_string(LeftAxis.Y) + "] ";
		ButtonsString += " [RX: " + to_string(RightAxis.X) + ", RY: " + to_string(RightAxis.Y) + "] ";
		return ButtonsString;
	}
};

class Controller
{
public:
	Controller();
	virtual ~Controller();

	vector<ControllerInfo>& GetControllers() { return m_controllers; }

	void DetectControllers();
	bool Added(SDL_Event _event);
	bool Removed(SDL_Event _event);
	bool ProcessButtons(SDL_Event _event);
	bool ProcessMotion(SDL_Event _event);

	string ToString();

private:
	void Add(SDL_GameController* _controller);

	vector<ControllerInfo> m_controllers;
};

#endif

