#include "Particle.h"

ParticleSystem::ParticleSystem()
{
	_particle = nullptr;
}

ParticleSystem::~ParticleSystem()
{

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
	_rotation = rotation;
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

void ParticleSystem::SetDrawRotationY(float angle_y, Vector3 front_dir)
{
	if (front_dir.z != 0)
	{
		_rotation = Vector3(MathHelper_ToDegrees(angle_y + 180), 0.0f, 0.0f);
	}
	else if (front_dir.x > 0)
	{
		_rotation = Vector3(0.0, 0.0f, MathHelper_ToDegrees(angle_y + 180));
	}
	else if (front_dir.x < 0)
	{
		_rotation = Vector3(0.0, 0.0f, MathHelper_ToDegrees(angle_y + 90));
	}
}
