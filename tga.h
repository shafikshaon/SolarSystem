#ifndef RYAN_TGA_H
#define RYAN_TGA_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>


class TGA
{
private:
	
	GLuint textureHandle;
public:
	
	TGA(char* imagePath);

	
	GLuint getTextureHandle(void);
};

#endif
