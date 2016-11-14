#include <stdio.h>
#include "lodepng.h"

#include "lodepng.h"

#include <stdio.h>
#include <stdlib.h>

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

 
  for ( i = 0 ; i < width * height*4 ; i += 4) {
		image[i + 1 ] = 0;
		image[i + 2] = 0;
		
  }

  encodeOneStep("LennaRed.png",image,width,height);
  /*use image here*/

  free(image);
}



int main(){
	decodeOneStep("Lenna.png");
}