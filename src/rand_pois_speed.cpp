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
	TRandom3 trand2 = TRandom3(541);

	poisson_distribution<int> cdist(1);

	int n_gens = 10000000;
	double p = std::exp(-1.0);

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

	chrono::system_clock::time_point start_root2 = chrono::system_clock::now();
	for (int i = 0; i < n_gens; i++) {
		sample_poisson(trand2.Rndm());
	}
	chrono::duration<double> elap_root2 = chrono::system_clock::now() - start_root2;

	cout << "Root sample_poisson speed: " << elap_root2.count() << "s" << endl;

	chrono::system_clock::time_point start_root3 = chrono::system_clock::now();
	for (int i = 0; i < n_gens; i++) {
		sample_poisson2(trand2.Rndm(), p);
	}
	chrono::duration<double> elap_root3 = chrono::system_clock::now() - start_root3;

	cout << "Root sample_poisson pass p speed: " << elap_root3.count() << "s" << endl;
}


// Looks like TRandom3 is somehow generally just faster than the C++ implementation.
void pois_dist_test() {
	TRandom3 trand = TRandom3(456);
	TRandom3 trand2 = TRandom3(541);

	int n_gens = 100000;

	ofstream root_file("F:/Research/Results/Rand_Tests/root_dist.txt");
	for (int i = 0; i < n_gens; i++) {
		root_file << trand.Poisson(1) << '\n';
	}
	root_file.close();

	ofstream sample_poisson_file("F:/Research/Results/Rand_Tests/sample_poisson_dist.txt");
	for (int i = 0; i < n_gens; i++) {
		sample_poisson_file << sample_poisson(trand2.Rndm()) << '\n';
	}
	sample_poisson_file.close();
}


int sample_poisson(double r) {
	double p = std::exp(-1.0);
	int k = 0;
	while (r > p) {
		r -= p;
		k++;
		p *= 1.0 / k;
	}
	return k;
}

// From chat-gpt but distribution seems to match actual
// Passing p almost twice as fast
int sample_poisson2(double r, double p) {
	int k = 0;
	while (r > p) {
		r -= p;
		k++;
		p *= 1.0 / k;
	}
	return k;

}