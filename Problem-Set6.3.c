#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 600;
const int HEIGHT = 600;
const int RGB = 3;

void flipHorizontal(unsigned char image[WIDTH][HEIGHT][RGB]);

int main(){
  unsigned char image[WIDTH][HEIGHT][RGB];
  unsigned char ctmp;
  int x,y,i;
  
  FILE *fp;
  if((fp=fopen("Gradient.ppm","r"))==NULL){
    printf("File does not exist or corrupted.\n");
    return 1;
  }

  fscanf(fp,"P3\n600 600\n255\n"); //Skip reading the header file

  //Get colors for each pixel
  unsigned int color;
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      for(int rgb = 0; rgb < RGB; rgb++){
        fscanf(fp, "%u", &color);
        image[x][y][rgb] = color;
      }
    }
  }

  fclose(fp);

  
  flipHorizontal(image);

  fp = fopen("ReversedGradient.ppm", "w");

  fprintf(fp,"P3\n%d %d\n255\n", WIDTH, HEIGHT);

  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
        for(int rgb = 0; rgb < RGB; rgb++){
            fprintf(fp, "%i ", image[x][y][rgb]);
        }
    }
  }

  fclose(fp);
  return 0;
}

void flipHorizontal(unsigned char image[WIDTH][HEIGHT][RGB]){
    unsigned char save;
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH/2; j++){
            for(int rgb = 0; rgb < RGB; rgb++){
                save = image[i][WIDTH-j-1][rgb];
                image[i][WIDTH-j-1][rgb] = image[i][j][rgb];
                image[i][j][rgb]= save;
            }
        }
    }

}