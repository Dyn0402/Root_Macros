/*
 * ampt_identical_track_finder.h
 *
 *  Created on: Sep 8, 2021
 *      Author: dylan
 */

#ifndef AMPT_IDENTICAL_TRACK_FINDER_H_
#define AMPT_IDENTICAL_TRACK_FINDER_H_

#include <vector>

#include <TTree.h>
#include <TBranch.h>

using namespace std;


struct ampt_tree_branches {
	int event;
	int refmult;
	int refmult2;
	int refmult3;

	float imp;
	float qx, qy;

	int npp, npt, nesp, ninesp, nest, ninest;

	vector<int> *pid = 0;
	vector<float> *px = 0;
	vector<float> *py = 0;
	vector<float> *pz = 0;

	TBranch *branch_pid = 0;
	TBranch *branch_px = 0;
	TBranch *branch_py = 0;
	TBranch *branch_pz = 0;
};


void find_identical_tracks();
void set_ampt_tree_branches(TTree* tree, ampt_tree_branches &branches);
void set_ampt_branches(TTree* tree);



#endif /* AMPT_IDENTICAL_TRACK_FINDER_H_ */
