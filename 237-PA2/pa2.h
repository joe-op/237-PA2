/****************************************************************
* Title:       CS 237 Programming Assignment #2
* Author:      Joe Opseth & Jens Myklebust
* Created:     22 February 2016
* Modified:
* Description: Tests a dynamically-allocated, sorted array class.
* Team:        Group 5
****************************************************************/
#pragma once
#include <iostream>
class data_set {
public:
	data_set();
	data_set(int initial_capacity);
	data_set &data_set::operator=(const data_set&);
	data_set(const data_set &original);
	~data_set(); // destructor

	void insert(double);
	bool remove(double);
	void print(std::ostream &out) const;
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