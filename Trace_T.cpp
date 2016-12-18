#include <cstdlib>
#include <iostream>
#include "Trace_T.h"

bool Trace_T::c_ready = false;

Trace_T::Trace_T()
{
	i_mapEntry.clear();
	Trace_T::c_ready = true;
}

void Trace_T::add(void* p, const char* file, long line)
{
	if (Trace_T::c_ready)
	{
		i_mapEntry[p] = Entry_T(file, line);
	}
}

void Trace_T::reduce(void* p)
{
	if (Trace_T::c_ready)
	{
		std::map<void*, Entry_T>::const_iterator it;
		it = i_mapEntry.find(p);

		if (it != i_mapEntry.end())
		{
			i_mapEntry.erase(it);
		}
	}
}

void Trace_T::dump() const
{
	if (i_mapEntry.size() > 0)
	{
		std::map<void*, Entry_T>::const_iterator it;

		for (it = i_mapEntry.begin(); it != i_mapEntry.end(); ++it)
		{
			std::cout << "file:" << it->second.file() << std::endl
				<< "line:" << it->second.line() << std::endl;
		}
	}
}

Trace_T::~Trace_T()
{
	dump();
	Trace_T::c_ready = false;
}

Trace_T f_trace;

void* operator new(size_t size, const char* file, long line)
{
	void* p = malloc(size);
	f_trace.add(p,file, line);

	return p;
}
void operator delete(void* p)
{
	if (Trace_T::c_ready)
	{
		f_trace.reduce(p);
	}
	free(p);
}