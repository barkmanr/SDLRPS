#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"
#include "TGAReader.h"

class Asset;

class Texture : public Resource
{
public:
	Texture();
	virtual ~Texture();

	Asset* GetData() { return m_texture; }
	ImageInfo* GetImageInfo() { return &m_imageInfo; }

	SDL_BlendMode GetBlendMode() { return m_blendMode; }
	void SetBlendMode(SDL_BlendMode _blendMode) { m_blendMode = _blendMode; }
	byte GetBlendAlpha() { return m_blendAlpha; }
	void SetBlendAlpha(byte _blendAlpha) { m_blendAlpha = _blendAlpha; }

	void Serialize(ostream& _stream) override;
	void Deserialize(istream& _stream) override;
	void ToString() override;
	void Load(string _guid);

	static ObjectPool<Texture>* Pool;

private:
	ImageInfo m_imageInfo;
	Asset* m_texture;

	SDL_BlendMode m_blendMode;
	byte m_blendAlpha;
};

#endif

