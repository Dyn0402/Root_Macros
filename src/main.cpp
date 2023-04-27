/*
 * main.cpp
 *
 *  Created on: Sep 8, 2021
 *      Author: dylan
 */


#include <iostream>

#include "file_io.h"

#include "ampt_identical_track_finder.h"
#include "ubuntu_thread_test.h"
#include "resample_alg_test.h"
#include "rand_pois_speed.h"
#include "flat_test.h"

using namespace std;

int main() {
//	find_identical_tracks();
	//ubuntu_thread_test();
	//resamp_alg_speed();
//	resamp_alg_comp();
//	resamp_alg_rndm_comp();
	pois_speed_test();
	pois_dist_test();
	//flat_test();
	cout << "donzo" << endl;
	return 0;
}


