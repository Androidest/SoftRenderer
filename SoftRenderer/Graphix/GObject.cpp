#include "GObject.h"

GObject::GObject(const GMesh& _mesh, const Vector3f& pos, const Vector3f& rot, const Vector3f& _scale)
{
	vec3 p = vec3(pos.x, pos.y, pos.z);
	vec3 r = vec3(rot.x, rot.y, rot.z);
	vec3 s = vec3(_scale.x, _scale.y, _scale.z);
	set(_mesh, p, r, s);
}

GObject::GObject(const GMesh& _mesh, const vec3& pos, const vec3& rot, const vec3& _scale)
{
	set(_mesh, pos, rot, _scale);
}

void GObject::set(const GMesh& _mesh, const vec3& pos, const vec3& rot, const vec3& _scale)
{
	mesh = _mesh;
	setPosition(pos);
	setRotation(rot);
	setScale(_scale);
}

void GObject::setPosition(const vec3& pos) 
{
	position = pos;
	posTrans = translate(mat4(0.1f), position);
}

void GObject::setRotation(const vec3& rot)
{
	rotation = rot;
	rotTrans = rotate(mat4(0.1f), radians(rot.x), vec3(1.0f, 0.0f, 0.0f));
	rotTrans = rotate(rotTrans, radians(rot.y), vec3(0.0f, 1.0f, 0.0f));
	rotTrans = rotate(rotTrans, radians(rot.z), vec3(0.0f, 0.0f, 1.0f));
}

void GObject::setScale(const vec3& s) 
{
	scale = s;
	scaleTrans = glm::scale(mat4(0.1f), scale);
}

const vec3& GObject::getPosition() const { return position; }
const vec3& GObject::getRotation() const { return rotation; }
const vec3& GObject::getScale() const { return scale; }

void GObject::move(const vec3& delta) { position += delta; }

mat4 GObject::getModel() { return posTrans * rotTrans * scaleTrans; }

GMesh GObject::getMesh() { return mesh; }
