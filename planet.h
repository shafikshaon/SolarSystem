#ifndef RYAN_PLANET_H
#define RYAN_PLANET_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <vector>
#include "moon.h"

class Planet
{
private:
	float distanceFromSun;

	float orbitTime;

	float rotationTime;

	float radius;

	GLuint textureHandle;

	float position[3];
	float rotation;

	std::vector<Moon> moons;

public:

	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	void calculatePosition(float time);

	void render(void);

	void renderOrbit(void);

	void getPosition(float* vec);

	float getRadius(void);

	void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
};

#endif

