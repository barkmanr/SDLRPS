#ifndef SPRITEANIM_H
#define SPRITEANIM_H

#include "Resource.h"

class SpriteAnim : Resource
{
public:
	SpriteAnim();
	virtual ~SpriteAnim();

	short GetClipCurrent() { return (short)m_clipCurrent; }

	virtual void Serialize(ostream& _stream) override;
	virtual void Deserialize(istream& _stream) override;
	virtual void ToString() override;

	void ClearMemory();
	void Create(short _clipStart, short _clipCount, float _clipSpeed);
	void Update(float _deltaTime);
	void Reset();

	static ObjectPool<SpriteAnim>* Pool;

private:
	short m_clipStart;
	short m_clipCount;
	short m_clipEnd;
	float m_clipCurrent;
	float m_clipSpeed;

};

#endif
