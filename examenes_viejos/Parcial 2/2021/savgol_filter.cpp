//Program to filter a signal using a Savitzky-Golay filter
//
//The filter is a linear filter that is used to smooth noisy data.
//It is a type of low-pass filter, particularly suited for smoothing
//data with a significant peak.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

//Reads a signal from a file
//The first line of the file contains the number of samples
//The second line contains the samples
//The samples are separated by spaces
//The file must be in the same directory as the program
//The file must be in the format specified above
//The file must exist
//The file must contain a valid signal
//The number of samples must be a positive integer

void readSignal(const string &filename, vector<double> &signal) {
    ifstream file(filename);
    int n;
    file >> n;
    signal.resize(n);
    for (int i = 0; i < n; i++) {
        file >> signal[i];
    }
}

//Writes a signal to a file
//The first line of the file contains the number of samples
//The second line contains the samples
//The samples are separated by spaces
//The file is created in the same directory as the program
//The file is created in the format specified above
//The number of samples must be a positive integer

void writeSignal(const string &filename, const vector<double> &signal) {
    ofstream file(filename);
    file << signal.size() << endl;
    for (int i = 0; i < signal.size(); i++) {
        file << signal[i] << " ";
    }
    file << endl;
}

//Computes the convolution of a signal with a filter
//The convolution is computed using the formula
//y[n] = sum_{k=-M}^{M} x[n-k] h[k]
//where x is the signal, h is the filter, and y is the result
//The signal is padded with zeros at the beginning and at the end
//The signal must have a positive number of samples
//The filter must have an odd number of samples
//The filter must have a positive number of samples

void convolve(const vector<double> &signal, const vector<double> &filter, vector<double> &result) {
    assert(signal.size() > 0);
    assert(filter.size() > 0);
    assert(filter.size() % 2 == 1);
    int M = filter.size() / 2;
    result.resize(signal.size());
    for (int n = 0; n < signal.size(); n++) {
        double sum = 0;
        for (int k = -M; k <= M; k++) {
            if (n - k >= 0 && n - k < signal.size()) {
                sum += signal[n - k] * filter[k + M];
            }
        }
        result[n] = sum;
    }
}

//Computes the Savitzky-Golay filter
//The filter is computed using the formula
//h[k] = sum_{i=0}^{N} c[i] * x[i] * x[i+k]
//where x is the vector of samples, c is the vector of coefficients, and h is the filter
//The filter must have an odd number of samples
//The filter must have a positive number of samples
//The number of samples must be a positive integer
//The number of samples must be greater than or equal to the number of coefficients

void savitzkyGolayFilter(const vector<double> &samples, const vector<double> &coefficients, vector<double> &filter) {
    assert(samples.size() > 0);
    assert(coefficients.size() > 0);
    assert(filter.size() > 0);
    assert(filter.size() % 2 == 1);
    assert(samples.size() >= coefficients.size());
    int N = coefficients.size() - 1;
    int M = filter.size() / 2;
    for (int k = -M; k <= M; k++) {
        double sum = 0;
        for (int i = 0; i <= N; i++) {
            sum += coefficients[i] * samples[i] * samples[i + k];
        }
        filter[k + M] = sum;
    }
}


