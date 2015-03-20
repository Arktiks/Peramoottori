#ifdef _DEBUG
	#ifndef MEMORY_H
	#define MEMORY_H

	#include <cstdlib>
	#include <new>
	#include <iostream>

/*inline void *operator new(size_t, const char*, int);
inline void *operator new[](size_t, const char*, int);
inline void operator delete(void*);
inline void operator delete[](void*);
inline void deleter(const char*, int);*/

	class Memory
	{
	public:

		static Memory* GetInstance();
		void DestroyInstance();

		static char delete_name;
		static int delete_line;

	private:

		static Memory* instance;

		Memory() {};
		~Memory() {};

	};



	void *operator new(size_t size, const char* file, int line)
	{
		void *ptr = malloc(size);
		if(ptr == NULL)
		{
			std::cout << "No memory to allocate." << std::endl;
			exit(-1);
		}

		std::cout << "New: " << file << " (" << line << ")" << std::endl;
		return ptr;
	}

	void *operator new[](size_t size, const char *file, int line)
	{
		return operator new(size, file, line);
	}

	void deleter(const char *file, int line)
	{
		Memory::GetInstance()->delete_name = *file;
		Memory::GetInstance()->delete_line = line;
	}

	void operator delete(void *ptr)
	{
		free(ptr);
		std::cout << "Delete: " << Memory::GetInstance()->delete_name << " (" << Memory::GetInstance()->delete_line << ")" << std::endl;
	}

	void operator delete[](void *ptr)
	{
		operator delete(ptr);
	}

	#define new new(__FILE__, __LINE__)
	#define delete deleter(__FILE__, __LINE__)

	#endif
#endif