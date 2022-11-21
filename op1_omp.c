#include <stdio.h>
#include <omp.h>

void op1(float *input_vec, int m, int n, float *filter_vec, int k,
         float *output_vec, int b)
{
    float(*input)[m][n] = (float(*)[m][n])input_vec;
    float(*filter)[k] = (float(*)[k])filter_vec;
    float(*output)[m][n] = (float(*)[m][n])output_vec;
    int i, j, q, p,c,f,l,v;
    c = (k-1)/2;
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
        for (i = 0; i <= m-k; i++){
            for (j = 0; j <= n-k; j++){//calculate with filter
                temp1=0;
                for(q=0;q<(k*k);q++){
                    l=q%k;
                    f=q/k;
                    temp1+=(*(*(*(input+v)+f+i)+l+j))*(*(*(filter+f)+l));
                    //printf("%f\n",*(*(*(input+v)+f+i)+l+j));//check the potinter in right position
                }
                *(*(*(output+v)+i+c)+j+c)=temp1;
                //printf("\n");
        }
    }
    }
    double end=omp_get_wtime();
    printf("%.16g\n",(end-strat));
}
