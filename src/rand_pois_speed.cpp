/*
 * rand_pois_speed.cpp
 *
 *  Created on: Dec 12, 2021
 *      Author: dylan
 */


#include "rand_pois_speed.h"


// Looks like TRandom3 is somehow generally just faster than the C++ implementation.
void pois_speed_test() {
	mt19937_64 *crand = new mt19937_64(456);
	TRandom3 trand = TRandom3(456);

	poisson_distribution<int> cdist(1);

	int n_gens = 10000;

	chrono::system_clock::time_point start_c = chrono::system_clock::now();
	for (int i=0; i<n_gens; i++) {
		cdist(*crand);
	}
	chrono::duration<double> elap_c = chrono::system_clock::now() - start_c;

	cout << "C++ speed: " << elap_c.count() << "s" << endl;

	chrono::system_clock::time_point start_root = chrono::system_clock::now();
	for (int i=0; i<n_gens; i++) {
		trand.Poisson(1);
	}
	chrono::duration<double> elap_root = chrono::system_clock::now() - start_root;

	cout << "Root speed: " << elap_root.count() << "s" << endl;
}
