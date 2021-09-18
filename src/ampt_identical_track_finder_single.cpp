

#include <iostream>
#include <vector>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TVector3.h>



struct ampt_tree_branches {
	int event;
	int refmult;
	int refmult2;
	int refmult3;

	float imp;
	float qx, qy;

	int npp, npt, nesp, ninesp, nest, ninest;

	vector<int>* pid = 0;
	vector<float>* px = 0;
	vector<float>* py = 0;
	vector<float>* pz = 0;

	TBranch* branch_pid = 0;
	TBranch* branch_px = 0;
	TBranch* branch_py = 0;
	TBranch* branch_pz = 0;
};


void find_identical_tracks();
void set_ampt_tree_branches(TTree* tree, ampt_tree_branches& branches);
void set_ampt_branches(TTree* tree);


void ampt_identical_track_finder_single(string root_path) {
	cout << root_path << endl;
	//TFile f(root_path.data(), "READ");
	//TTree* tree = (TTree*)f.Get("tree");
	//set_ampt_tree_branches(tree, branches);
	//set_ampt_branches(tree);

	//int event_index = 0;
	//int duplicate_count = 0;
	//while (tree->GetEvent(event_index++)) {
	//	int tracks = (int)branches.pid->size();
	//	for (int track_index_i = 0; track_index_i < tracks - 1; track_index_i++) {
	//		if (find(ignore_pids.begin(), ignore_pids.end(), (int)branches.pid->at(track_index_i)) != ignore_pids.end()) {
	//			continue;
	//		}
	//		TVector3 vec_i(branches.px->at(track_index_i), branches.py->at(track_index_i), branches.pz->at(track_index_i));
	//		if (fabs(vec_i.Eta()) > max_eta) { continue; }

	//		for (int track_index_j = track_index_i + 1; track_index_j < tracks; track_index_j++) {
	//			if (branches.px->at(track_index_i) != branches.px->at(track_index_j)) { continue; }
	//			if (branches.py->at(track_index_i) != branches.py->at(track_index_j)) { continue; }
	//			if (branches.pz->at(track_index_i) != branches.pz->at(track_index_j)) { continue; }
	//			if (branches.pid->at(track_index_i) != branches.pid->at(track_index_j)) { continue; }
	//			duplicate_count++;

	//			//					 cout << "Identical Tracks in Event " << event_index - 1 << " of " << tree->GetEntries() << endl;
	//			//					 cout << "\tTrack " << track_index_i << ":\tpid = " << branches.pid->at(track_index_i) << " px = " << branches.px->at(track_index_i) << " py = " << branches.py->at(track_index_i) << " pz = " << branches.pz->at(track_index_i) << endl;
	//			//					 cout << "\tTrack " << track_index_j << ":\tpid = " << branches.pid->at(track_index_j) << " px = " << branches.px->at(track_index_j) << " py = " << branches.py->at(track_index_j) << " pz = " << branches.pz->at(track_index_j) << endl;
	//			//					 cout << endl;
	//		}
	//	}
	//	if (duplicate_count > 0) {
	//		cout << "File " << ++file_index << " of " << files << ": " << root_path << endl;
	//		cout << "Identical Tracks in Event " << event_index - 1 << " of " << tree->GetEntries() << "  " << duplicate_count << " identical pairs" << endl;
	//	}
	//}

	//f.Close();
}


// Set tree branch addresses and return them in a tree_branches struct.
void set_ampt_tree_branches(TTree* tree, ampt_tree_branches& branches) {
	tree->SetBranchAddress("event", &branches.event);

	tree->SetBranchAddress("refmult", &branches.refmult);
	tree->SetBranchAddress("refmult2", &branches.refmult2);
	tree->SetBranchAddress("refmult3", &branches.refmult3);

	tree->SetBranchAddress("imp", &branches.imp);
	tree->SetBranchAddress("qx", &branches.qx);
	tree->SetBranchAddress("qy", &branches.qy);

	tree->SetBranchAddress("npp", &branches.npp);
	tree->SetBranchAddress("npt", &branches.npt);
	tree->SetBranchAddress("nesp", &branches.nesp);
	tree->SetBranchAddress("ninesp", &branches.ninesp);
	tree->SetBranchAddress("nest", &branches.nest);
	tree->SetBranchAddress("ninest", &branches.ninest);

	tree->SetBranchAddress("pid", &branches.pid, &branches.branch_pid);
	tree->SetBranchAddress("px", &branches.px, &branches.branch_px);
	tree->SetBranchAddress("py", &branches.py, &branches.branch_py);
	tree->SetBranchAddress("pz", &branches.pz, &branches.branch_pz);
}


void set_ampt_branches(TTree* tree) {
	tree->SetBranchStatus("*", 0);
	tree->SetBranchStatus("pid", 1);
	tree->SetBranchStatus("px", 1);
	tree->SetBranchStatus("py", 1);
	tree->SetBranchStatus("pz", 1);
}