/****************************************************************
* Title:       CS 237 Programming Assignment #2
* Author:      Joe Opseth & Jens Myklebust
* Created:     22 February 2016
* Modified:    13 March 2016
* Description: Tests a dynamically-allocated, sorted array class.
               Includes bonus remove function & tests.
* Team:        Group 5
****************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include "pa2.h"

using namespace std;

/*  Begin data_set definitions  */


/*
 * Default constructor for data_set
 * Sets capacity to 10
 * Input: none
 * Output: a data_set object
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
Copy constructor for deep copies
Input: A data_set object
Output: A data_set object
*/
data_set::data_set(const data_set &original) {
	curr_cap = original.curr_cap;
	curr_size = original.curr_size;
	points = new double[curr_cap];
	for (int i = 0; i < curr_size; i++) {
		points[i] = original.points[i];
	}
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

/*
 * Expand the capacity of the data_set array
 * Input: none
 * Output: none
 */
void data_set::reallocate() {
	curr_cap *= 2;
	double* temp = new double[curr_cap];
	for (int i = 0; i < curr_size; i++)
		temp[i] = points[i];

	delete[] points;
	points = temp;
}

/*
 * Delete the points object when data_set goes out of scope
 * Input: none
 * Output: none
 */
data_set::~data_set()
{
	delete[] points;
	points = NULL;
}

/* 
 * Put a double in the array
 * Puts a double into the array, keeping the array sorted
 * by shifting greater numbers to the right
 * Input: A double
 * Output: None
 */
void data_set::insert(double value)
{
	if (curr_size == curr_cap)
	{
		reallocate();
	}
	if (curr_size == 0) {
		points[0] = value;
		curr_size = 1;
	}
	else {
		for (int i = curr_size - 1; i >= 0; i--) {
			if (value > points[i]) {
				points[i + 1] = value;
				curr_size++;
				return;
			}
			else if (i == 0) {
				points[i + 1] = points[i];
				points[0] = value;
				curr_size++;
				return;
			}
			else {
				points[i + 1] = points[i];
			}
		}
	}
}

/*
 * Remove a double from the array.
 * Takes a double as input and removes one
 * instance of it if it is found;
 * otherwise, does nothing.
 * Returns a boolean indicating if the value was found.
 * Input: double
 * Output: bool
 */
bool data_set::remove(double rm_me) {
	bool found = false;
	int i = 0;
	while (!found && i < curr_size) {
		if (points[i] == rm_me)
			found = true;
		else
			i++;
	}
    /* 
	 * If double was found, decrement curr_size,
	 * shift remaining values to the left
	 * and make the last value null
	 */
	if (found) {
		--curr_size;
		for (int j = i; j < curr_size; j++) {
			points[j] = points[j + 1];
		}
		points[curr_size] = NULL;
	}
	return found;
}

/*
 * Return the double value found at index.
 * Throws an error if the value is not within
 * [0, curr_size - 1] .
 * Input: int
 * Output: double
 */
double data_set::get(int index) {
	if (index >= 0 && index < curr_size) {
		return points[index];
	}
	else {
		throw runtime_error("Invalid index!");
	}
}


/* 
Print the values in the data set
Values are printed in a set of brackets
e.g. { 3, 4.2, 7, 8.8 }
Input: an ostream object
Output: None
*/
void data_set::print(ostream &out) const
{
	if (curr_size <= 0) {
		out << "{ }\n";
	}
	else {
		out << "{ " << points[0];
		int i = 1;
		while (i < curr_size) {
			out << ", " << points[i];
			i++;
		}
		out << " }\n";
	}
}

/*
Return the current size of the array
Input: none
Output: int
*/
int data_set::size() const
{
	return curr_size;
}

/*
Return the current capacity of the array
Input: None
Output: int
*/
int data_set::capacity() const
{
	return curr_cap;
}

/*
Return the mean of the values in the array
The array cannot be empty
Input: none
Output: double
*/
double data_set::mean() const
{
	if (curr_size == 0) {
		throw runtime_error("Requested mean of empty array!");
	}
	else {
		double sum = 0;
		for (int i = 0; i < curr_size; i++) {
			sum += points[i];
		}
		return sum / curr_size;
	}
}

/*
Returns the median value of the values in the array
Array cannot be empty
Input: none
Output: double

*/
double data_set::median() const
{
	if (curr_size <= 0) {
		throw runtime_error("Empty array!");
	}
	else {
		double median = NULL;
		if (curr_size % 2 == 0)
			median = (points[curr_size / 2] + points[curr_size / 2 - 1]) / 2;
		else {
			median = points[(curr_size / 2)];
		}
		return median;
	}
}

/*
Returns the minimum value in the sorted array
Input: none
Output: double
*/
double data_set::minimum() const
{
	if (curr_size <= 0) {
		throw runtime_error("Empty array!");
	}
	else {
		return points[0];
	}
}

/* 
Returns the maximum value in the sorted array
Input: none
Output: double
*/
double data_set::maximum() const
{
	if (curr_size <= 0) {
		throw runtime_error("Empty array!");
	}
	else {
		return points[curr_size - 1];
	}
}


/*  End data_set definitions  */

void pause_237(bool);
int test_data_set();


/*
Tests the data_set class
First, runs a set of tests on the class functions and
displays the number that failed
Second, provides a loop for the user to enter values,
and then displays the size, mean, median, maximum, and
minimum
Input: none
Output: int
*/
int main()
{
	int failed = test_data_set();

	// loop for input

	bool done = false;
	double input;
	string bad_input;

	data_set myds;

	do {
		cout << "Current data set:" << endl;
		myds.print(cout);
		cout << endl;
		cout << "Enter a number: ";
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			getline(cin, bad_input);
			if (bad_input == "quit")
				done = true;
			else
				cout << "That's not a number!\n";
		}
		else {
			myds.insert(input);
		}
		cout << endl;
	} while (!done);

	cout << endl;

	// display information about data set
	cout << "Final data set: " << endl;
	myds.print(cout);
	cout << endl;

	cout << left << setw(15) << "Size:" << myds.size() << endl;
	cout << left << setw(15) << "Mean:" << myds.mean() << endl;
	cout << left << setw(15) << "Median:" << myds.median() << endl;
	cout << left << setw(15) << "Maximum:" << myds.maximum() << endl;
	cout << left << setw(15) << "Minimum:" << myds.minimum() << endl;

	cout << endl << endl;

	// Remove all values from data set and print empty data set
	for (int i = myds.size() - 1; i >= 0; --i) {
		myds.remove(myds.get(0));
	}
	cout << "Cleared data set: " << endl;
	myds.print(cout);
	cout << endl;

	pause_237(false);
	return 0;
}

/*
Pause the program
Pauses the program and clears the newline if one was entered
Input: boolean
Output: none
*/
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

/*
Test data set functions
Runs a series of tests on the data set 
class functions and then
displays how many failed
Input: none
Output: int
*/
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

	/*
	Tests for mean
	1. Test for exception on empty array
	2. Test for correct value from working array
	*/
	curr_test++;
	caught = false;
	try {
		double x = empty.mean();
	}
	catch (exception e) {
		caught = true;
	}
	if (!caught) {
		cerr << "Test " << curr_test << " failed: missing exception" << endl;
		failed++;
	}
	curr_test++;
	if (working.mean() != 4.5) {
		cerr << "Test " << curr_test << " failed: got " << working.mean() << ", expected 4.5." << endl;
		failed++;
	}

	/*
	Tests for maximum
	1. Test for exception on empty array
	2. Test for correct value from working array
	*/
	curr_test++;
	caught = false;
	try {
		double x = empty.maximum();
	}
	catch (exception e) {
		caught = true;
	}
	if (!caught) {
		cerr << "Test " << curr_test << " failed: missing exception" << endl;
		failed++;
	}
	curr_test++;
	if (working.maximum() != 5.5) {
		cerr << "Test " << curr_test << " failed: got " << working.maximum() << ", expected 5.5 ." << endl;
		failed++;
	}

	/*
	  Tests for median
	  1. Test working set
	  2. Add a value and test working set again
	*/
	curr_test++;
	if (working.median() != 4.5) {
		cerr << "Test " << curr_test << " failed: got " << working.median() << ", expected 4.5 ." << endl;
		failed++;
	}
	curr_test++;
	data_set median_copy(working);
	median_copy.insert(5.5);
	if (median_copy.median() != 5) {
		cerr << "Test " << curr_test << " failed: got " << median_copy.median() << ", expected 5 ." << endl;
		failed++;
	}
	/*
	 * Tests for remove
	 * Make a copy of working
	 * 1. Remove 3.5 and verify removed
	 * 2. Insert 3.5, remove 4.5 and verify removed & shifted
	 * 3. Remove 7 and verify nothing changed
	 * 4. Remove remaining values & verify all removed
	 * 5. Remove something and verify data_set is not changed
	 */
	data_set rm_copy(working);
	bool removed;
	curr_test++;
	{
		ostringstream rm_expected;
		ostringstream rm_actual;
		data_set remove_verify(10);
		remove_verify.insert(4.5);
		remove_verify.insert(5.5);
		remove_verify.print(rm_expected);
		removed = rm_copy.remove(3.5);
		rm_copy.print(rm_actual);
		if (!removed || rm_expected.str() != rm_actual.str()) {
			cout << "Test " << curr_test << " failed; 3.5 was not properly removed.\n";
			failed++;
		}
	}
	curr_test++;
	{
		ostringstream rm_expected;
		ostringstream rm_actual;
		data_set remove_verify(10);
		remove_verify.insert(3.5);
		remove_verify.insert(5.5);
		remove_verify.print(rm_expected);
		rm_copy.insert(3.5);
		removed = rm_copy.remove(4.5);
		rm_copy.print(rm_actual);
		if (!removed || rm_expected.str() != rm_actual.str()) {
			cout << "Test " << curr_test << " failed; 4.5 was not properly removed.\n";
			failed++;
		}
	}
	curr_test++;
	{
		ostringstream rm_expected;
		ostringstream rm_actual;
		data_set remove_verify(working);
		remove_verify.print(rm_expected);
		rm_copy = working;
		removed = rm_copy.remove(7);
		rm_copy.print(rm_actual);
		if (removed || rm_expected.str() != rm_actual.str()) {
			cout << "Test " << curr_test << " failed; 7 was not removed properly or deep copy operator may have failed.\n";
			failed++;
		}
	}
	curr_test++;
	ostringstream rm_expected;
	ostringstream rm_actual;
	data_set remove_verify(10); // expected data_set is empty
	for (int i = rm_copy.size() - 1; i >= 0; --i) {
		rm_copy.remove(rm_copy.get(0));
	}
	remove_verify.print(rm_expected);
	rm_copy.print(rm_actual);
	if (rm_expected.str() != rm_actual.str()) {
		cout << "Test " << curr_test << " failed; data set was not properly cleared.\n";
		failed++;
	}
	curr_test++;
	removed = rm_copy.remove(1.1);
	if (removed || rm_expected.str() != rm_actual.str()) {
		cout << "Test " << curr_test << " failed; removing value from empty data set caused an error.\n";
		failed++;
	}
	
	// Output for successful test

	if (failed == 0)
	{
		cerr << "All tests passed." << endl;
	}

	// Add an extra blank line after the tests.
	cerr << endl;

	return 0;
}
