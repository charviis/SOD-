/*
 * Programming introduction with the SOD Embedded Image Processing API.
 * Copyright (C) PixLab | Symisc Systems, https://sod.pixlab.io
 */
/*
* Compile this file together with the SOD embedded source code to generate
* the executable. For example:
*
*  gcc sod.c hilditch_thin.c -lm -Ofast -march=native -Wall -std=c99 -o sod_img_proc
*  
* Under Microsoft Visual Studio (>= 2015), just drop `sod.c` and its accompanying
* header files on your source tree and you're done. If you have any trouble
* integrating SOD in your project, please submit a support request at:
* https://sod.pixlab.io/support.html
*/
/*
* This simple program is a quick introduction on how to embed and start
* experimenting with SOD without having to do a lot of tedious
* reading and configuration.
*
* Make sure you have the latest release of SOD from:
*  https://pixlab.io/downloads
* The SOD Embedded C/C++ documentation is available at:
*  https://sod.pixlab.io/api.html
*/
#include <stdio.h>
#include "sod.h"
/*
 * Perform Hilditch thinning on an input image.
 *
 * Skeletonization is useful when we are interested not in the size of the pattern but rather
 * in the relative position of the strokes in the pattern (Character Recognition,
 *  X, Y Chromosome Recognition, etc.).
 * The target image must be binary (i.e. images whose pixels have only two possible intensity
 * value mostly black or white). You can obtain a binary image via sod_canny_edge_image(),
 * sod_otsu_binarize_image(), sod_binarize_image() or sod_threshold_image(). 
 */
int main(int argc, char *argv[])
{
	/* Input image (pass a path or use the test image shipped with the samples ZIP archive) */
	const char *zInput = argc > 1 ? argv[1] : "./acgt.png";
	/* Processed output image path */
	const char *zOut = argc > 2 ? argv[2] : "./out_hilditch.png";
	/* Load the input image in the grayscale colorspace */
	sod_img imgIn = sod_img_load_from_file(zInput, SOD_IMG_GRAYSCALE/* single channel colorspace (gray)*/);
	if (imgIn.data == 0) {
		/* Invalid path, unsupported format, memory failure, etc. */
		puts("Cannot load input image..exiting");
		return 0;
	}
	/* Binarize the input image before the thinning process */
	sod_img binImg = sod_threshold_image(imgIn, 0.5);
	/* Perform Hilditch thinning on this binary image. */
	sod_img imgOut = sod_hilditch_thin_image(binImg);
	/* Finally save our processed image to the specified path */
	sod_img_save_as_png(imgOut, zOut);
	/* Cleanup */
	sod_free_image(imgIn);
	sod_free_image(binImg);
	sod_free_image(imgOut);
	return 0;
}