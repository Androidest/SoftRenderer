#include "GPerspectiveCamera.h"

GPerspectiveCamera::GPerspectiveCamera(const float& _fov, const float& _nearClip, const float& _farClip) : GCamera()
{
	setView(_fov, _nearClip, _farClip);
}

void GPerspectiveCamera::setFov(const float& _fov) { fov = _fov; }

void GPerspectiveCamera::setView(const float& _fov, const float& _nearClip, const float& _farClip)
{
	fov = _fov;
	nearClip = _nearClip;
	farClip = _farClip;
}

const float& GPerspectiveCamera::getFov() const { return fov; }

mat4 GPerspectiveCamera::getProjectionTrans(const float& width, const float& height)
{ 
	return mat4(1.0f) * perspective(fov, width/height, nearClip, farClip);
}