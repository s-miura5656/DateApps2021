#pragma once

#include "../../ESGLib.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	
	void RegisterParticle(EFFEKSEER& particle);
	void Draw();
    void Play();
	void PlayOneShot();
	void Stop();

	void SetPosition(Vector3 position);
	void SetRotation(Vector3 rotation);
	void SetScale(Vector3 scale);
	void SetScale(float scale);
	void SetSpeed(float speed);
	void SetColor(Color wirecolor);
	void SetNomalEffect();
private:
	//! file
	EFFEKSEER _particle;

	//! position
	Vector3 _position = Vector3_Zero;

	//! scale
	Vector3 _scale = Vector3_One;

	//! rotation
	Vector3 _rotation = Vector3_One;

	//! handle
	int _handle = INT_MAX;

	//! speed
	float _speed = 1.0f;

	Color _wire_color;
};