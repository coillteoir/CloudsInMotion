#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080

#define OUTPUT_FILE_PATH "output.ppm"

#define COLOUR_RED		0xFF0000FF
#define COLOUR_GREEN	0xFF00FF00
#define COLOUR_BLUE		0xFFFF0000
#define COLOUR_WHITE	0xFFFFFFFF
#define COLOUR_BLACK	0xFF000000

typedef uint32_t Colour32;

typedef struct dot
{
	uint32_t pX;
	uint32_t pY;
}Dot;

static Colour32 image[HEIGHT][WIDTH];

void fill_image(Colour32 colour)
{
	for(size_t y = 0; y < HEIGHT; y++)
	{
		for(size_t x = 0; x <WIDTH; x++)
		{
				image[y][x] = colour;
		}
	}
}

void rect(Colour32 colour, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	for(size_t baseY = y; baseY < y + h; baseY++)
	{
		for(size_t baseX = x; baseX < x + w; baseX++)
		{
			image[baseY][baseX] = colour;
		}
	}
}

void circle(Colour32 colour, uint32_t x, uint32_t y, uint32_t rad)
{
	uint32_t diam = 2 * rad;
	for(size_t baseY = y; baseY < y + diam; baseY++)
	{
		for(size_t baseX = x; baseX < x + diam; baseX++)
		{
			uint32_t bx = baseX - x - rad;
			uint32_t by = baseY - y - rad;

			if((bx * bx) + (by * by) <= rad * rad)
				if(baseX < WIDTH && baseY < HEIGHT)
					image[baseY][baseX] = colour;
		}
	}
}

void save_image_as_ppm(const char *file_path)
{
	FILE *f = fopen(file_path, "wb+");

	if(!f)
	{
		fprintf(stderr, "ERROR: FILE COULD NOT BE OPENED");
		exit(1);
	}

	fprintf(f,"P6\n%d %d 255\n", WIDTH, HEIGHT);
	for(size_t y = 0; y < HEIGHT; y++)
	{
		for(size_t x = 0; x <WIDTH; x++)
		{
			uint32_t pixel = image[y][x];	
			uint8_t bytes[3] = {
								//extract red
								(pixel&0x0000FF)>>8*0,
								//extract blue
								(pixel&0x00FF00)>>8*1,
								//extract green
								(pixel&0xFF0000)>>8*2,
							   };
			fwrite(bytes + 0, 1, 1, f);
			fwrite(bytes + 1, 1, 1, f);
			fwrite(bytes + 2, 1, 1, f);
		}
	}

	fclose(f);
}

int main()
{
	srand(time(NULL));
	Colour32 t = (Colour32) rand();
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			image[i][j] = (t + i) | (COLOUR_RED + j);


	save_image_as_ppm(OUTPUT_FILE_PATH);
	return 0;
}
