#include "GPerspectiveCamera.h"
#include "GSoftRenderer.h"
#include "GTriangle.h"
#include "GLine.h"
#include <iostream>
using namespace std;

unsigned int *GSoftRenderer::buffer = NULL;

GSoftRenderer::GSoftRenderer(const int& w, const int& h, const string& name) :window(VideoMode(w, h), name) 
{
	width = 0;
	height = 0;
	initBuffer(w, h);
}

void GSoftRenderer::setCamera(GPerspectiveCamera* cam) { camera = cam; }
void GSoftRenderer::addChild(const string& name, GObject& obj) { objects[name] = &obj; }
void GSoftRenderer::removeChild(const string& name) { objects.erase(name); }

void GSoftRenderer::initBuffer(const int& w, const int& h)
{
	if (w == width && h == height) 
		return;
	width = w;
	height = h;
	bufSize = w * h * sizeof(unsigned int);
	delete buffer;
	buffer = new unsigned int[w*h];
	GLine::setBuffer(buffer, w, h);
}

void GSoftRenderer::render()
{
	vec4 clip;
	vec2 pixel1;
	vec2 pixel2;
	vec2 pixel3;
	Vector2u winSize = window.getSize();
	float w = (float)winSize.x*0.5f;
	float h = (float)winSize.y*0.5f;
	initBuffer(winSize.x, winSize.y);
	memset(buffer, 0, bufSize);

	mat4 finalCamTrans = camera->getProjectionTrans((float)width, (float)height) * camera->getViewTrans();
	for (std::map<string, GObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		GObject *obj = it->second;
		mat4 trans = finalCamTrans * obj->getModel();
		GMesh mesh = obj->getMesh();
		vec3* data = mesh.getData();
		Color* color = mesh.getColor();
		int size = mesh.getSize();
		
		for (int i(0); i < size; ++i)
		{
			clip = trans * vec4(data[i], 1.0f);
			pixel1 = vec2((clip.x / clip.w + 1) * w, (clip.y / clip.w + 1) * h);

			clip = trans * vec4(data[++i], 1.0f);
			pixel2 = vec2((clip.x / clip.w + 1) * w, (clip.y / clip.w + 1) * h);

			clip = trans * vec4(data[++i], 1.0f);
			pixel3 = vec2((clip.x / clip.w + 1) * w, (clip.y / clip.w + 1) * h);

			GTriangle triangle(pixel1, pixel2, pixel3, color[i]);
			triangle.drawOutLine();
		}
	}
	image.create(width, height, (unsigned char*)buffer);
	texture.loadFromImage(image);
	sprite.setTexture(texture, true);
	window.draw(sprite);
}

void GSoftRenderer::run()
{
	this->Start();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		this->Update();
		render();
		window.display();
	}
}