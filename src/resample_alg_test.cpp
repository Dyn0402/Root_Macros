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


void resample_alg_test() {
	TRandom3 *trand = new TRandom3(0);

	double bin_width = 120.0 / 180.0 * M_PI;
	int re_runs = 10;
//	int samples = 1;
	vector<int> samples {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int i=15; i<=720; i+=5) { samples.push_back(i); }
	int n_tracks = 30;
	int n_events = 10000;
//	vector<double> angles {0.5, 0.06, 0.8};

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
				get_resamples2(angles, bin_width, sample);
			}
			chrono::duration<double> elap = chrono::system_clock::now() - start_run;

	//		cout << elap.count() << "s" << endl;
			elaps.push_back(elap.count());
		}

		cout << sample << " " << get_mean(elaps) << " " << get_sd(elaps) << " s" << endl;
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
