#include "shared_memory.h"

Shared_Memory::Shared_Memory()
{
    if (pthread_mutex_init(&mutex, NULL) != 0){
        std::cout << "mutex init failed" << std::endl;
    }
}

std::vector<int> Shared_Memory::getUbled_status()
{
    std::vector<int> result;
    pthread_mutex_lock( &mutex );
    result = ubled_status;
    pthread_mutex_unlock( &mutex );
    return result;
}

void Shared_Memory::setUbled_status(std::vector<int> v)
{
    pthread_mutex_lock( &mutex );
    this->ubled_status = v;
    pthread_mutex_unlock( &mutex );
}
