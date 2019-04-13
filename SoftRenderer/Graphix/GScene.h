#pragma once
#include "GSoftRenderer.h"

class GScene : public GSoftRenderer
{
private:
	GMesh mesh;
	GObject cube;
	GPerspectiveCamera camera;

public:
	GScene() : GSoftRenderer(1000, 700, "Stephen") {}

	virtual void Start()
	{
		mesh = GMesh("cube.mesh");
		cube = GObject(mesh);		
		camera.setPosition(vec3(0, 0, -3));

		setCamera(&camera);
		addChild("cube", cube);
	}

	virtual void Update()
	{
		cube.setRotation(cube.getRotation() + vec3(0.2, 0.4, 0));
	}
};
