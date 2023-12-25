#include <stdio.h>
#include <time.h>
#include "images.h"


#define N 10    /*Frame dimension for QCIF format*/
#define M 10     /*Frame dimension for QCIF format*/

#define B 5      /*Block size*/

#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/


void phods_motion_estimation(const int current[N][M], const int previous[N][M], int vectors_x[N/B][M/B],int vectors_y[N/B][M/B])
{
    int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
    int tempx, tempy;
    int block[B][B];
    int cond1, cond2;
    distx = 0;
    disty = 0;


    /*For all blocks in the current frame*/
    for(x=0; x<N/B; x++)
    {
        for(y=0; y<M/B; y++)
        {
            /*Initialize the vector motion matrices*/
            S = 4;
            vectors_x[x][y] = 0;
            vectors_y[x][y] = 0;
            for (k = 0; k < B; ++k)
                for (l = 0; l < B; ++l)
                    block[k][l] = current[B*x+k][B*y+l];

            while(S > 0)
            {
                min1 = 255*B*B;
                min2 = 255*B*B;

                /*For all candidate blocks in X dimension*/
                for(i=-S; i<S+1; i+=S)
                {
                    distx = 0;
                    disty = 0;
                    tempx = B * x + vectors_x[x][y];
                    tempy = B * y + vectors_y[x][y];
                    /*For all pixels in the block*/
                    for(k=0; k<B; k++)
                    {
                        for(l=0; l<B; l++)
                        {
                            p1 = block[k][l];

                            // cond1 = ((tempx + i + k) < 0 || (tempx + i + k) > (N-1) || (tempy + l) < 0 || (tempy + l) > (M-1));
                            // cond2 = ((tempx + k) < 0 || (tempx + k) > (N-1) || (tempy + i + l) < 0 || (tempy + i + l) > (M-1));
                            // p2 = cond1 * 0 + (1 - cond1) * (previous[tempx + i + k][tempy + l]);
                            // q2 = cond2 * 0 + (1 - cond2) * (previous[tempx + k][tempy + i + l]);

                            if((tempx + i + k) < 0 || (tempx + i + k) > (N-1) ||
                                    (tempy + l) < 0 || (tempy + l) > (M-1))
                                p2 = 0;
                            else
                                p2 = previous[tempx+i+k][tempy+l];

                            if((tempx + k) < 0 || (tempx + k) > (N-1) ||
                                    (tempy + i + l) < 0 || (tempy + i + l) > (M-1))
                                q2 = 0;
                            else
                                q2 = previous[tempx+k][tempy+i+l];

                            distx += (p1 - p2 > 0) ? p1 - p2: p2 - p1;
                            disty += (p1 - q2 > 0) ? p1 - q2: q2 - p1;
                        }
                    }
                    if(distx < min1)
                    {
                        min1 = distx;
                        bestx = i;
                    }
                    if(disty < min2)
                    {
                        min2 = disty;
                        besty = i;
                    }
                }
                S = S/2;
                vectors_x[x][y] += bestx;
                vectors_y[x][y] += besty;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the software delay function provided by the BSP.
 * Only references two other modules including the BSP, IOPORT.
 *
 **********************************************************************************************************************/
int main(void) {
    // Code to initialize the DWT->CYCCNT register
    /* Initialize your variables here */
    const int NUM_MEASUREMENTS=10;
    const int NUM_TRIALS=2;
    const int B_TRIALS[NUM_TRIALS] = {2, 5};
    const int BX_TRIALS[NUM_TRIALS] = {2, 5};
    const int BY_TRIALS[NUM_TRIALS] = {2, 5};

    double exec_time[NUM_MEASUREMENTS];
    double mean_time = 0.0;
    double total_time = 0.0;
    double max_time = 0.0;
    double min_time = (double) CLOCKS_PER_SEC;

    int motion_vectors_x[N/B][M/B], motion_vectors_y[N/B][M/B], i, j;

    clock_t begin = clock();
    clock_t end = clock();
    double time_spent;


    for (j = 0; j < NUM_TRIALS; ++j)
    {
        printf("B = %d\n", B_TRIALS[j]);
        for (i = 0; i < NUM_MEASUREMENTS; ++i)
        {
            begin = clock();
            phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);
            end = clock();
            exec_time[i] = (double)(end - begin) / CLOCKS_PER_SEC;

            total_time += exec_time[i];
            min_time = exec_time[i] < min_time ? exec_time[i] : min_time;
            max_time = exec_time[i] > max_time ? exec_time[i] : max_time;
        }
        mean_time = ((double) total_time) / ((double) NUM_MEASUREMENTS);
        printf("\tmean time: %lf\n", mean_time);
        printf("\tmin time: %lf\n", min_time);
        printf("\tmax time: %lf\n", max_time);
    }
    return 0;
}
