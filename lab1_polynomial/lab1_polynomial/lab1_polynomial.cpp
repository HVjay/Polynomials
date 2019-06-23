
#include "lab1_polynomial.h"



class PolynomialTest {


public:

	bool test_constructors1() {
		bool constructor1 = true;
		//test case of positive
		int i1[] = { 1, 0, 0, 2 };
		Polynomial p1(i1, 4);

		constructor1 = constructor1 && p1.data.size() == 4;
		constructor1 = constructor1 && p1.data[0] == 1;

		//special case of putting size less than 1;
		int i3[] = { 1,3,12 };
		Polynomial p3(i3, -3);

		constructor1 = constructor1 && p3.data.size() == 0;
		return constructor1;
	}

	bool test_random() {
		Polynomial px;
		Polynomial py;
		Polynomial pz;
		bool not_equal = true;

		cout << "Random Polynomial 1: ";
		px.trunc_print();

		cout << "\nRandom Polynomial 2: ";
		py.trunc_print();

		cout << "\nRandom Polynomial 3: ";
		pz.trunc_print();

		cout << "\nAre these random? (Y/N) " << endl;

		char prompt;
		cin >> prompt;

		not_equal = not_equal && prompt == 'Y';

		not_equal = not_equal && !(px.data.size() == py.data.size() && py.data.size() == pz.data.size());
		not_equal = not_equal && !(pz.data[0] == py.data[0] && px.data[0] == py.data[0]);

		return not_equal;
	}

	bool test_add() {

		//adding two polynomials with the same sizes
		int i1[] = { 1, 0, 0, 2 };
		Polynomial p1(i1, 4);

		int i2[] = { 2, 1, 1, 1 };
		Polynomial p2(i2, 4);


		Polynomial p3 = p1 + p2;
		int i4[] = { 3, 1, 1, 3 };

		Polynomial p4(i4, 4);

		//adding two polynomials with different sizes
		int i5[] = { 1, 3, 1 };
		Polynomial p5(i5, 3);
		Polynomial p6 = p5 + p2;

		int i7[] = { 3, 4, 2, 1 };
		Polynomial p7(i7, 4);

		//adding one polynomial with an empty one
		int i8[] = { 0 };
		Polynomial p8(i8, 0);
		Polynomial p9 = p8 + p3;
		bool add_valid = p3 == p4 && p7 == p6 && p9 == p3;
		return add_valid;
	}

	bool test_subtract() {
		//subtracting polynomials of the same size
		int i1[] = { 1, 0, 0, 2 };
		Polynomial p1(i1, 4);

		int i2[] = { 2, 1, 1, 1 };
		Polynomial p2(i2, 4);

		Polynomial p3 = p1 - p2;
		int i4[] = { -1, -1, -1, 1 };
		Polynomial p4(i4, 4);

		//subtracting two polynomials with different sizes
		int i5[] = { 1, 4, 1 };
		Polynomial p5 = { i5,3 };
		Polynomial p6 = p5 - p2;

		int i7[] = { -1, 3, 0, -1 };
		Polynomial p7 = { i7,4 };

		//subtracting one polynomial with an empty one
		int i8[] = { 0 };
		Polynomial p8(i8, 1);
		Polynomial p9 = p1 - p8;

		bool subtract_valid = p3 == p4 && p7 == p6 && p9 == p1;
		return subtract_valid;
	}

	bool test_multiplying() {

		//multipling two polynomials with the same size
		int i10[] = { 2,4,4 };
		Polynomial p10(i10, 3);

		int i11[] = { 5,7,2 };
		Polynomial p11 = Polynomial(i11, 3);

		Polynomial p12 = p10 * p11;
		int i13[] = { 10,34,52,36,8 };
		Polynomial p13(i13, 5);


		//Multiplying polynomials with different sizes

		int i1[] = { 1, 0, 0, 2 };
		Polynomial p1(i1, 4);

		int i2[] = { 0, 0, 2, 0, 1 };
		Polynomial p2(i2, 5);

		Polynomial p3 = p1 * p2;

		int i4[] = { 0, 0, 2, 0, 1, 4, 0, 2 };
		Polynomial p4(i4, 8);


		//Multiplying a polynomial with nothing
		int i5[] = { 0 };
		Polynomial p5(i5, 1);
		Polynomial p7 = p5 * p4;

		p7.zero_poly();

		bool multiply_valid = p7 == p5 && p13 == p12 && p4 == p3;
		return multiply_valid;

	}

	bool test_derivative() {

		//derivative of a constant
		int i1[] = { 1 };
		Polynomial p1(i1, 1);
		p1 = p1.derivative();

		int i2[] = { 0 };
		Polynomial p2(i2, 0);

		//Derivative of a polynomial Test 1
		int i3[] = { 3,5,3 };
		Polynomial p3(i3, 3);
		p3 = p3.derivative();
		int i4[] = { 5,6 };
		Polynomial p4(i4, 2);

		//Derivative of a Polynomial Test 2
		int i5[] = { 1,4,6,2 };
		Polynomial p5(i5, 4);
		p5 = p5.derivative();

		int i6[] = { 4,12,6 };
		Polynomial p6(i6, 3);


		bool derivative_valid = p1 == p2 && p3 == p4 && p5 == p6;
		return derivative_valid;
	}

	bool test_filereading() {

		//Test to correctly read a file
		Polynomial poly1("inputpoly.txt");
		int i1[] = { 1,4,5 };
		Polynomial p1(i1, 3);

		//Test 2
		Polynomial poly2("inputpoly2.txt");
		int i2[] = { 4,5,3 };
		Polynomial p2(i2, 3);

		//Test 3 - more coefficients than the size specified
		Polynomial poly3("inputpoly3.txt");
		int i3[] = { 5,1,2,6 };
		Polynomial p3(i3, 4);

		return poly1 == p1 && poly2 == p2 && poly3== p3 && poly3.negative_polynomial[0]==3;
	}

	void run() {
		assert(test_constructors1());
		cout << "Constructor 1 test passed" << endl;

		assert(test_random());
		cout << "Random constructor test passed" << endl;

		assert(test_equals());
		cout << "Equals operator test passed" << endl;

		assert(test_add());
		cout << "Addition operator test passed" << endl;

		assert(test_subtract());
		cout << "Subtraction operator test passed" << endl;

		assert(test_multiplying());
		cout << "Multiplication operator test passed" << endl;

		assert(test_derivative());
		cout << "Derivative method test passed" << endl;

		assert(test_filereading());
		cout << "File reading constructor test passed" << endl;
	}
};


int main()
{
	srand(time(0));
	PolynomialTest polytest;
	polytest.run();
	return 0;
}
