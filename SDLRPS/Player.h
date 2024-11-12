#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerState.h"
#include "Resource.h"

class SpriteSheet;
class Renderer;
class TTFont;

class Player : Resource
{
public:
	Player();
	virtual ~Player();

	PlayerState* GetState() { return m_state; }
	void SetState(PlayerState* _state) { m_state = _state; }
	SpriteSheet* GetAnimations() { return m_animations; }
	Rect* GetSrcRect() { return &m_srcRect; }
	void SetPosition(glm::vec2 _pos) { m_position = _pos; }
	glm::vec2 GetPosition() { return m_position; }
	void setName(string _name) { m_name = _name; }
	string getName() { return m_name; }
	void setStatus(string _state) { m_status = _state; }
	void addWin() { m_wins++; }
	void addLoss() { m_losses++; }
	void setRoll(int _role) { roll = _role; }
	int getRoll() { return roll; }
	void SetVert(float _set) { m_moveVert = _set; }
	void SetHor(float _set) { m_moveHor = _set; }


	virtual void HandleInput(SDL_Event _event, float _deltaTime);
	virtual void Update(float _deltaTIme,Point ws);
	virtual void Render(Renderer* _render,TTFont* _font);

	void CheckWin(Player* _other);

	void Serialize(ostream& _stream) override;
	void Deserialize(istream& _stream) override;

private:
	PlayerState* m_state;
	SpriteSheet* m_animations;
	Rect m_srcRect;
	glm::vec2 m_position;
	string m_name; //won't save, name should be the same
	int roll;
	string m_status;
	unsigned int m_wins;
	unsigned int m_losses;
	float m_moveVert; //Wont save as you can lose key up ability
	float m_moveHor;
};

#endif

