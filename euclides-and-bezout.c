/*
    A program that reads n<=N integers and finds their gcd,
    with Euclides' algorithm and Bezout's identity.
*/

#include <stdio.h>

#define N 5

int main (void) {
    unsigned n, k, i; /* number of numbers, indices */
    int e[N], ll[N], gcd; /* numbers, Bezout’s coefficients, gcd */
    int a0, a1, a2, p0, p1, p2, q0, q1, q2; /* for algorithm for 2 numbers */
    int r, c; /* remainder and quotient */
    long int bezout ; /* bezout’s sum, to do test */
    
    /* reading data */
    printf("Introduce at most %i numbers, stop with 0\n" , N);
    for(n=0; n<N; n++) {
        scanf(" %d", &e[n]);
        if(e[n]==0) {
            break;
        }
    }

    /* Initialization of Bezout’s identity (trivial case: k=0) */
    if (e[0] > 0) {
        gcd = e[0];
        ll[0] = 1;
    } else {
        gcd = -e[0];
        ll[0] = -1;
    }

    /* loop from k=1 to n-1 */
    for (k=1; k<n; k++) {
        /* Computation of Bezout’s identity for a=gcd and b=e[k] */

        /* Initialization */
        a0 = gcd; a1 = e[k];
        p0 = 1; p1 = 0;
        q0 = 0; q1 = 1;

        /* Loop for extended Euclides’ algorithm */
        while(1) {
            
            c=a0/a1;
            r=a0%a1;
            
            if(a0 < 0) {
                r=-1*((-1*a0)%a1);
            }

            if(a1 < 0) {
                r=-1*((-1*a0)%(-1*a1));
            }

            if(a0 < 0 && a1 < 0) {
                r=(-1*a0)%(-1*a1);
            }

            a2 = r;
            p2 = p0-c*p1;
            q2 = q0-c*q1;

            if(a2==0) {
                break;
            }
            
            a0 = a1;
            a1 = a2;
            p0 = p1;
            p1 = p2;
            q0 = q1;
            q1 = q2;
        }

        /* In the end: a1= p1*a+q1*b and if gcd<0 --> -gcd=-a1=-(p1*a+q1*b)=-p1*a-q1*b*/
        gcd=a1;
        if(gcd < 0) {
            gcd=-gcd;
            q1=-q1;
            p1=-p1;
        }

        /* Compute extended Bezout’s identity up to k */
        ll[k]=q1;
        for (i=0; i<k; i++) {
            ll[i] *= p1;
        }

    }
    /* Test */
    bezout=0;
    for(i=0; i<n; i++) {
        bezout += (long) ll[i]*e[i];
    }
    printf("\nTest: %i= %li\n", gcd, bezout);
    
    /* Printing Bezout’s identity */
    printf("%d = (%d)(%d)", gcd, ll[0], e[0]); 
    for(i=1; i<n; i++) {
        printf(" + (%d)(%d)", ll[i], e[i]);
    }
    printf("\n");

    return 0;
}
