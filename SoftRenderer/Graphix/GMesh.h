#pragma once

#include<string>
#include"glm.hpp"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace glm;
using namespace sf;

class GMesh
{
private:
	vec3 *data;
	Color *color;
	int size;
	
public:
	GMesh();
	GMesh(const string& filename);
	bool set(const string& filename);
	Color* getColor();
	vec3* getData();
	int getSize();
};

