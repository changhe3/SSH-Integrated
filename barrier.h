#include <thread>

class barrier
{
public:
	barrier(size_t count);
	~barrier();
	
	bool wait();
};