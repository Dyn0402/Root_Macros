#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

void run_test(int vector_size, int n_samples, const string& file_name);
double shuffle_test(int vector_size, int n_samples);
double erase_test(int vector_size, int n_samples);


//void time_test(int vector_size, int n_samples_max) {
//    string file_name = "F:/Research/Results/c++_timing_tests/timing_results_vecsize" + to_string(vector_size) + ".txt";
//    for (int n_samples = 1; n_samples < n_samples_max; ++n_samples) {
//        std::cout << "n_samples " << n_samples << ":\n";
//        run_test(vector_size, n_samples, file_name);
//        std::cout << "-----------------------\n";
//    }
//}


void time_test(int vector_size) {
    int trials = 100;  // Number of times to repeat tests to get better average
    int n_samples_max = vector_size - 1;

    // Open output file for appending
    string file_name = "F:/Research/Results/c++_timing_tests/timing_results_vecsize" + to_string(vector_size) + ".txt";
    ofstream output_file(file_name, ios_base::out);

    for (int n_samples = 1; n_samples < n_samples_max; ++n_samples) {

        // Run shuffle test <trials> times and calculate average time
        double shuffle_total_time = 0.0;
        for (int i = 0; i < trials; i++) {
            shuffle_total_time += shuffle_test(vector_size, n_samples);
        }
        double shuffle_avg_time = shuffle_total_time / (double)trials;

        // Run erase test <trials> times and calculate average time
        double erase_total_time = 0.0;
        for (int i = 0; i < trials; i++) {
            erase_total_time += erase_test(vector_size, n_samples);
        }
        double erase_avg_time = erase_total_time / (double)trials;

        // Output average times to file
        cout << n_samples << " " << shuffle_avg_time << " " << erase_avg_time << "\n";
        output_file << n_samples << " " << shuffle_avg_time << " " << erase_avg_time << "\n";
    }

    // Close output file
    output_file.close();
}


double shuffle_test(int vector_size, int n_samples) {
    // Initialize vector with integers from 0 to vector_size - 1
    vector<int> vec(vector_size);
    for (int i = 0; i < vector_size; i++) {
        vec[i] = i;
    }

    // Create random number generator
    random_device rd;
    mt19937 g(rd());

    int dummy_index;  // What would be used in actual code

    // Shuffle vector and measure elapsed time
    auto start_time = chrono::high_resolution_clock::now();
    std::shuffle(vec.begin(), vec.end(), g);
    for (int i = 0; i < n_samples; i++) {
        dummy_index = vec[i];
    }
    auto end_time = chrono::high_resolution_clock::now();
    double elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();

    return elapsed_time;
}

double erase_test(int vector_size, int n_samples) {
    // Initialize vector with integers from 0 to vector_size - 1
    vector<int> vec(vector_size);
    for (int i = 0; i < vector_size; i++) {
        vec[i] = i;
    }

    // Create random number generator
    random_device rd;
    mt19937 g(rd());
    
    int dummy_index;  // What would be used in actual code
    int random_index;

    // Erase n_samples random elements and measure elapsed time
    auto start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < n_samples; i++) {
        std::uniform_int_distribution<int> dist(0, vec.size() - 1);
        random_index = dist(g);
        dummy_index = vec[random_index];
        vec.erase(vec.begin() + random_index);
    }
    auto end_time = chrono::high_resolution_clock::now();
    double elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();

    return elapsed_time;
}


void run_test(int vector_size, int n_samples, const string& file_name) {
    // Create a vector of 100 integers
    //int vector_size = 100;
    //int n_samples = 50;

    std::vector<int> myVec(vector_size);
    for (int i = 0; i < vector_size; ++i) {
        myVec[i] = i;
    }

    // Shuffle the vector
    std::random_device rd;
    std::mt19937 g(rd());
    
    int dummy_index;  // What would be used in actual code

    // Measure the time it takes to iterate through the first 10 elements
    auto start1 = std::chrono::high_resolution_clock::now();
    std::shuffle(myVec.begin(), myVec.end(), g);
    for (int i = 0; i < n_samples; ++i) {
        dummy_index = myVec[i];
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time1 = end1 - start1;
    std::cout << "Time to iterate through the first 10 elements: " << time1.count() << " ms" << std::endl;

    // Erase 10 random elements from the vector
    std::shuffle(myVec.begin(), myVec.end(), g);
    auto start2 = std::chrono::high_resolution_clock::now();
    int random_index;
    for (int i = 0; i < n_samples; ++i) {
        //random_index = (int)(g() * myVec.size());
        std::uniform_int_distribution<int> dist(0, myVec.size() - 1);
        random_index = dist(g);
        //cout << "random_index: " << random_index << endl;
        //if ((random_index > myVec.size()) || (random_index < 0)) { cout << "BAD!" << endl; break; }
        dummy_index = myVec[random_index];
        //cout << "dummy_index: " << dummy_index << endl;
        myVec.erase(myVec.begin() + random_index);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time2 = end2 - start2;
    std::cout << "Time to erase 10 random elements: " << time2.count() << " ms" << std::endl;

    // Append the results to the specified file
    std::ofstream output_file;
    output_file.open(file_name, std::ios_base::app);
    if (output_file.is_open()) {
        output_file << n_samples << "," << time1.count() << "," << time2.count() << "\n";
        output_file.close();
    }
    else {
        std::cerr << "Error: Could not open output file!\n";
    }
}