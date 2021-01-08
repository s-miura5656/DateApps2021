#include "Particle.h"

ParticleSystem::ParticleSystem()
{
	_particle = nullptr;
	_wire_color = Color(255, 255, 255);
}

ParticleSystem::~ParticleSystem()
{
	_particle->Stop(_handle);
//	Effekseer.ReleaseEffect(_particle);
}

void ParticleSystem::RegisterParticle(EFFEKSEER& particle)
{
	_particle = particle;
}

void ParticleSystem::Draw()
{
	_particle->SetPosition(_handle, _position);
	_particle->SetRotation(_handle, _rotation);
	_particle->SetScale(_handle, _scale);
	_particle->SetSpeed(_handle, _speed);
	_particle->SetColor(_handle, _wire_color);
}

void ParticleSystem::Play()
{
	_handle = _particle->Play(_position);
}

void ParticleSystem::PlayOneShot()
{
	if (_handle != INT_MAX)
		return;

	_handle = _particle->Play(_position);
}

void ParticleSystem::Stop()
{
	if (_handle == INT_MAX)
		return;

	_particle->Stop(_handle);
	_handle = INT_MAX;
}

void ParticleSystem::SetPosition(Vector3 position)
{
	_position = position;
}

void ParticleSystem::SetRotation(Vector3 rotation)
{
	_rotation.x = MathHelper_ToRadians(rotation.x);
	_rotation.y = MathHelper_ToRadians(rotation.y);
	_rotation.z = MathHelper_ToRadians(rotation.z);
}

void ParticleSystem::SetScale(Vector3 scale)
{
	_scale = scale;
}

void ParticleSystem::SetScale(float scale)
{
	_scale = Vector3_One * scale;
}

void ParticleSystem::SetSpeed(float speed)
{
	_speed = speed;
}

void ParticleSystem::SetColor(Color wirecolor)
{
	_wire_color = wirecolor;
}
