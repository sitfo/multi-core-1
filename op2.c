#include <stdio.h>
#include <omp.h>

void op2 ( float * a_vec , int m, int n , int p , float *b_vec ,float *c_vec) {
		float (*a)[n] = ( float (*) [n] ) a_vec;
		float (*b)[p] = ( float (*) [p] ) b_vec;
		float (*c)[p] = ( float (*) [p] ) c_vec;
		int i,j,k,s;
		int index;
		//matrix mutliple
		for(index=0;index<(m*p);index++){
			i=index/p;
			j=index%p;
			(*c+i*p)[j]=0;
			for (k=0;k<p;k++){
				(*c+i*p)[j]+=(*a+i*n)[k]*(*b+k*p)[j];
			}
		}
	}
/*	
int main(){
	float a[5][5]={
		{5,5,5,5,5},
		{1,1,1,1,1},
		{2,2,2,2,2},
		{3,3,3,3,3},
		{4,4,4,4,4},
	};
	float b[5][5]={
		{1,1,1,1,1},
		{2,2,2,2,2},
		{3,3,3,3,3},
		{4,4,4,4,4},
		{5,5,5,5,5},
	};
	float c[5][5];
	double start =omp_get_wtime();
	op2(a, 5, 5, 5, b, c);
	double end=omp_get_wtime();
	double time = end-start;
	printf("%g\n",time);
}*/