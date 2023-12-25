#include "hal_data.h"
#include "stdio.h"
#include "string.h"
#include "images.h"
#define N 10      /*Frame dimension for QCIF format*/
#define M 10      /*Frame dimension for QCIF format*/
#define BX 5      /*Block size*/
#define BY 2      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/

void phods_motion_estimation(const int current[N][M], const int previous[N][M], int vectors_x[N/BX][M/BY],int vectors_y[N/BX][M/BY])
{
    int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
    int tempx, tempy;
    //int block[N][BY];
    int current_line[BX][M];
    int min_init = 255*BX*BY;
    int cached_x = cached_y = 0;
    distx = 0;
    disty = 0;
    /*For all blocks in the current frame*/
    for(x=0; x<N/BX; x++)
    {
        for(k = 0; k < BX; ++k)
            for(l = 0; l < M; ++l)
                current_line[k][l] = current[BX*x+k][l];
        cached_x = BX*x;
        for(y=0; y<M/BY; y++)
        {
            /*Initialize the vector motion matrices*/
            vectors_x[x][y] = 0;
            vectors_y[x][y] = 0;
            //for (k = 0; k < BX; ++k)
            //    for (l = 0; l < BY; ++l)
            //        block[k][l] = current[BX*x+k][BY*y+l];
            S = 4;
            cached_y = BY*y;
            while(S > 0)
            {
                min1 = min_init;
                min2 = min_init;
                /*For all candidate blocks in X dimension*/
                for(i=-S; i<S+1; i+=S)
                {
                    distx = 0;
                    disty = 0;
                    tempx = cached_x + vectors_x[x][y];
                    tempy = cached_y + vectors_y[x][y];
                    /*For all pixels in the block*/
                    for(k=0; k<BX; k++)
                    {
                        for(l=0; l<BY; l++)
                        {
                            //p1 = block[k][l];
                            p1 = current_line[k][cached_y+l];
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

void hal_entry(void) {
    // Code to initialize the DWT->CYCCNT register
    CoreDebug->DEMCR |= 0x01000000;
    ITM->LAR = 0xC5ACCE55;
    DWT->CYCCNT = 0;
    DWT->CTRL |= 1;
    /* Initialize your variables here */
    const int NUM_MEASUREMENTS=10, CLOCK_FREQ = 240000000;
    double exec_time[NUM_MEASUREMENTS];
    double mean_time = 0.0, total_time = 0.0;
    double max_time = 0.0, min_time = (double) CLOCK_FREQ;
    int motion_vectors_x[N/BX][M/BY], motion_vectors_y[N/BX][M/BY], i, j;

    while(1){
        /* Add timer code here */
        for (i = 0; i < NUM_MEASUREMENTS; ++i)
        {
            DWT->CYCCNT = 0;
            phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);
            exec_time[i] = ((double) (DWT->CYCCNT)) / ((double) CLOCK_FREQ) ;
            total_time += exec_time[i];
            min_time = exec_time[i] < min_time ? exec_time[i] : min_time;
            max_time = exec_time[i] > max_time ? exec_time[i] : max_time;
        }
        mean_time = ((double) total_time) / ((double) NUM_MEASUREMENTS);
    }
    while(1){}
}
