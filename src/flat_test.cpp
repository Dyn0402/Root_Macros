

#include "flat_test.h"


void flat_test() {
	TFile *in_file = new TFile("C:/Users/Dylan/Desktop/flat_tests/11GeV_qa.root", "READ");

	TH1I* phi_test_hist_in = (TH1I*)in_file->Get("original_phi_non-protons_cent_5_eta_bin_0_runkey_11148");
	TH1I* phi_test_hist = (TH1I*)phi_test_hist_in->Clone();
	phi_test_hist->SetDirectory(0);

	TH1I* ep_test_hist_in = (TH1I*)in_file->Get("original_psi_east_cent_5_runkey_11148");
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
		flat.calc_phi_terms("protons", 8, 0, 11148000, rand_phi);
		rand_samples_phi.push_back(rand_phi);
	}
	flat.write_phi();

	flat.init_ep_flattener();

	for (double sample : rand_samples_phi) {
		phi_flattened->Fill(flat.get_flat_phi(sample, "protons", 8, 0, 11148000));
	}

	vector<double> rand_samples_ep;
	for (int i = 0; i < samples; i++) {
		float rand_psi = ep_test_hist->GetRandom();
		ep_sample_dist->Fill(rand_psi);
		flat.calc_ep_terms("west", 8, 11148000, rand_psi);
		rand_samples_ep.push_back(rand_psi);
	}

	for (double sample : rand_samples_ep) {
		ep_flattened->Fill(flat.get_flat_ep(sample, "west", 8, 11148000));
	}

	TFile* out_file = new TFile("C:/Users/Dylan/Desktop/flat_tests/test_out.root", "RECREATE");
	phi_test_hist->Write();
	phi_sample_dist->Write();
	phi_flattened->Write();
	ep_test_hist->Write();
	ep_sample_dist->Write();
	ep_flattened->Write();
	out_file->Close();
}