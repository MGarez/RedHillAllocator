#include "allocator.h"

StackAllocator::StackAllocator(size_t size)
	: m_total_size(size), m_offset(0)
{
	m_start_ptr = ::operator new(m_total_size);
}

StackAllocator::~StackAllocator()
{
	::operator delete(m_start_ptr);
	m_start_ptr = nullptr;
}

void* StackAllocator::Allocate(size_t size, size_t alignment)
{
	void* current_ptr = static_cast<char*>(m_start_ptr) + m_offset;

	size_t padding = 0;
	if (reinterpret_cast<uintptr_t>(current_ptr) % alignment != 0)
	{
		padding = alignment - (reinterpret_cast<uintptr_t>(current_ptr) % alignment);
	}

	if (m_offset + size + padding > m_total_size)
	{
		return nullptr;
	}

	m_offset += size + padding;

	void* aligned_ptr = static_cast<char*>(current_ptr) + padding;

	return aligned_ptr;
}

void StackAllocator::Clear()
{
	m_offset = 0;
}
