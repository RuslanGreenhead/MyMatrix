//
// Allocator #1
//

#pragma once

template<typename T>
class Allocator {
public:
	static T* allocate(size_t count){
		if (count > 0) {
			//void* ptr = ::operator new(cout * sizeof(T));
			return reinterpret_cast<T*>(::operator new(count * sizeof(T)));
		}else{
			return nullptr;
		}
	}

	static void deallocate(T* ptr) {
		//void* ptr_T = reinterpret_cast<void*>(ptr);
		::operator delete(reinterpret_cast<void*>(ptr));
	}

	template<typename ... Types>
	static void construct(T* ptr, const Types& ... args) {
		new(ptr) T(args...);
	}

	static void destroy(T* ptr) {
		ptr->~T();
	}
};