#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <time.h>

void op1(float *input_vec, int m, int n, float *filter_vec, int k,
         float *output_vec, int b)
{
    float(*input)[m][n] = (float(*)[m][n])input_vec;
    float(*filter)[k] = (float(*)[k])filter_vec;
    float(*output)[m][n] = (float(*)[m][n])output_vec;
    int i, j, q, p,c,f,l,v;
    int Row = m-k;
    int Col = n-k;
    int border = k*k;
    c = (k-1)/2;//calculate center of filter
    float temp1;
    //copy valus to 3Darray output.
    for(v=0;v<b;v++){
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                *(*(*(output+v)+i)+j)=*(*(*(input+v)+i)+j);
            }
        }
    }
    //Calculate
    double strat =omp_get_wtime();
    #pragma omp parallel for private(v,i,j,q),collapse(3)
    for(v=0;v<b;v++){
        for (i = 0;i<=Row; i++){
            for (j = 0;j<=Col; j++){//limit calculation area of input
                temp1=0;
                for(q=0;q<border;q++){//calculate with filter
                    l=q%k;
                    f=q/k;
                    temp1+=(*(*(*(input+v)+f+i)+l+j))*(*(*(filter+f)+l));
                }
                *(*(*(output+v)+i+c)+j+c)=temp1;
            }
        }
    }
    double end=omp_get_wtime();
    printf("%.16g\n",(end-strat));//print time cost
}
