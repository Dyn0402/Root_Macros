

#include "flat_test.h"


void flat_test() {
	int energy = 62;
	int cent = 8;
	int eta_bin = 0;
	int runkey = 11112;
	string east_west = "west";
	TFile *in_file = new TFile("C:/Users/Dylan/Desktop/flat_tests/" + to_string(energy) + "GeV_qa.root", "READ");

	string orig_phi_name = "original_phi_non-protons_cent_" + to_string(cent) + "_eta_bin_" + to_string(eta_bin) + "_runkey_" + to_string(runkey);
	TH1I* phi_test_hist_in = (TH1I*)in_file->Get(orig_phi_name);
	TH1I* phi_test_hist = (TH1I*)phi_test_hist_in->Clone();
	phi_test_hist->SetDirectory(0);

	string orig_psi_name = "original_psi_" + east_west + "cent_" + to_string(cent) + "_runkey_" + to_string(runkey);
	TH1I* ep_test_hist_in = (TH1I*)in_file->Get(orig_psi_name);
	TH1I* ep_test_hist = (TH1I*)ep_test_hist_in->Clone();
	ep_test_hist->SetDirectory(0);

	in_file->Close();


	TH1D* phi_sample_dist = new TH1D("Phi_Sample_Hist", "Samples from Phi Distribution", 200, 0, 2 * M_PI);
	TH1D* phi_flattened = new TH1D("Phi_Flattened", "Flattened Phi Distribution", 200, 0, 2 * M_PI);

	TH1D* ep_sample_dist = new TH1D("Ep_Sample_Hist", "Samples from EP Distribution", 200, 0, M_PI);
	TH1D* ep_flattened = new TH1D("EP_Flattened", "Flattened EP Distribution", 200, 0, M_PI);


	Flattener flat("C:/Users/Dylan/Desktop/flat_tests/phi_coefs_test.root", "C:/Users/Dylan/Desktop/flat_tests/ep_coefs_test.root");
	flat.init_phi_flattener();

	vector<double> rand_samples_phi;
	int samples = 1000000;
	for (int i = 0; i < samples; i++) {
		float rand_phi = phi_test_hist->GetRandom();
		phi_sample_dist->Fill(rand_phi);
		flat.calc_phi_terms("non-protons", cent, eta_bin, runkey * 1000, rand_phi);
		rand_samples_phi.push_back(rand_phi);
	}
	flat.write_phi();

	flat.init_ep_flattener();

	for (double sample : rand_samples_phi) {
		phi_flattened->Fill(flat.get_flat_phi(sample, "non-protons", cent, eta_bin, runkey * 1000));
	}

	vector<double> rand_samples_ep;
	for (int i = 0; i < samples; i++) {
		float rand_psi = ep_test_hist->GetRandom();
		ep_sample_dist->Fill(rand_psi);
		flat.calc_ep_terms(east_west, cent, runkey * 1000, rand_psi);
		rand_samples_ep.push_back(rand_psi);
	}

	for (double sample : rand_samples_ep) {
		ep_flattened->Fill(flat.get_flat_ep(sample, east_west, cent, runkey * 1000));
	}
	flat.write_ep();

	TFile* out_file = new TFile("C:/Users/Dylan/Desktop/flat_tests/test_out.root", "RECREATE");
	phi_test_hist->Write();
	phi_sample_dist->Write();
	phi_flattened->Write();
	ep_test_hist->Write();
	ep_sample_dist->Write();
	ep_flattened->Write();
	out_file->Close();
}