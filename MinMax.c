#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Comparisons of two algorithms for finding min and max in array

///computational complexity 3N/2 - 1 (unsorted array)
///returns number of comparisons
int fastMinMax(int* simpleArray, int size);
///computational complexity 2N (unsorted array)
///returns number of comparisons
int otherMinMax(int* ar, int size);
const int SIZE = 100000;
int main()
{
    srand(time(NULL));
    int simpleArray[SIZE];
	//array initalization
    for(int i = 0; i < SIZE; i++)
    {
        simpleArray[i] = rand() % 98 + 1;
    }
    int n = fastMinMax(simpleArray, sizeof(simpleArray)/sizeof(int));
    printf("%d comparisons for fast\n", n);
    n = otherMinMax(simpleArray, sizeof(simpleArray)/sizeof(int));
    printf("%d comparisons for slow\n", n);
    return 0;
}

int otherMinMax(int *simpleArray, int size)
{
    int counter = 0;
    int max = simpleArray[0];
    int min = simpleArray[0];
    for(int i = 0; i < size; i++)
    {
        if(simpleArray[i] > max)
        {
            max = simpleArray[i];
        }
        if(simpleArray[i] < min)
        {
            min = simpleArray[i];
        }
        counter += 2;			//counter
    }
    printf("Max = %d, min = %d\n", max, min);
    return counter;
}

int fastMinMax(int* simpleArray, int size)
{
    int max, min;
    int iterator = 0;
    int counter = 0;
    if(size % 2 == 0)
    {
        if(simpleArray[0] > simpleArray[1])
        {
            max = simpleArray[0];
            min = simpleArray[1];
        }
        else
        {
            max = simpleArray[1];
            min = simpleArray[0];
        }
        iterator = 2;
        counter += 2;   //counter
    }
    else
    {
        max = simpleArray[0];
        min = simpleArray[0];
        iterator = 1;
        counter += 1;   //counter
    };
    for(iterator; iterator < size-1; iterator += 2)
    {
        if(simpleArray[iterator] > simpleArray[iterator+1])
        {
            if(simpleArray[iterator] > max)
            {
                max = simpleArray[iterator];
            }
            if(simpleArray[iterator+1] < min)
            {
                min = simpleArray[iterator+1];
            }
        }
        else //simpleArray[iterator] < simpleArray[iterator+1]
        {
            if(simpleArray[iterator+1] > max)
            {
                max = simpleArray[iterator+1];
            }
            if(simpleArray[iterator] < min)
            {
                min = simpleArray[iterator];
            }
        }
        counter += 3; //counter
    }
    printf("Max = %d, min = %d\n", max, min);
    return counter;
}
