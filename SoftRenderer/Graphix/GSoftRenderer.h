#pragma once

#include <map>
#include <SFML\Graphics.hpp>
using namespace std;
using namespace sf;

class GPerspectiveCamera;
class GObject;

class GSoftRenderer
{
private:
	int width;
	int height;
	RenderWindow window;

	int bufSize;
	static unsigned int *buffer;
	Image image;
	Texture texture;
	Sprite sprite;

	map<string, GObject*> objects;
	GPerspectiveCamera *camera;

public:
	GSoftRenderer(const int& w, const int& h, const string& name);
	virtual void Start() = 0;
	virtual void Update() = 0;

	void initBuffer(const int& w, const int& h);
	void setCamera(GPerspectiveCamera* cam);
	void addChild(const string& name, GObject& obj);
	void removeChild(const string& name);

	void render();

	void run();
};