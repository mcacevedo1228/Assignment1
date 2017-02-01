/**
* CS 371 Assignment 2
* Marc Acevedo
* This program is a matrix multiplier that satisfies the requirements for Asn2
**/

#include <stdio.h>
#include <stdlib.h>
#include "mm.h"
#include "fcycmm.h"
#include "clock.h"

/* whether or not fcyc should clear the cache */
#define CLEARCACHE 1  

/* global arrays [ ok for this kind of hacking, but not in production ] */
array ga, gb, gc;	// Declared globally so memory addresses can be accessed

/* purpose: check the result array for correctness 
 * input: the product array and its size
 * returns: nothing (complains in an error message if result is wrong)
 */
void checkresult(array gc, int n)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (gc[i][j] != (double)n) // TODO: Find out what this does
      {
        printf("Error: bad number (%f) in result matrix (%d,%d) -- N is (%d)\n", 
            gc[i][j], i, j, n);
        fflush(stdout);
        exit(0);
      }
}


/* purpose: Run function f and return clocks per inner loop iteration 
 * input: a function and the matrix size
 * returns: the number of cycles taken per inner loop iteration
 */
double run(test_funct f, int n)
{
  double cpi;

  cpi = fcyc(f, n, CLEARCACHE) / (n*n*n);
  checkresult(gc, n);
  return cpi;
}


/* purpose: reset result array to zero 
 * input: the array and its size
 * returns: the array updated to all zeros
 */
void reset(array c, int n)
{
  int i,j;
  
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) 
      c[i][j] = 0.0;
}


/* purpose: initialize input arrays to 1 
 * input: the input arrays and their size
 * returns: the arrays updated to all ones.
 */
void init(array ga, array gb, int n) 
{
  int i,j;
  
  for (i = 0; i < n; i++) 
  {
    for (j = 0; j < n; j++) 
    {
      ga[i][j] = 1.0;
      gb[i][j] = 1.0;
    }
  }
}


/* purpose: print an array 
 * input:  the array and its size
 * returns: nothing (printing is a side effect)
 */
void printarray(array a, int n)
{
  int i, j;

  for (i = 0; i < n; i++) 
  {
    for (j = 0; j < n; j++) 
      printf("%5.1f ", a[i][j]);
    
    printf("\n");
  }
}


/* purpose: Determine cost of products from 3 different suppliers via matrix multiplication
 * input: A square array of products and prices, a square array of the amount of each ingredient needed, a square array of prices for each supply needed, and array length
 * returns: nothing, multiplies matrices and reassigns values of array indeces
 */
void multiply(array ga, array gb, array gc, int n) 
{
	int i,j,k;

	for (i = 0; i< n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				gc[i][j] += ga[i][k] * gb[k][j]; 	
			}
		}
	}
}

void multiplyP(array ga, array gb, array gc, int n)
{
	int i,j,k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				gc[i][j] += ga[j][k] * gb[k][i];
			}
		}
	}

}

void multiplyS(array ga, array gb, array gc, int n)
{
	int i,j,k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				gc[i][j] += ga[i][j] * gb[j][k];
			}
		}
	}
}


/* 
 * Run matrix multiply and display performance
 * as clock cycles per inner loop iteration.
 */ 
int main()
{
  int n;

  init(ga, gb, MAXN);
  printf("matmult cycles/loop iteration\n");
  fflush(stdout);
  
  for (n = MINN; n <= MAXN; n += INCN) 
  {  
    printf("%3d", n);

    printf("%9.2f ", run(multiply, n));
      
    //          Used for alternate multiplication methods
    printf("%9.2f ", run(multiplyP, n));
    printf("%9.2f", run(multiplyS, n));
      
      
    printf("\n");
    fflush(stdout);
  }

  exit(0);
}

