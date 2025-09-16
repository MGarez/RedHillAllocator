#include <iostream>

#include "allocator.h" 

struct Transform
{
	int32_t x;
	int32_t y;
	int32_t z;
};

int main()
{

	StackAllocator frame_allocator(1024 * 1024);

	std::cout << "--- Simulating Game Frames ---\n";

	for (uint16_t i = 0; i < 10; ++i)
	{
		std::cout << "\n--- Frame " << i << " ---\n";

		auto* p_int = new (frame_allocator.Allocate(sizeof(int), alignof(int))) int(i * 10);
		auto* p_transform = new (frame_allocator.Allocate(sizeof(Transform), alignof(Transform))) Transform();
		auto* p_char_array = new (frame_allocator.Allocate(23)) char[23];

		std::cout << "Integer Allocated at:     " << p_int << " (value: " << *p_int << ")\n";
		std::cout << "Transform Allocated at:   " << p_transform << "\n";
		std::cout << "Char array Allocated at:  " << static_cast<void*>(p_char_array) << "\n";

		frame_allocator.Clear();

		std::cout << "--- Frame Allocator Cleared ---\n";
	}

	return 0;
}