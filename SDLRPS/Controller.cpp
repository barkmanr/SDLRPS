#include "Controller.h"

Controller::Controller() {}
Controller::~Controller() {}

void Controller::DetectControllers()
{
	m_controllers.clear();
	int numControllers = SDL_NumJoysticks();

	for (int count = 0; count < numControllers; count++)
	{
		if (!SDL_IsGameController(count)) continue;
		Add(SDL_GameControllerOpen(count));
	}
}

void Controller::Add(SDL_GameController* _controller)
{
	if (_controller == nullptr)  return;

	SDL_Joystick* j = SDL_GameControllerGetJoystick(_controller);
	SDL_JoystickID jID = SDL_JoystickInstanceID(j);
	for (ControllerInfo c : m_controllers)
	{
		if (c.ID == jID) return;
	}

	ControllerInfo c = ControllerInfo();
	c.Contoller = _controller;
	c.Name = string(SDL_GameControllerName(_controller));
	c.ID = jID;
	m_controllers.push_back(c);
}

bool Controller::Added(SDL_Event _event)
{
	if (_event.type != SDL_CONTROLLERDEVICEADDED) return false;

	if (SDL_IsGameController(_event.cdevice.which))
	{
		SDL_GameController* controller = SDL_GameControllerOpen(_event.cdevice.which);
		Add(controller);
	}
	return true;
}

bool Controller::Removed(SDL_Event _event)
{
	if (_event.type != SDL_CONTROLLERDEVICEREMOVED) return false;

	for (unsigned int count = 0; count < m_controllers.size(); count++)
	{
		if (m_controllers[count].ID != _event.cdevice.which) continue;// might be wrong
		m_controllers.erase(m_controllers.begin() + count);
		break;
	}

	return true;
}

string Controller::ToString()
{
	int cc = 0;
	string s = "Controller: ";
	for (ControllerInfo c : m_controllers)
	{
		cc++;
		s += to_string(cc) + " - " + c.Name + ": ";
		s += c.ToString();
	}
	return s;
}

bool Controller::ProcessButtons(SDL_Event _event)
{
	if (_event.type == SDL_CONTROLLERBUTTONDOWN)
	{
		for (unsigned int count = 0; count < m_controllers.size(); count++)
		{
			if (m_controllers[count].ID != _event.cdevice.which) continue; //wrong??
			auto v = m_controllers[count].Buttons;
			if (find(v.begin(), v.end(), _event.cbutton.button) == v.end())
			{
				m_controllers[count].Buttons.push_back(SDL_GameControllerButton(_event.cbutton.button));
			}
			break;
		}
		return true;
	}

	else if (_event.type == SDL_CONTROLLERBUTTONUP)
	{
		for (unsigned int count = 0; count < m_controllers.size(); count++)
		{
			vector<SDL_GameControllerButton>* v = &m_controllers[count].Buttons;
			for (unsigned int button = 0; button < v->size(); button++)
			{
				if ((*v)[button] == _event.cbutton.button)
				{
					v->erase(v->begin() + button);
					break;
				}
			}
		}
		return true;
	}
	return false;
}

bool Controller::ProcessMotion(SDL_Event _event)
{
	if (_event.type != SDL_CONTROLLERAXISMOTION) return false;

	for (unsigned int count = 0; count < m_controllers.size(); count++)
	{
		if (m_controllers[count].ID != _event.cdevice.which) continue; //?

		if (_event.caxis.axis == 0)
		{
			m_controllers[count].LeftAxis.X = _event.caxis.value;
		}

		else if (_event.caxis.axis == 1)
		{
			m_controllers[count].LeftAxis.Y = _event.caxis.value;
		}

		if (_event.caxis.axis == 2)
		{
			m_controllers[count].RightAxis.X = _event.caxis.value;
		}

		else if (_event.caxis.axis == 3)
		{
			m_controllers[count].RightAxis.Y = _event.caxis.value;
		}
	}
	return true;
}
