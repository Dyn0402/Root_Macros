/*
 * resample_alg_test.h
 *
 *  Created on: Dec 10, 2021
 *      Author: dylan
 */

#ifndef RESAMPLE_ALG_TEST_H_
#define RESAMPLE_ALG_TEST_H_


#include "ratio_methods.h"

void resamp_alg_speed();
void resamp_alg_comp();
void resamp_alg_rndm_comp();
double get_mean(vector<double> vals);
double get_sd(vector<double> vals);



#endif /* RESAMPLE_ALG_TEST_H_ */
