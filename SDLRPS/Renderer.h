#ifndef RENDERER_H
#define RENDERER_H

#include "StandardIncludes.h"
#include "Texture.h"

class Asset;


class Renderer : public Singleton<Renderer>
{
public:
	Renderer();
	virtual ~Renderer();

	SDL_Window* GetWindow() { return m_window; }
	SDL_Renderer* GetRenderer() { return m_renderer; }
	SDL_Texture* GetSDLTexture(Texture* _texture);

	vector<SDL_DisplayMode>& GetResoulution() { return m_resolutions; }

	void Initialize(int _xResolution, int _yResolution);
	void Initialize();
	void EmumerateDisplayModes();
	void ChangeDisplayMode(SDL_DisplayMode* _mode);

	void SetDrawColor(Color _color);
	void ClearScreen();
	void Shutdown();


	void RenderPoint(Point _position);
	void RenderLine(Rect _points);
	void RenderRectangle(Rect _rect);
	void RenderFillRectangle(Rect _rect);

	void RenderTexture(Texture* _texture, Point _point);
	void RenderTexture(Texture* _texture, Rect _rect);
	void RenderTexture(SDL_Texture* _texture, Rect _srcRect, Rect _destRect, double _angle);

	Point GetWindowSize();
	void SetViewport(Rect _viewport);

	void RenderTexture(Texture* _texture, Rect _srcRect, Rect _destRect, int _alpha = 255);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Rect m_destRect;
	SDL_Surface* m_surface;
	map<string, SDL_Texture*> m_textures;

	SDL_Rect m_viewPort;
	SDL_Rect m_srcRect;

	vector<SDL_DisplayMode> m_resolutions;

};

#endif RENDERER_H

