
#define _USE_MATH_DEFINES
#include <vector>
#include <map>
#include <iostream>
#include <numeric>
#include <cmath>

#include "TRandom3.h"

#include "mixer_bad_event_alg_test.h"

using namespace std;


void gen_rand_events(vector<vector<double>>& events, int n_events, TRandom3 rand);


void mixer_bad_event_alg_test() {
	int cent_bin = 0;
	int ep_bin = 0;
	int vz_bin = 0;

	int num_protons = 3;
	int num_pool_events = 200;
	int num_iterations = 1000000;

	TRandom3 rand(0);

	for (int iteration = 0; iteration < num_iterations; iteration++) {
		if (!(iteration % 10000)) { cout << "iteration " << iteration << endl; }
		int max_protons = 150;  // Big problems if this is broken!
		vector<double> mixer_randoms;  // Make sure number of random calls independent of how many tracks in each event
		if (num_protons > max_protons) { cout << "Too many protons in get_mixed! " << num_protons << endl; }
		mixer_randoms.reserve(2 * max_protons);
		for (int i = 0; i < 2 * max_protons; i++) {
			mixer_randoms.push_back(rand.Rndm());
		}

		vector<vector<vector<vector<vector<double>>>>> angles;
		angles.push_back(vector<vector<vector<vector<double>>>>());
		angles[0].push_back(vector<vector<vector<double>>>());
		angles[0][0].push_back(vector<vector<double>>());

		//angles[0][0][0].push_back(vector<double> {1, 2, 3});
		//angles[0][0][0].push_back(vector<double> {});
		//angles[0][0][0].push_back(vector<double> {3, 4, 6});
		//angles[0][0][0].push_back(vector<double> {5, 6});

		gen_rand_events(angles[cent_bin][ep_bin][vz_bin], num_pool_events, rand);

		vector<double> mix_angles(num_protons);
		int pool_events = (int)angles[cent_bin][ep_bin][vz_bin].size();

		int rand_index = 0;
		vector<int> event_indices(pool_events);
		iota(begin(event_indices), end(event_indices), 0);
		int event_meta_index, event_index, num_angles, angle_index;
		double new_angle;
		for (int i = 0; i < num_protons; i++) {
			event_meta_index = mixer_randoms[rand_index++] * event_indices.size();
			if (event_meta_index >= event_indices.size()) {
				cout << "This should never run" << endl;
				return;
			}
			event_index = event_indices[event_meta_index];
			num_angles = angles[cent_bin][ep_bin][vz_bin][event_index].size();
			while (num_angles == 0) {  // If no angles, just take first index remaining in list
				event_indices.erase(event_indices.begin() + event_meta_index);
				event_meta_index = 0;
				if (event_meta_index >= event_indices.size()) {
					cout << "event_indices call out of range. Size=" << event_indices.size() << " event_meta_index=" << event_meta_index << endl;
					cout << "Returning without mixed for cent_bin: " << cent_bin << " ep_bin: " << ep_bin << " vz_bin: " << vz_bin << " n_protons: " << num_protons << " pool_events: " << pool_events << endl;
					return;
				}
				event_index = event_indices[event_meta_index];
				num_angles = angles[cent_bin][ep_bin][vz_bin][event_index].size();
			}
			angle_index = mixer_randoms[rand_index++] * angles[cent_bin][ep_bin][vz_bin][event_index].size();
			new_angle = angles[cent_bin][ep_bin][vz_bin][event_index][angle_index];
			mix_angles[i] = new_angle;
			event_indices.erase(event_indices.begin() + event_meta_index);
		}

		//for (double ang : mix_angles) {
		//	cout << ang << ", " << flush;
		//}
		//cout << " Number of events left in pool: " << event_indices.size() << endl;
	}
}


void gen_rand_events(vector<vector<double>>& events, int n_events, TRandom3 rand) {
	vector<int> angles_per_event;
	for (int event_index = 0; event_index < n_events; event_index++) {
		angles_per_event.push_back((int)(rand.Rndm() * 3));
	}

	for (int n_angles : angles_per_event) {
		events.push_back(vector<double> ());
		for (int angle_index = 0; angle_index < n_angles; angle_index++) {
			events.back().push_back(rand.Rndm() * 2 * M_PI);
		}
 	}
}