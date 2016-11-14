#include <stdio.h>
#include "lodepng.h"

#include "lodepng.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define THRESHOLD 10
/*
3 ways to decode a PNG from a file to RGBA pixel data (and 2 in-memory ways).
*/

void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}


/*
Example 1
Decode from disk to raw pixels with a single function call
*/
void decodeOneStep(const char* filename)
{
  unsigned error;
  unsigned char* image;
  unsigned width, height;
   int i ,j;
  error = lodepng_decode32_file(&image, &width, &height, filename);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

 for (i = 1; i < height; i++)
 {
	 for (j = 1; j < width; j++)
	 {
		 //int sum = image[i * width + j
	 }
 }
  for ( i = 0 ; i < width * height*4 ; i += 4) {
		image[i + 1 ] = 0;
		image[i + 2] = 0;
		
  }

  encodeOneStep("LennaRed.png",image,width,height);
  /*use image here*/

  free(image);
}


unsigned char* grayscale(unsigned char* image, unsigned int width, unsigned int height)
{
	unsigned char *grayscaleImage = malloc(width * height * sizeof(unsigned char));
	int i;
	
	for (i = 0; i < width * height * 4; i += 4)
	{
		grayscaleImage[i / 4] = (unsigned char)(0.21f * image[i] + 0.72f * image[i + 1] + 0.072f * image[i + 2]);
	}
	
	return grayscaleImage;
}

unsigned char* detectEdges(unsigned char* image, unsigned int width, unsigned int height)
{
	unsigned char *edges = calloc(width * height, sizeof(unsigned char));
	
	int i, j;
	int result = 0;
	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			int currentPixel = i * width + j;
			result = abs(8 * image[currentPixel] - image[currentPixel - 1] - image[currentPixel + 1] -
					image[currentPixel + width] - image[currentPixel - width] - image[currentPixel + width - 1] -
					image[currentPixel + width + 1] - image[currentPixel - width - 1] - image[currentPixel - width + 1]) / 8;
					
			if (result > THRESHOLD) 
			{
				edges[currentPixel] = 1;
			}
		}
	}
	
	return edges;
}

unsigned char* erode(unsigned char* edges, unsigned int width, unsigned int height)
{
	int i, j;
	unsigned char *eroded = calloc(width * height, sizeof(unsigned char));
	
	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			int currentPixel = i * width + j;
			
			if (edges[currentPixel - 1] == 1 && edges[currentPixel + 1] == 1 &&
				edges[currentPixel + width] == 1 && edges[currentPixel - width] == 1)
				{
					eroded[currentPixel] = 1;
				}
		}
	}
	
	return eroded;
}

unsigned char* dilate(unsigned char* edges, unsigned int width, unsigned int height)
{
	int i, j;
	unsigned char *dilated = calloc(width * height, sizeof(unsigned char));
	
	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			int currentPixel = i * width + j;
			
			if (edges[currentPixel - 1] == 1 || edges[currentPixel + 1] == 1 ||
				edges[currentPixel + width] == 1 || edges[currentPixel - width] == 1)
				{
					dilated[currentPixel] = 1;
				}
		}
	}
	
	return dilated;
}

void writeEdges(unsigned char* edges, unsigned int width, unsigned int height)
{
	unsigned char *image = malloc(width * height * 4 * sizeof(unsigned char));
	int i;
	for (i = 0; i < width * height * 4; i += 4)
	{
		if (edges[i / 4] == 0)
		{
			image[i] = 0;
			image[i + 1] = 0;
			image[i + 2] = 0;
		}
		else if (edges[i / 4] == 1)
		{
			image[i] = 255;
			image[i + 1] = 255;
			image[i + 2] = 255;
		}
		
		image[i + 3] = 255;
	}
	
	encodeOneStep("fruitsedge.png", image, width, height);
	free(image);
}


int main(){
	//decodeOneStep("fruits.png");
	unsigned error;
	unsigned char* image;
	unsigned width, height;
	int i ,j;
	error = lodepng_decode32_file(&image, &width, &height, "fruits.png");
	if(error) 
		printf("error %u: %s\n", error, lodepng_error_text(error));
	
	unsigned char* grayscaleIm = grayscale(image, width, height);
	unsigned char* edges = detectEdges(grayscaleIm, width, height);
	
	//unsigned char* eroded = erode(edges, width, height);
	
	//unsigned char* dilated = dilate(eroded, width, height);
	
	/* for (i = 0; i < 2; i++)
	{
		dilated = dilate(dilated, width, height);
	} */
	
	writeEdges(edges, width, height);
	//encodeOneStep("LennaGray.png",grayscaleIm,width,height);
	
}