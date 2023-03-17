

#include "flat_test.h"


void flat_test() {
	TFile *in_file = new TFile("C:/Users/Dylan/Desktop/flat_tests/11GeV_qa.root", "READ");

	//TH1I* h = (TH1I*)f->Get("original_psi_east_cent_5_runkey_11148");
	TH1I* phi_test_hist_in = (TH1I*)in_file->Get("original_phi_non-protons_cent_5_eta_bin_0_runkey_11148");
	cout << phi_test_hist_in << endl;
	TH1I* phi_test_hist = (TH1I*)phi_test_hist_in->Clone();
	cout << phi_test_hist << endl;

	in_file->Close();

	//Flattener flat("C:/Users/Dylan/Desktop/flat_tests/phi_coefs_test.root");
	//flat.init_phi_flattener();

	//TH1D *phi_sample_dist = new TH1D("Phi_Sample_Hist", "Samples from Phi Distribution", 200, 0, 2 * M_PI);
	////vector<double> rand_samples;
	//int samples = 1000000;
	//for (int i = 0; i < samples; i++) {
	//	cout << phi_test_hist << endl;
	//	float rand_phi = phi_test_hist->GetRandom();
	//	phi_sample_dist->Fill(rand_phi);
	//	//flat.calc_phi_terms("protons", 8, 0, 11148000, rand_phi);
	//	//rand_samples.push_back(rand_phi);
	//}

	//TH1D* phi_flattened = new TH1D("Phi_Flattened", "Flattened Phi Distribution", 200, 0, 2 * M_PI);
	//for (double sample : rand_samples) {
	//	phi_flattened->Fill(flat.get_flat_phi(sample, "protons", 8, 0, 11148000));
	//}

	TFile* out_file = new TFile("C:/Users/Dylan/Desktop/flat_tests/test_out.root", "RECREATE");
	phi_test_hist->Write();
	//phi_sample_dist->Write();
	//phi_flattened->Write();
	out_file->Close();
}