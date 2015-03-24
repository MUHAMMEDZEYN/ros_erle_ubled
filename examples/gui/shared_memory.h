#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

//standard
#include <vector>
#include <pthread.h>
#include <iostream>

class Shared_Memory
{
public:
    Shared_Memory();

    std::vector<int> getUbled_status();
    void setUbled_status(std::vector<int>);

private:
    std::vector<int> ubled_status;
    pthread_mutex_t mutex;

};

#endif // SHARED_MEMORY_H
