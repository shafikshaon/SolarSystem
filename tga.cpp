#include "tga.h"
#include <cstdio>
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>


#pragma pack(1)
struct TGAHeader{
    char    id_length;
    char    map_type;
    char    type;
    short   map_start;
    short   map_length;
    char    map_depth;
    short   x_origin;
    short   y_origin;
    short   width;
    short   height;
    char    bpp;
    char    descriptor_bits;
};
#pragma pack()

TGA::TGA(char* imagePath)
{
    FILE* file = NULL;
    TGAHeader header;
    char* pixels, *buffer;


    int c, r, i, j, bytespp = 4;
    char n, packet_header;
    char pixel[4];


    file = fopen(imagePath, "rb");


    fread(&header, 18, 1, file);

    bytespp = header.bpp / 8;

	pixels = (char*)malloc(bytespp * header.width * header.height);


    if (header.type == 2)
	{

        fseek(file, header.map_start + header.map_length * bytespp + 18, SEEK_SET);


        buffer = (char*)malloc(bytespp * header.width * header.height);
        fread(buffer, bytespp, header.width * header.height, file);


        for (c = 0; c < header.width; c ++)
		{
            for (r = 0; r < header.height; r ++)
			{
                if (bytespp == 4)
				{
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 0] =
                        buffer[(c + r * header.width) * bytespp + 2];
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 1] =
                        buffer[(c + r * header.width) * bytespp + 1];
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 2] =
                        buffer[(c + r * header.width) * bytespp + 0];
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 3] =
                        buffer[(c + r * header.width) * bytespp + 3];
                }
				else if (bytespp == 3)
				{
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 0] =
                        buffer[(c + r * header.width) * bytespp + 2];
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 1] =
                        buffer[(c + r * header.width) * bytespp + 1];
                    pixels[(c + (header.height - r - 1) * header.width) * bytespp + 2] =
                        buffer[(c + r * header.width) * bytespp + 0];
                }
            }
        }

        free(buffer);

    }
	else if (header.type == 10)
	{

        fseek(file, header.map_start + header.map_length * bytespp + 18, SEEK_SET);

        c = 0; r = header.height - 1;

        while (r >= 0)
		{

            fread(&packet_header, sizeof(packet_header), 1, file);

            n = packet_header & 0x7F;

            *((int*)pixel) = 0;
            if (n != packet_header)
                fread(&pixel, bytespp, 1, file);


            for (i = 0; i < n + 1; i++)
			{
                if (n == packet_header)
                    fread(&pixel, bytespp, 1, file);

                if (bytespp == 4)
				{
                    pixels[(c + r * header.width) * bytespp + 0] =
                        pixel[2];
                    pixels[(c + r * header.width) * bytespp + 1] =
                        pixel[1];
                    pixels[(c + r * header.width) * bytespp + 2] =
                        pixel[0];
                    pixels[(c + r * header.width) * bytespp + 3] =
                        pixel[3];
                }
				else if (bytespp == 3)
				{
                    pixels[(c + r * header.width) * bytespp + 0] =
                        pixel[2];
                    pixels[(c + r * header.width) * bytespp + 1] =
                        pixel[1];
                    pixels[(c + r * header.width) * bytespp + 2] =
                        pixel[0];
                }

                c += 1;
                if (c >= header.width)
				{
                    c = 0;
                    r -= 1;
                }
            }
        }
    }

    fclose(file);


	glGenTextures(1, &textureHandle);

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, header.width, header.height,
                   GL_RGB, GL_UNSIGNED_BYTE, pixels);


	free(pixels);
}

GLuint TGA::getTextureHandle(void)
{
	return textureHandle;
}


