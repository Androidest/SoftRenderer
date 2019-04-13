#pragma once

#include "GObject.h"

class GShader;
class GWindow;

class GCamera : public GObject
{
protected:
	float nearClip;
	float farClip;
	vec3  aim;
	vec3  up;
	vec3  front;

public:
	GCamera(const vec3& _aim = vec3(0.0f, 0.0f, 1.f), const vec3& _up = vec3(0.0f, 1.0f, 0.0f));
	~GCamera() {}

	void setAim(const vec3& _aim);
	void setUp(const vec3& _up);
	void setDirection(const vec3& pos, const vec3& dir, const vec3& _up);

	void moveByDirection(const vec3& delta);
	void yawPitch(const vec2& delta);

	const vec3& getAim() const;
	const vec3& getUp() const;

	mat4 getViewTrans();
};
