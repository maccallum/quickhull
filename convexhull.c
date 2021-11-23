/* 
   2D quickhull implementation in C
   https://en.wikipedia.org/wiki/Quickhull

   John MacCallum
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

double dist(double x1,
            double y1,
            double x2,
            double y2,
            double x,
            double y)
{
	return (y - y1) * (x2 - x1) - (y2 - y1) * (x - x1);
}

int whichside(double d)
{
	if(d > 0)
    {
		return 1;
	}
    else if(d < 0)
    {
		return -1; 
	}
    else
    {
		return 0;
	}
}

int quickhull(int hulln,
              int *hull,
              int p1,
              int p2,
              int n,
              double *xs,
              double *ys,
              int side)
{
	int idx = -1;
	double max = 0;
	for(int i = 0; i < n; i++)
    {
		double d = dist(xs[p1], ys[p1], xs[p2], ys[p2], xs[i], ys[i]);
		double absd = fabs(d);
		int w = whichside(d);
		if(w == side && absd > max)
        {
			idx = i;
			max = absd;
		}
	}
	if(idx == -1)
    {
		if(!hull[p1])
        {
			hulln++;
		}
		hull[p1] = 1;
		if(!hull[p2])
        {
			hulln++;
		}
		hull[p2] = 1;
		return hulln;
	}

	hulln = quickhull(hulln, hull, idx, p1, n, xs, ys,
                      -whichside(dist(xs[p1],
                                      ys[p1],
                                      xs[p2],
                                      ys[p2],
                                      xs[idx],
                                      ys[idx])));
	hulln = quickhull(hulln, hull, idx, p2, n, xs, ys,
                      -whichside(dist(xs[p2],
                                      ys[p2],
                                      xs[p1],
                                      ys[p1],
                                      xs[idx],
                                      ys[idx])));
	return hulln;
}

void test(int *hull, int p1, int p2, int n, double *xs, double *ys)
{
	int hulln = 0;
	hulln = quickhull(hulln, hull, p1, p2, n, xs, ys, 1);
	hulln = quickhull(hulln, hull, p1, p2, n, xs, ys, -1);
	printf("%d points in the hull\n", hulln);
	for(int i = 0; i < n; i++)
    {
		if(hull[i])
        {
			printf("(%f, %f)\n", xs[i], ys[i]);
		}
	}
}

int main(int ac, char **av)
{
	double xs[] = {0, 1, 2, 4, 0, 1, 3, 3};
	double ys[] = {3, 1, 2, 4, 0, 2, 1, 3};
	int n = sizeof(xs) / sizeof(double);
	if(n < 3){
		printf("n must be >= 3\n");
		return 1;
	}
	int minx = 0, maxx = 0;
	for(int i = 1; i < n; i++){
		if(xs[i] < xs[minx]){
			minx = i;
		}else if(xs[i] > xs[maxx]){
			maxx = i;
		}
	}
	int hull[n];
	memset(hull, 0, n * sizeof(int));
	test(hull, minx, maxx, n, xs, ys);
	
	return 0;
}
