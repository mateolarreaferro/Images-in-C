#include <stdio.h>

	const int WIDTH = 100;
	const int HEIGHT = 100;
	const int RGB = 3;

	int main(){
		unsigned char image[WIDTH][HEIGHT][RGB];
		// Open a text file in write mode
		FILE *fp = fopen("Megenta.ppm","w");
		// Write the header information
		fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT); 
		unsigned char magenta[RGB]= {255, 0, 255};
		// Generate white pixels by going through 
		// each pixels and colors within pixels
		for(int x = 0; x < WIDTH; x++){
			for(int y = 0; y < HEIGHT; y++){
				for(int rgb = 0; rgb < RGB; rgb++){
					image[x][y][rgb] = magenta[rgb]; 

				}
			}
		}

		// Write out individual pixels to the file
		for(int x = 0; x < WIDTH; x++){
			for(int y = 0; y < HEIGHT; y++){
				for(int rgb = 0; rgb < RGB; rgb++){
					fprintf(fp, "%i ", image[x][y][rgb]);
				}
			}
		}
		
		fclose(fp); // Close the file
		return 0;
	}