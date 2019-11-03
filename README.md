# Problem Set 6

Start Date and Time| Due Date and Time | Cut-off Date and Time |
---|---|---|
10:50:00 AM on October 18, 2019 | 11:59:59 PM on October 3, 2019 | 12:00:00 AM on November 11, 2019 |

## Problem 6.1: PPM Image Format
We will be using a human-readable image file format called **PPM** (Netpbm color image format) for this problem set. Each pixel in PPM contains red, green, and blue (**RGB**), and each pixel represents color with a total of 24-bits. A 24-bit color uses 8-bits to signify the amount of red in a pixel’s color, 8-bits to signify the amount of green in a pixel’s color, and 8 bits to signify the amount of blue in a pixel’s color. If the R, G, and B values of some pixel in a PPM file are, say, 255, 0, and 0, that pixel is purely red, as 255 implies “a lot of red,” while 0 and 0 imply “no green” and “no blue,” respectively. 

Recall that computer files can be either a text or binary file. PPM file saved with an ASCII encoding is essentially a text file that you can open up in a text editor. Here is a sample content of a PPM file when opened in a text editor:

	P3
	4 4
	255
	17 17 17	255 0 0		59 59 59		0 0 255
	0 0 255		49 49 49	65 65 65		82 82 82
	59 59 59	0 255 0		255 255 255		89 89 89
	0 255 0		82 82 82	89 89 89		255 0 0

### Image Header
The first three lines of a PPM file contain the **header** information. They provide an overview of the contents of the image. The header information in the above example PPM file is:

	P3
	4 4
	255

- `P3` defines the **image format**, meaning what type of PPM (full color, ASCII encoding) image a file is in. For this problem set, this will always be P3.
- `4 4` describes the number of **columns** and the number of **rows** in the image. `4 4` means this PPM file has 4-pixel by 4-pixel image.
- `255` describes the **maximum color value** this image file can have for each color. If the value is 255, the red, green, and blue values for a pixel can range from 0 to 255. Stick to 255 for this problem set.
- The whitespaces, including new line, are essential, and you must follow the exact spacing protocol.

### Image Body
The **image body** starts right after the header information, and it is where the actual picture information is recorded as a series of RGB values. Each RGB value in the image body represents a pixel (colored square) in the picture. In other words, each pixel is defined by a triplet of values representing how much red, green, and blue (RGB) exist. The figure below demonstrates us how a mix of red, green, and blue can produce colors such as yellow, cyan, magenta, and white:

![Additive colour mixtures of blue, green and red to produce cyan, magenta, yellow and white](./img/KallColor3.jpg)

*Photo Credit: webvision.med.utah.edu.*

Following the example PPM file above, the first pixel has a value of 17 17 17 which translates to dark gray color. The last pixel in the image body is 255 0 0, which translates to red. In this way, by varying the levels of the RGB values, you can create different colors.

In the PPM file, color values must be separated by a space. The image viewer applications ignore any additional whitespace. The example PPM file above uses additional whitespaces to format the pixel values so that it is easy for us to read. The computers do not care if all RGB values are on one line, or if there is one line of RGB values per line of the image or some mixture of the two. Please never assume that one line in the file corresponds to one line in the image.

The example PPM file above would look like this when opened in the image view applications such as [GIMP](https://www.gimp.org/):

![Pixles](./img/pixels.png)

Please keep in mind that each square in the image is one pixel. The real image is much smaller, only containing 4 x 4 = 16 pixels. The image above is just for demonstration purpose, and it was blown up by 18000% to show you the actual pixel contents.

Please also keep in mind that While PPM files are easy to view as text, they are highly inefficient. Most modern image formats (png, jpg, gif, etc.) use some form of compression to reduce the amount of information stored while preserving the image appearance.

### Viewing PPM files
Please download and install [GIMP](https://www.gimp.org/) to view the PPM file. GIMP is a free and open-source raster graphics viewer/editor. GIMP can open, view, and edit PPM files. 

## Problem 6.2: White to Magenta Pixels
The following program will generate a PPM file with white image:

```C
	#include <stdio.h>

	const int WIDTH = 100;
	const int HEIGHT = 100;
	const int RGB = 3;

	int main(){
		unsigned char image[WIDTH][HEIGHT][RGB];
		// Open a text file in write mode
		FILE *fp = fopen("WhitePixels.ppm","w");
		// Write the header information
		fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT); 
		
		// Generate white pixels by going through 
		// each pixels and colors within pixels
		for(int x = 0; x < WIDTH; x++){
			for(int y = 0; y < HEIGHT; y++){
				for(int rgb = 0; rgb < RGB; rgb++){
					image[x][y][rgb] = 0xff; // 0xff is 255 in decimal
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
```
`unsigned` in front of `char` for the `image` array variable means that the number range should only be in the positive range. Therefore, `unsigned char` will only hold values between 0 ~ 255. 

The `image` variable is a three-dimensional array that holds the pixel information. The first dimension is for the **rows** of pixels represented with the `WIDTH` constant value. The second dimension is for the **columns** of pixels represented with the `HEIGHT` constant value. The third dimension is for the actual **RGB** color values represented with the `RGB` constant value. Remember that each pixel has RGB values (in 24-bits)? Computers need to know every single pixel values to be able to display that image for us correctly. This is the reason why we need a three-dimensional array to represent an image within C. 

Spend some time learning how the [`fprintf()`](http://www.cplusplus.com/reference/cstdio/fprintf/) function works in writing files in conjunction with `fopen()` and `fclose()`.

Modify this program to generate pixels with magenta instead of white. Think about RGB color space. What combination of red, green, and blue colors would produce magenta? How can we implement magenta in the for-loop we have above? Your C program for this problem should be called `ProblemSet6.2.c`.

The generated ppm file should look like this:  

![Magenta](./img/MagentaPixels.png)

## Problem Set 6.3: Flip an Image Horizontally
The following program will open a PPM file named "Gradient.ppm" and copies the pixel information into a three-dimensional array named `image`:

```C
#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 600;
const int HEIGHT = 600;
const int RGB = 3;

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
  return 0;
}
```
This program uses the `fscanf()` function to read the color values in the PPM file one at the time using three nested for-loops. The color values are then copied into the `image` variable.

Take the above program as a starting point for this problem and write a function called `flipHorizontal()` which will flip the image horizontally. In other words, the pixel that is on the far right end of the row ends up on the far left of the row and vice versa (remember to preserve RGB order!). The function prototype for `flipHorizontal()` should look like: 

	void flipHorizontal(unsigned char image[WIDTH][HEIGHT][RGB]);

This function must flip the pixels contained in the `image` three-dimensional array variable. After flipping the image horizontally, save the image to a file with the name `ReverseGradient.ppm`. Saving the file does not need to take place inside the `flipHorizontal()` function. Your C program for this problem set should be called `ProblemSet6.3.c`.

Here is how the "Gradient.ppm" looks like:
![Gradient](./img/Gradient.png)

After flipping the horizontal and saving the file, your PPM file should look like this:
![ReverseGradient](./img/ReverseGradient.png)

## Problem 6.4: Array and Pointer
Take the program you wrote in Problem 6.3 and save it as `Problemset6.4.c`. 

If you are feeling less comfortable, work on converting the three-dimensional array named `image` to a one-dimensional array to represent all the pixels. In C program, this means converting:

	unsigned char image[WIDTH][HEIGHT][RGB];

to:

	unsigned char image[WIDTH * HEIGHT * RGB];

The `image` array variable is now one-dimensional but carries the same number of pixels as it did before. The function prototype for `flipHorizontal()` function should now look like: 

	void flipHorizontal(unsigned char image[]);

The trickiest part of working on this problem is on how to correctly index the one-dimensional array and treat it like a three-dimensional array. Remember also that each pixel has three colors, RGB. 

If you are feeling more comfortable, work on converting the three-dimensional array named `image` to a pointer. In C program, this means converting:

	unsigned char image[WIDTH][HEIGHT][RGB];

to 

	unsigned char *image;

The `image` variable is now a pointer. Use `malloc()` to allocate an appropriate amount of memory space for the `image` variable (`WIDTH*HEIGHT*RGB*sizeof(unsigned char)`). Use [pointer arithmetic](https://www.tutorialspoint.com/cprogramming/c_pointer_arithmetic.htm) to access each pixel in the `image` pointer. Make sure to dereference the `image` variable to store or access the color values. The function prototype for `flipHorizontal()` function should now look like: 

	void flipHorizontal(unsigned char *image);

Even though we can treat a pointer like an array, please refrain from using square brackets (`[]`) to access the `image` variable for this problem.

## Grading Rubric
Description|Grade
---|---:|
Submitted all programs.|10%
No compilation warning or error on all programs.| 10%
Programs are clean, understandable, commented and organized. | 10%
Thoroughly documented in *README.md* what the programs do. | 20%
Correctly implemented all programs.| 50%
**Total** | **100%**

## Submission Guideline
- Create a new GitHub project with the right name and problem set number (e.g., `LMSC261-ProblemSet1`).
- Commit and push Scratch files for this problem set into the newly created project.
- Submit the link to the repository on OL to complete the problem set.

## Submission policy:
- All problem set must be first committed and pushed to your GitHub repository. 
- The link to your repository must be submitted to OL to complete the problem set.
- Late projects will incur a penalty of 10% each day.
- Problem sets and projects are due by 11:59:59 pm on the date specified
- After 12:00:00 am (the next day after the due day), your problem sets/projects is one day late (-10%).
- After the next 12: 00:00 am cycle (two days after the due day), your problem sets/projects is two days late (-20%).
- Problem sets and projects will not be accepted after 12:00:00 am at one week after the deadline

---  
**Berklee College of Music**    
Liberal Arts Department  
LMSC-261: Introduction to Computer Programming  
Fall 2019