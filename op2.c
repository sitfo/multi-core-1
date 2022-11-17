#include <stdio.h>
#include <time.h>

void op2 ( float * a_vec , int m, int n , int p , float *b_vec ,float *c_vec) {
		float (*a)[n] = ( float (*) [n] ) a_vec;
		float (*b)[p] = ( float (*) [p] ) b_vec;
		float (*c)[p] = ( float (*) [p] ) c_vec;
		int i,j,k,s;
		int index;
		//matrix mutliple
		double start=clock();
		for(i=0;i<m;i++){
			for(j=0;j<p;j++){
				(*c+i*p)[j]=0;
				for (k=0;k<n;k++){
					(*c+i*p)[j]+=(*a+i*n)[k]*(*b+k*p)[j];
				}
			}			
		}
		double end = clock();
		double time = (end - start)/CLOCKS_PER_SEC;
		printf("%.16g\n", time);
	}