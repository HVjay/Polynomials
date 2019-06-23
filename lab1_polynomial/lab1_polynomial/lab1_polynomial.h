#ifndef lab1_polynomial
#define lab1_polynomial
#define NOMINMAX

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <istream>
#include <ostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <filesystem>
using namespace std;

class Polynomial {
	// Using vector implementation of Polynomial class
	vector<int> data;
	vector<int> negative_polynomial; // stores least negative exponents first


public:
	// Generation of a random Polynomial that can be no bigger than 1001 terms and no smaller than 1 term
	Polynomial() {

		data.resize(rand() % 1001);

		for (int i = 0; i < data.size(); i++) {
			data[i] = rand() % 1000;
			bool is_negative = rand() % 2;

			if (is_negative) data[i] *= -1;
		}

	}

	// Parameterized Polynomial Constructor that takes an integer array and array size
	Polynomial(int A[], int size) {

		if ((size < 0)) {
			int i1[] = { 0 };
			Polynomial(i1, 0);
		}

		else {
			data.resize(size);

			for (int i = 0; i < size; i++) {
				data[i] = A[i];
			}
		}

	}

	// File input constructor
	Polynomial(string fileName) {
		string s;
		int sTotal = 0;

		ifstream in;
		in.open(fileName.c_str());

		while (!in.eof()) {
			getline(in, s);
			sTotal++;
		}

		ifstream poly_stream;

		poly_stream.open(fileName.c_str());

		int size;
		poly_stream >> size;
		data.resize(size);

		int value = 0;

		for (int i = 0; i < size; i++) {
			poly_stream >> value;
			data[i] = value;
		}
		// Dealing with negative coefficients if there are coefficients remaining (ie more coefficients than size specified)
		if (sTotal != size + 1) {
			int diff = sTotal - size - 1;
			for (int j = 0; j < diff; j++) {
				poly_stream >> value;
				negative_polynomial.push_back(data[0]);
				for (int i = 0; i < data.size()-1;i++) {
					data[i] = data[i + 1];
				}
				data[data.size() - 1] = value;
			}

		}

		poly_stream.close();

	}

	// Method that returns value at particular index of polynomial
	int val_at_index(int index) {
		return data[index];
	}

	// Method that returns size of polynomial when called
	int vector_size() {
		return data.size();
	}

	// Deconstructor
	~Polynomial() {
		data.erase(data.begin(), data.end());
	}

	// Compares to see if two polynomials are equal
	bool operator==(const Polynomial& target) {
		if (data.size() != target.data.size()) return false;
		for (int i = 0; i < data.size(); ++i) {
			if (data[i] != target.data[i]) return false;
		}
		return true;
	}

	// Adds two polynomials
	Polynomial operator+(const Polynomial& target) {
		int max_size = max(data.size(), target.data.size());
		int min_size = min(data.size(), target.data.size());

		int* array = new int[max_size];

		for (int i = 0; i < max_size; i++) {
			if (i < min_size)
				array[i] = data[i] + target.data[i];
			else if (data.size() > min_size)
				array[i] = data[i];
			else
				array[i] = target.data[i];
		}

		Polynomial new_poly(array, max_size);
		return new_poly;
	}

	// Subtracts polynomials
	Polynomial operator-(const Polynomial& target) {
		int max_size = max(data.size(), target.data.size());
		int min_size = min(data.size(), target.data.size());

		int* array = new int[max_size];

		for (int i = 0; i < max_size; i++) {
			if (i < min_size) array[i] = data[i] - target.data[i];
			else if (data.size() > min_size) array[i] = data[i];
			else array[i] = -1 * target.data[i];
		}

		Polynomial new_poly(array, max_size);
		return new_poly;
	}

	// Multiplies two polynomials
	Polynomial operator*(const Polynomial& target) {
		int new_size = data.size() + target.data.size() - 1;

		int* array = new int[new_size];

		for (int k = 0; k < new_size; k++) array[k] = 0;

		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < target.data.size(); j++)
			{
				int power = i + j;
				array[power] += data[i] * target.data[j];
			}
		}
		Polynomial new_poly(array, new_size);
		return new_poly;
	}

	// Derivative method
	Polynomial derivative() {
		// Creates an an array of size n-1 where n is the polynomial size
		int new_size = data.size() - 1;
		int* array = new int[new_size];

		// If the size is equal to 1, returns a polynomial of size 1 and value 0 (since the derivative of a constant is 0)
		if (data.size() == 1) {
			int i1[] = { 0 };
			Polynomial der_poly(i1, 0);
			return der_poly;
		}

		// Else, computes the derivative using drop-down rule of exponents (x^n => n * x^n-1)
		else {
			for (int i = 0; i < new_size; i++) {
				array[i] = data[i + 1] * (i + 1);
			}
			Polynomial der_poly(array, new_size);
			return der_poly;
		}
	}

	// Print method
	void print() {
		for (int i = data.size() - 1; i >= 0; i--)
		{
			if (data[i] != 0) {
				if (i != data.size() - 1) {
					cout << " + ";
				}
				if (data[i] >= 0) {
					cout << data[i] << "x^" << i;
				}
				else cout << "(" << data[i] << ")" << "x^" << i;
			}

		}

		cout << endl;
	}


	// Prints the first 5 terms of the polynomial, used to print and test randomly generated polynomials for "randomness"
	void trunc_print() {
		if (data.size() <= 5) print();
		else {
			for (int i = data.size() - 1; i >= data.size() - 5; i--) {
				if (data[i] != 0) {
					if (i != data.size() - 1)
						cout << " + ";
					if (data[i] >= 0) {
						cout << data[i] << "x^" << i;
					}
					else cout << "(" << data[i] << ")" << "x^" << i;
				}
			}
		}
	}

	// Custom method to resize a polynomial where all values are zero and size is polynomial size >1 to a single-term zero polynomial
	void zero_poly() {
		bool all_zero = true;
		for (int i = 0; i < data.size(); i++) {
			if (data[i] != 0)
				all_zero = false;
		}
		if (all_zero) {
			data.resize(1);
		}
	}

	// Creating friend class that will be able to use methods of Polynomial class (for testing)
	friend class PolynomialTest;

};



#endif 
