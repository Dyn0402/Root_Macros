/*
 * resample_alg_test.cpp
 *
 *  Created on: Dec 10, 2021
 *      Author: dylan
 */


#include <vector>
#include <cmath>
#include <chrono>

#include <TRandom3.h>

#include "resample_alg_test.h"
#include "ratio_methods.h"

using namespace std;


void resamp_alg_speed() {
	TRandom3 *trand = new TRandom3(0);

	double bin_width = 120.0 / 180.0 * M_PI;
	int re_runs = 10;
//	int samples = 1;
	vector<int> samples {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int i=15; i<=720; i+=5) { samples.push_back(i); }
	int n_tracks = 10;
	int n_events = 10000;

	for (int sample : samples) {
		vector<double> elaps;
		for (int rerun_i=0; rerun_i < re_runs; rerun_i++) {
			chrono::system_clock::time_point start_run = chrono::system_clock::now();
			for (int event_i=0; event_i < n_events; event_i++) {
				vector<double> angles;
				for (int track_i=0; track_i < n_tracks; track_i++) {
					angles.push_back(trand->Rndm() * 2 * M_PI);
				}
				sort(angles.begin(), angles.end());
				get_resamples(angles, bin_width, sample);
			}
			chrono::duration<double> elap = chrono::system_clock::now() - start_run;

	//		cout << elap.count() << "s" << endl;
			elaps.push_back(elap.count());
		}

		cout << sample << " " << get_mean(elaps) << " " << get_sd(elaps) << " s" << endl;
	}

}


void resamp_alg_comp() {
	double bin_width = 120.0 / 180.0 * M_PI;
	int samples = 3;
	vector<double> angles {0.5, 1.5};

	cout << "get_resamples3" << endl;
	for (pair<int, int> hist : get_resamples3(angles, bin_width, samples)) {
		cout << hist.first << ": " << hist.second << endl;
	}

	cout << endl << "get_resamples2" << endl;
	for (int hist : get_resamples2(angles, bin_width, samples)) {
		cout << hist << endl;
	}

	cout << endl << "get_resamples" << endl;
	for (int hist : get_resamples(angles, bin_width, samples)) {
		cout << hist << endl;
	}
}


void resamp_alg_rndm_comp() {
	TRandom3 *trand = new TRandom3(0);
	int tests = 1000000;
	int max_particle = 100;
	int max_samples = 1000;

	for (int test_i=0; test_i < tests; test_i++) {
		int samples = ceil(trand->Rndm() * max_samples);
		double bin_width = trand->Rndm() * 2 * M_PI;
		vector<double> angles;
		for (int track_i=0; track_i < ceil(trand->Rndm() * max_particle); track_i++) {
			angles.push_back(trand->Rndm() * 2 * M_PI);
		}
//		cout << "test " << test_i << ":" << endl;
//		for (double angle : angles) { cout << angle << " " << flush; }
//		cout << endl;
		map<int, int> alg3 = get_resamples3(angles, bin_width, samples);
		vector<int> alg2 = get_resamples2(angles, bin_width, samples);
		vector<int> alg1 = get_resamples(angles, bin_width, samples);

		for (unsigned index=0; index < alg2.size(); index++) {
			if (alg1[index] != alg2[index] || alg1[index] != alg3[index] || alg2[index] != alg3[index]) {
				cout << "test " << test_i << ":" << endl;
				cout << alg1[index] << "  " << alg2[index] << "  " << alg3[index] << endl;
			}
		}
	}
}


double get_mean(vector<double> vals) {
	double sum = 0;
	for (double val : vals) {
		sum += val;
	}

	return sum / (int) vals.size();
}

double get_sd(vector<double> vals) {
	double mean = get_mean(vals);
	double sum = 0;
	for (double val : vals) {
		sum += pow((val - mean), 2);
	}

	return pow(sum / ((int)vals.size() - 1), 0.5);
}
