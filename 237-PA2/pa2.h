#pragma once
class data_set {\
public:
	data_set();
	data_set(const data_set&);
	~data_set(); // destructor
	data_set operator=(const data_set&);

private:
	void reallocate(); // make array capacity larger

	int curr_cap;
	int curr_size;
	double *points;
};