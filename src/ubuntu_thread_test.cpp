/*
 * ubuntu_thread_test.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: dylan
 */


#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <random>

#include <TROOT.h>
#include <TRandom3.h>

#include "ThreadPool.h"
#include "ubuntu_thread_test.h"

using namespace std;



void ubuntu_thread_test() {
	int num = 1000000000;
	ROOT::EnableThreadSafety();
	for (unsigned threads = 1; threads <= thread::hardware_concurrency(); threads++) {
//		chrono::system_clock::time_point start = chrono::high_resolution_clock::now();
//		clock_t start = clock();
		auto start = chrono::system_clock::now();
		{
			ThreadPool pool(threads);
			for (int i=0; i < threads; i++) {
				pool.enqueue(work, num);
			}
		}
//		chrono::system_clock::time_point stop = chrono::high_resolution_clock::now();
//		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		chrono::duration<double> duration = (chrono::system_clock::now() - start);
		cout << "Threads " << threads << " " << duration.count() << "s" << endl;
	}
//	vector<int> hist = work(num);
//	for (int count : hist) {
//		cout << count << endl;
//	}
}


vector<int> work(int num) {
	TRandom3 *rand = new TRandom3(0);
	int bins = 10;
	vector<int> hist(bins);
	for (int i=0; i < num; i++) {
		double r = rand->Rndm();
		for (int j=1; j < bins + 1; j++) {
			if (r < j * 1.0 / bins) {
				hist[j-1] += 1;
				break;
			}
		}
	}

	return hist;
}


vector<int> work_rand_shuff(int num) {
	TRandom3 *rand = new TRandom3(0);
	mt19937 eng(rand->Integer(2147483647));
	int bins = 10;
	vector<int> hist(bins);
	for (int i=0; i < num; i++) {
		double r = rand->Rndm();
		for (int j=1; j < bins + 1; j++) {
			if (r < j * 1.0 / bins) {
				hist[j-1] += 1;
				break;
			}
		}
	}

	return hist;
}
