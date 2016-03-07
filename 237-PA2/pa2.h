#pragma once
#include <iostream>
using namespace std;
class data_set {\
public:
	data_set();
	data_set(int initial_capacity);
	data_set &data_set::operator=(const data_set&);
	~data_set(); // destructor

	void insert(double);
	void print(ostream &out) const;
	int size() const;
	int capacity() const;
	double mean() const;
	double median() const;
	double minimum() const;
	double maximum() const;



private:
	void reallocate(); // make array capacity larger

	int curr_cap;
	int curr_size;
	double *points;
};