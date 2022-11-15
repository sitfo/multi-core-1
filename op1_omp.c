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
//test with example
/*int main(){
    int m,n=5;
    int b=1000;
    float a[5][5]={
        {7,2,3,3,8},
        {4,5,3,8,4},
        {3,3,2,8,4},
        {2,8,7,2,7},
        {5,4,4,5,4}
    };
    float input[b][m][n];
    float filter[3][3]={
        {1,0,-1},
        {1,0,-1},
        {1,0,-1},
    };
    int i,j,v;
    for(v=0;v<b;v++){
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                input[v][i][j]=a[i][j];
            }
        }
    }
    float output[b][m][n];
	double strat=omp_get_wtime();
    op1(input, m, n, filter, 3, output, b);
	double end=omp_get_wtime();
	double time=end-strat;
	printf("%.16g\n",time);
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%f\t",*(*(*(output+500)+i)+j));
        }
        printf("\n");
    }
}*/