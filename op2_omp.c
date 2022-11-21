#include <stdio.h>
#include <omp.h>

void op2(float *a_vec, int m, int n, int p, float *b_vec, float *c_vec)
{
	float(*a)[n] = (float(*)[n])a_vec;
	float(*b)[p] = (float(*)[p])b_vec;
	float(*c)[p] = (float(*)[p])c_vec;
	int i, j, k;
	int index;
	// matrix mutliple
	double start = omp_get_wtime();
#pragma omp parallel for private(index, k)
	for (index = 0;index < (m*p); index++)//conunt Row & Col by border of C
	{
		i=index/p;
		j=index%p;
		(*c + i * p)[j] = 0;
		for (k = 0; k < n; k++)
		{
			(*c + i * p)[j] += (*a + i * n)[k] * (*b + k * p)[j];//operation
		}
	}
	double end = omp_get_wtime();
	double time = end - start;
	printf("%.16g\n", time);
}