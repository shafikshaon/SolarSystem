#ifndef RYAN_CAMERA_H
#define RYAN_CAMERA_H

class Camera
{
private:
	float forwardVec[3];
	float rightVec[3];
	float upVec[3];
	float position[3];

	float cameraSpeed;
	float cameraTurnSpeed;

public:
	Camera(void);

	void transformOrientation(void);

	void transformTranslation(void);

	void pointAt(float* targetVec);

	void speedUp(void);

	void slowDown(void);

	void forward(void);

	void left(void);

	void right(void);

	void backward(void);

	void rollRight(void);

	void rollLeft(void);

	void pitchUp(void);

	void pitchDown(void);

	void yawLeft(void);

	void yawRight(void);
};

#endif

