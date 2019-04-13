#pragma once

#include "GCamera.h"

class GPerspectiveCamera : public GCamera
{
protected:
	float fov;

public:
	~GPerspectiveCamera() {}
	GPerspectiveCamera(const float& _fov = 45.0f,
					   const float& _nearClip = 0.1f,
					   const float& _farClip = 100.0f);
	
	void setFov(const float& _fov);
	void setView(const float& _fov, const float& near, const float& far);

	const float& getFov() const;

	mat4 getProjectionTrans(const float& width, const float& height);
};
