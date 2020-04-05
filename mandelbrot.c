/*
  Compile:
  gcc -fopenmp mandelbrot.c -o mandelbrot
  Run:
  ./mandelbrot
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    /* The window in the plane. */
    const double xmin = -2.5;
    const double xmax = 1.5;
    const double ymin = -2.0;
    const double ymax = 2.0;

    /* Maximum number of iterations. */
    const uint16_t maxiter = (unsigned short)5000;

    /* Image size, width is given, height is computed. */
    const int xres = 1024;
    const int yres = (xres * (ymax - ymin)) / (xmax - xmin);

    /* Open the file and write the header. */
    FILE *fp = fopen("mandel.pmm", "wb");
    char *comment = "# Mandelbrot set"; /* comment should start with # */

    /*write ASCII header to the file*/
    fprintf(fp,
            "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
            xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

    /* Precompute pixel width and height. */
    double dx = (xmax - xmin) / xres;
    double dy = (ymax - ymin) / yres;

    double x, y; /* Coordinates of the current point in the complex plane. */
    double u, v; /* Coordinates of the iterated point. */
#pragma omp parallel
    {
        int i, j; /* Pixel counters */
        int k;    /* Iteration counter */
#pragma omp for
        for (j = 0; j < yres; j++)
        {
            y = ymax - j * dy;
            for (i = 0; i < xres; i++)
            {
                double u = 0.0;
                double v = 0.0;
                double u2 = u * u;
                double v2 = v * v;
                x = xmin + i * dx;
                /* iterate the point */
                for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++)
                {
                    v = 2 * u * v + y;
                    u = u2 - v2 + x;
                    u2 = u * u;
                    v2 = v * v;
                };
                /* compute  pixel color and write it to file */
                if (k >= maxiter)
                {
                    /* interior */
                    const unsigned char black[] = {0, 0, 0, 0, 0, 0};
                    fwrite(black, 6, 1, fp);
                }
                else
                {
                    /* exterior */
                    unsigned char color[6];
                    color[0] = k >> 8;
                    color[1] = k & 255;
                    color[2] = k >> 8;
                    color[3] = k & 255;
                    color[4] = k >> 8;
                    color[5] = k & 255;
                    fwrite(color, 6, 1, fp);
                };
            }
        }
    }
    fclose(fp);
    return 0;
}