#pragma once

#include <array>

#ifdef CXX_OBJS
using obj_t = struct cpp_Base;
#else
using obj_t = struct c_Base;
#endif

static constexpr size_t objects_nr = 1024 * 1024 * 4;

struct cpp_Base {
	virtual void put_nr(int *addr) noexcept = 0;
	virtual void dummy1(void) noexcept = 0;
	virtual void dummy2(void) noexcept = 0;
	virtual void dummy3(void) noexcept = 0;
};

struct cpp_Deliv1 : public cpp_Base {
	void put_nr(int *addr) noexcept override final;
	void dummy1(void) noexcept override final;
	void dummy2(void) noexcept override final;
	void dummy3(void) noexcept override final;
};

struct cpp_Deliv2 : public cpp_Base {
	void put_nr(int *addr) noexcept override final;
	void dummy1(void) noexcept override final;
	void dummy2(void) noexcept override final;
	void dummy3(void) noexcept override final;
};

struct c_Base {
	void(*put_nr)(int *) noexcept;
	void(*dummy1)(void) noexcept;
	void(*dummy2)(void) noexcept;
	void(*dummy3)(void) noexcept;
};

void generate_rnd_objects(std::array<obj_t *, objects_nr>& objs_arr);
