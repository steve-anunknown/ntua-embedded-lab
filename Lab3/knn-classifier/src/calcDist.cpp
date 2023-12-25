#include <math.h>
#include "calcDist.h"

void calcDistancesHW(float* data_hw, float* dists_hw)
{
	float data_hw_tmp[MOVIES_NUM][USERS_NUM];
	float movie_tmp[USERS_NUM];
	float dists_hw_tmp[MOVIES_NUM];
#pragma HLS ARRAY_PARTITION variable=data_hw_tmp factor=4 cyclic dim=2
#pragma HLS ARRAY_PARTITION variable=movie_tmp factor=4 cyclic dim=1
#pragma HLS ARRAY_PARTITION variable=dists_hw_tmp factor=4 cyclic dim=1

	int i, j;
LOAD_DATA_HW_TMP:
	for (i = 0; i < MOVIES_NUM; i++) {
		for (j = 0; j < USERS_NUM; j++) {
#pragma HLS PIPELINE
			data_hw_tmp[i][j] = data_hw[i * USERS_NUM + j];
		}
	}

LOAD_MOVIE_TMP:
	for (i = 0; i < USERS_NUM; i++){
#pragma HLS PIPELINE
		movie_tmp[i] = data_hw_tmp[MOVIE_ID][i];
	}

COMPUTE_DISTS:
	for (i = 0; i < MOVIES_NUM; i++) {
#pragma HLS PIPELINE
		float sum = 0.0, diff = 0.0;
		for (j = 0; j < USERS_NUM; j++) {
			diff = data_hw_tmp[i][j] - movie_tmp[j];
			sum += diff * diff;
		}
		dists_hw_tmp[i] = sqrt(sum);
	}

WRITE_DISTS:
	for (i = 0; i < MOVIES_NUM; i++) {
#pragma HLS PIPELINE
		dists_hw[i] = dists_hw_tmp[i];
	}

}
