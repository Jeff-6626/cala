#ifndef	TRACE_H_
#define TRACE_H_

#include <map>

void* operator new(size_t, const char* file, long line);
void operator delete(void* p);

class Trace_T
{
public:
	class Entry_T
	{
	public:
		Entry_T(const char* pFile = 0, long line = 0)
			: i_file(pFile), i_line(line)	{}
		const char* file() const
		{
			return i_file;
		}
		long line() const
		{
			return i_line;
		}
	private:
		const char* i_file;
		long i_line;
	};

public:
	Trace_T();
	void add(void* p,const char* file, long line);
	void reduce(void* p);
	void dump() const;
	~Trace_T();
private:
	std::map<void*, Entry_T> i_mapEntry;
public:
	static bool c_ready;
};

#endif	//TRACE_H_