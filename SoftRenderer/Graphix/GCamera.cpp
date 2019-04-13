#include "GCamera.h"

GCamera::GCamera(const vec3& dir, const vec3& _up) : GObject(GMesh())
{
	setDirection(position, dir, _up);
}

void GCamera::setAim(const vec3& _aim) { aim = _aim; front = normalize(aim - position); }
void GCamera::setUp(const vec3& _up) { up = _up; }
void  GCamera::setDirection(const vec3& pos, const vec3& dir, const vec3& _up)
{
	position = pos;
	front = normalize(dir);
	aim = position + front;
	up = _up;
}

void GCamera::moveByDirection(const vec3& delta)
{
	vec3 right = normalize(cross(front,up));
	move(front * delta.z + right * delta.x + up*delta.y);
	aim = position + front;
}

void GCamera::yawPitch(const vec2& delta)
{
	vec3 right = normalize(cross(front, up));
	mat4 pitch = glm::rotate(mat4(1.0f), radians(-delta.y), right);
	mat4 yaw = glm::rotate(mat4(1.0f),radians(delta.x),up);
	front = yaw * pitch * vec4(front,1);
	front = normalize(front);
	aim = position + front;
}

const vec3& GCamera::getAim() const { return aim; }
const vec3& GCamera::getUp() const { return up; }

mat4 GCamera::getViewTrans() { return mat4(1.0f) * lookAt(position, aim, up); }
