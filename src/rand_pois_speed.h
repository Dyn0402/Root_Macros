/*
 * rand_pois_speed.h
 *
 *  Created on: Dec 12, 2021
 *      Author: dylan
 */

#ifndef RAND_POIS_SPEED_H_
#define RAND_POIS_SPEED_H_


#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>

#include <TRandom3.h>

using namespace std;

void pois_speed_test();
int sample_poisson(double r);
int sample_poisson2(double r, double p);
void pois_dist_test();


#endif /* RAND_POIS_SPEED_H_ */
