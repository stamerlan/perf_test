#include <iostream>
#include <chrono>
#include <fstream>
#include "objects.h"

constexpr size_t test_nr = 512;
int main(void)
{
	static std::array<obj_t *, objects_nr> objs_arr;
	static std::array<int, objects_nr> data_arr;

	std::array<std::chrono::microseconds, test_nr> time;

	generate_rnd_objects(objs_arr);

	/* virtual method call */
	for (auto& d : time) {
		using namespace std::chrono;

		auto start = high_resolution_clock::now();
		auto p = data_arr.data();
		for (auto& i : objs_arr)
			i->put_nr(p++);
		auto end = high_resolution_clock::now();

		d = duration_cast<microseconds>(end - start);
	}

	/* duration */
	std::ofstream out_f("duration.csv");
	for (auto& i : time)
		out_f << i.count() << ",";

	/* free */
	for (auto& i : objs_arr)
		delete i;

	return 0;
}

