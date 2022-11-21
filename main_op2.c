#include<stdio.h>
#include<stdlib.h>
#define __USE_C99_MATH
#include <stdbool.h>

bool test_case1();
void op2(float*, int, int, int, float*, float*);

int main() {
    bool tc1 = test_case1();
    printf("Test case 1: %s\n", tc1?"T":"F");
    return !tc1;
}

bool test_case1() {
    FILE *fp;
    fp = fopen("a.dat", "r");
    int m, n;
    fscanf(fp, "%d %d", &m, &n);
    float *a = malloc(m*n*sizeof(float));
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            fscanf(fp, "%f", &a[i*n+j]);
        }
    }
    fclose(fp);

    fp = fopen("b.dat", "r");
    int p;
    fscanf(fp, "%d %d", &n, &p);
    float *b = malloc(n*p*sizeof(float));
    for(int i=0; i<n; i++) {
        for(int j=0; j<p; j++) {
            fscanf(fp, "%f", &b[i*p+j]);
        }
    }
    fclose(fp);

    //read c.dat and assign it to an array called c. The dimensions m x p of c are in the first line of c.dat
    fp = fopen("c.dat", "r");
    int m2, p2;
    fscanf(fp, "%d %d", &m2, &p2);
    float *c_expected = (float*)malloc(m2*p2*sizeof(float));
    for(int i=0; i<m2; i++) {
        for(int j=0; j<p2; j++) {
            fscanf(fp, "%f", &c_expected[i*p2+j]);
        }
    }
    fclose(fp);
    //create an array called c to store the result of matrix multiplication
    float *c = malloc(m*p*sizeof(float));


    for(int i=0;i<(m*p); i++) {
        c[i] = 0;
    }

    op2(a, m, n, p, b, c);

    bool match = true;

    for(int i=0;i<(m*p); i++) {
        if(c[i]!=c_expected[i]) {
            match = false;
            printf("At position %d, expected %f but found %f. \n", i, c_expected[i], c[i]);
            // break;
        }
    }
    free(a);
    free(b);
    free(c);
    return match;
}