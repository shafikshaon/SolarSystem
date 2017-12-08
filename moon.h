#ifndef RYAN_MOON_H
#define RYAN_MOON_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>

class Moon
{
private:
	
	float distanceFromPlanet;

	
	float orbitTime;


	float rotationTime;

	
	float radius;

	
	GLuint textureHandle;

	
	float position[3];
	
	float rotation;

public:
	
	Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	
	void calculatePosition(float time);

	
	void render(void);

	
	void renderOrbit(void);
};

#endif
