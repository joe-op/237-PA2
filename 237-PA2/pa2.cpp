/****************************************************************
* Title:       CS 237 Programming Assignment #2
* Author:      Joe Opseth & Jens Myklebust
* Created:     22 February 2016
* Modified:
* Description: Tests a dynamically-allocated, sorted array class.
* Team:        Group 5
****************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include "pa2.h"

using namespace std;


/*
 * Default constructor for data_set
 * Sets capacity to 10
 */
data_set::data_set()
{
	curr_cap = 10;
	curr_size = 0;
	points = new double[curr_cap];
}

/*
 * Alternate constructor for data_set
 * Input: capacity (int)
 * Output: A data_set object
 */
data_set::data_set(int initial_capacity)
{
	curr_cap = initial_capacity;
	curr_size = 0;
	points = new double[curr_cap];
	// initial capacity, verify()

}

/*
 * Allow = to be used for deep copies
 * Input: A data_set object
 * Output: A copy of the data_set object
 */
data_set &data_set::operator=(const data_set &original)
{
	if (this == &original) {
		return *this;
	}
	else
	{
		curr_cap = original.curr_cap;
		curr_size = original.curr_size;
		delete[] points;
		points = new double[curr_cap];
		for (int i = 0; i < curr_size; i++) {
			points[i] = original.points[i];
		}
		return *this;
	}
}

void data_set::reallocate() {
	curr_cap *= 2;
	double* temp = new double[curr_cap];
	for (int i = 0; i < curr_size; i++)
		temp[i] = points[i];

	delete[] points;
	points = temp;
}

/*
 * 
 */
data_set::~data_set()
{
	delete[] points;
	points = NULL;
}

void data_set::insert(double value)
{

}

void data_set::print(ostream &out) const
{

}

int data_set::size() const
{
	return 0;
}

int data_set::capacity() const
{
	return 0;
}

double data_set::mean() const
{
	return 0.0;
}

double data_set::median() const
{
	return 0.0;
}

double data_set::minimum() const
{
	return 0.0;
}

double data_set::maximum() const
{
	return 0.0;
}

int main()
{
	int failed = test_data_set();

	// TODO: Read doubles in a loop and add them to a data set.  Repeat
	//   the loop on invalid input, then end when the user types "quit".
	//   Print the data set before each prompt.

	// TODO: Print the final data set, and compute its statistics:
	//   size, mean, minimum, maximum, and median.

	pause_237(false);
	return 0;
}

void pause_237(bool have_newline)
{
	if (have_newline) {
		// Ignore the newline after the user's previous input.
		cin.ignore(200, '\n');
	}

	// Prompt for the user to press ENTER, then wait for a newline.
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(200, '\n');
}

int test_data_set()
{
	// Current test number.  Be sure to increment this before each test!
	int curr_test = 0;

	// Number of failed tests.
	int failed = 0;

	cerr << "Testing..." << endl;

	// Test 1: does the default constructor create an empty data set?
	//   Tests: default constructor, size method
	curr_test++;
	data_set empty;
	if (empty.size() != 0) {
		cerr << "Test " << curr_test << " failed: size is "
			<< empty.size() << ", should be 0." << endl;
		failed++;
	}

	// Test 2: does the default constructor set the capacity correctly.
	//   Tests: default constructor, capacity method
	curr_test++;
	if (empty.capacity() != 10) {
		cerr << "Test " << curr_test << " failed: capacity is "
			<< empty.capacity() << ", should be 10." << endl;
		failed++;
	}

	// Test 3: does the integer constructor work?
	//   Tests: int constructor, capacity method.
	curr_test++;
	data_set tiny(1);
	if (tiny.capacity() != 1) {
		cerr << "Test " << curr_test << " failed: capacity is "
			<< tiny.capacity() << ", should be 10." << endl;
		failed++;
	}

	// Test 4: and is that data set empty, too?
	//   Tests: int constructor, size method.
	curr_test++;
	if (tiny.size() != 0) {
		cerr << "Test " << curr_test << " failed: size is "
			<< tiny.size() << ", should be 0." << endl;
		failed++;
	}

	// Test 5: can we insert?
	//   Tests: int constructor, insert and size methods.
	curr_test++;
	data_set working(2);
	working.insert(4.5);
	if (working.size() != 1) {
		cerr << "Test " << curr_test << " failed: size is "
			<< working.size() << ", should be 1." << endl;
		failed++;
	}

	// Test 6: can we insert over the current capacity?
	//   Tests: int constructor, insert and size methods.
	curr_test++;
	working.insert(5.5);
	working.insert(3.5);
	if (working.size() != 3) {
		cerr << "Test " << curr_test << " failed: size is "
			<< working.size() << ", should be 3." << endl;
		failed++;
	}

	// Test 7: did that update the capacity?
	//   Tests: int constructor, insert and capacity methods.
	curr_test++;
	if (working.capacity() < 3) {
		cerr << "Test " << curr_test << " failed: capacity is "
			<< working.capacity() << ", should be at least 3." << endl;
		failed++;
	}

	// Test 8: does the vector print in order and with the correct
	//         formatting?
	//   Tests: int constructor, insert and print methods.
	//   Uses an ostringstream to capture the output.
	curr_test++;
	ostringstream out;
	working.print(out);
	string expected = "{ 3.5, 4.5, 5.5 }\n";
	if (out.str() != expected) {
		cerr << "Test " << curr_test << " failed:" << endl;
		cerr << "Actual output:   " << out.str() << endl;
		cerr << "Expected output: " << expected << endl;
		failed++;
	}

	// Test 9: does the copy constructor faithfully copy?
	//   Tests: copy constructor and print methods.
	curr_test++;
	data_set copy(working);
	ostringstream out_copy;
	copy.print(out_copy);
	if (out_copy.str() != out.str()) {
		cerr << "Test " << curr_test << " failed:" << endl;
		cerr << "Original: " << out.str() << endl;
		cerr << "Copy:     " << out_copy.str() << endl;
		failed++;
	}

	// Test 10: did it do a deep copy?  Changing the copy shouldn't change
	//          the original.
	//   Tests: copy constructor, insert and print methods.
	curr_test++;
	copy.insert(2.0);

	ostringstream out_orig;
	working.print(out_orig);
	if (out_orig.str() != expected) {
		cerr << "Test " << curr_test << " failed:" << endl;
		cerr << "Actual output:   " << out_orig.str() << endl;
		cerr << "Expected output: " << expected << endl;
		failed++;
	}

	// Test 11: does the assignment operator change the size?
	//   Tests: assignment operator, size method.
	curr_test++;
	tiny = working;
	if (tiny.size() != 3) {
		cerr << "Test " << curr_test << " failed: size is "
			<< tiny.size() << ", should be 3." << endl;
		failed++;
	}

	// Test 11: did the assignment operator copy the values?
	//   Tests: assignment operator, print method.
	curr_test++;
	ostringstream out_tiny;
	working.print(out_tiny);

	if (out_tiny.str() != out_orig.str()) {
		cerr << "Test " << curr_test << " failed:" << endl;
		cerr << "Original: " << out_orig.str() << endl;
		cerr << "Copy:     " << out_tiny.str() << endl;
		failed++;
	}

	// Test 12: did it do a deep copy?
	//   Tests: assignment operator, insert and print methods.
	curr_test++;
	tiny.insert(9.0);

	ostringstream out_orig2;
	working.print(out_orig2);

	if (out_orig2.str() != expected) {
		cerr << "Test " << curr_test << " failed:" << endl;
		cerr << "Actual output:   " << out_orig2.str() << endl;
		cerr << "Expected output: " << expected << endl;
		failed++;
	}

	// Test 13: does minimum() work?
	//   Tests: insert and minimum methods
	curr_test++;
	if (working.minimum() != 3.5) {
		cerr << "Test " << curr_test << " failed: got "
			<< working.minimum() << ", expected 3.5." << endl;
		failed++;
	}

	// Test 14: does minimum throw an exception on an empty
	//          vector?
	//   Tests: empty constructor, minimum method
	curr_test++;

	bool caught = false;
	// We need a try/catch because we expect an exception.
	try {
		double x = empty.minimum();
	}
	catch (exception e) {
		caught = true;
	}
	if (!caught) {
		cerr << "Test " << curr_test << " failed: missing exception" << endl;
		failed++;
	}

	// TODO: implement two tests each for mean, maximum, and median.

	// If you are doing the bonus, remember the five test cases for remove!

	if (failed == 0)
	{
		cerr << "All tests passed." << endl;
	}

	// Add an extra blank line after the tests.
	cerr << endl;

	return 0;
}
