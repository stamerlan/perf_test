#include "objects.h"
#include <random>
#include <cassert>

void cpp_Deliv1::put_nr(int *addr) noexcept
{
	*addr = 1;
}

void cpp_Deliv1::dummy1(void) noexcept
{
}

void cpp_Deliv1::dummy2(void) noexcept
{
}

void cpp_Deliv1::dummy3(void) noexcept
{
}

void cpp_Deliv2::put_nr(int *addr) noexcept
{
	*addr = 2;
}

void cpp_Deliv2::dummy1(void) noexcept
{
}

void cpp_Deliv2::dummy2(void) noexcept
{
}

void cpp_Deliv2::dummy3(void) noexcept
{
}

static void c_deliv1_put_nr(int *addr) noexcept
{
	*addr = 1;
}

static void c_deliv2_put_nr(int *addr) noexcept
{
	*addr = 2;
}

template <typename T>
struct obj_allocator {
	static T *alloc(int type);
};

struct cpp_Base *obj_allocator<struct cpp_Base>::alloc(int type)
{
	switch (type) {
	case 0:
		return new cpp_Deliv1;
	case 1:
		return new cpp_Deliv2;
	default:
		assert(false);
		return nullptr;
	}
}

struct c_Base *obj_allocator<struct c_Base>::alloc(int type)
{
	struct c_Base *obj = new c_Base;

	switch (type) {
	case 0:
		obj->put_nr = c_deliv1_put_nr;
		break;
	case 1:
		obj->put_nr = c_deliv2_put_nr;
		break;
	default:
		assert(false);
	}

	return obj;
}

void generate_rnd_objects(std::array<obj_t *, objects_nr>& objs_arr)
{
	std::random_device rand_dev;
	std::mt19937 rng;
	rng.seed(rand_dev());

	std::uniform_int_distribution<> dist(0, 1);

	for (auto& i : objs_arr)
		i = obj_allocator<obj_t>::alloc(dist(rng));
}

