#pragma once

#include "GMesh.h"
#include "gtc/matrix_transform.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;

class GObject
{
protected:
	GMesh mesh;

	vec3 position;
	vec3 rotation;
	vec3 scale;

	mat4 posTrans;
	mat4 rotTrans;
	mat4 scaleTrans;

public:
	GObject() {}

	GObject(const GMesh& _mesh,
			const Vector3f& pos = Vector3f(0, 0, 0),
			const Vector3f& rot = Vector3f(0, 0, 0),
			const Vector3f& _scale = Vector3f(1, 1, 1));

	GObject(const GMesh& _mesh, const vec3& pos, const vec3& rot, const vec3& _scale);

	void set(const GMesh& _mesh, const vec3& pos, const vec3& rot, const vec3& _scale);

	void setPosition(const vec3& pos);
	void setRotation(const vec3& rot);
	void setScale(const vec3& s);

	const vec3& getPosition() const;
	const vec3& getRotation() const;
	const vec3& getScale() const;

	void move(const vec3& delta);

	mat4 getModel();
	
	GMesh getMesh();
};
