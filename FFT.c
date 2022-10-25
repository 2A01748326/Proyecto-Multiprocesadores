#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI       3.14159265358979323846   // pi
#define NumElem 8

typedef struct{
    float real, img;
}COMPLEX;

void init_W(int N, COMPLEX *W){
    int n; 
    float a = 2.0*M_PI/N;

    for(n = 0; n < N; n++){
        W[n].real = (float) cos(-n*a);
        W[n].img = (float) sin(-n*a);
    }
    
}


void FFT(COMPLEX* x){
    int n = NumElem;
    COMPLEX *W = (COMPLEX *)calloc(n, sizeof(COMPLEX));
    init_W(n, W);
    int len = n/2;
    int j,i,k;
    COMPLEX *Wptr;
    COMPLEX u, temp, tm;
    int Windex = 1;
    for ( len = n/2 ; len > 0 ; len /= 2) {
        Wptr = W ;
        for ( j = 0 ; j < len ; j++) {
            u = *Wptr ;
            for ( i = j ; i < n ; i = i + 2*len ) {
                temp.real = x[ i ].real + x[ i+len ].real ;
                temp.img = x [ i ].img + x[ i+len ].img ;
                tm.real = x [ i ].real - x[ i+len ].real ;
                tm.img = x [ i ].img - x[ i+len ].img ;
                x [ i+len ].real = tm.real*u.real - tm.img*u.img ;
                x [ i+len ].img = tm.real*u.img + tm.img*u.real ;
                x [ i] = temp ;
            }
        Wptr = Wptr + Windex ;
        }
    Windex = 2*Windex ;
    }

    j = 0;
    for(i =1; i < (n-1); i++){
        k = n/2;
        while(k<=j){
            j -= k;
            k /= 2;
        }
        j += k ;
        if(i < j) {
            temp = x[j];
            x [j] = x[i] ;
            x [i] = temp ;
        }
    }
    free(W);

}



int main(){
    COMPLEX *arr = (COMPLEX *)calloc(NumElem, sizeof(COMPLEX));
    for(int i =0; i<NumElem; i++){
        arr[i].real = i + 1.0;
        arr[i].img = 0.0;
        printf("%f, i%f\n", arr[i].real, arr[i].img);
    }
    FFT(arr);
    printf("Despues de FFT\n");
    for(int i =0; i<NumElem; i++){
        printf("%f, i%f\n", arr[i].real, arr[i].img);
    }
    free(arr);
    return 0;    
}