#pragma once

#include <cstddef>
#include <algorithm>


class StackAllocator
{
public:

	explicit StackAllocator(size_t size);
	~StackAllocator();
	StackAllocator(const StackAllocator&) = delete;
	StackAllocator& operator=(const StackAllocator&) = delete;
	StackAllocator(StackAllocator&&) noexcept = delete;
	StackAllocator& operator=(StackAllocator&&) noexcept = delete;

	void* Allocate(size_t size, size_t alignment = alignof(std::max_align_t));
	void Clear();

private:

	void* m_start_ptr = nullptr;

	size_t m_total_size;

	size_t m_offset;
};