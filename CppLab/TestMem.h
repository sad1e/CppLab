#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <map>

std::map<void*, size_t> map_alloc;

/*
void* operator new(size_t size)
{
    void* p = malloc(size);
    if (p == nullptr)
        throw std::bad_alloc();

    printf("new: p = %p, size = %zd\n", p, size);

    if (map_alloc.contains(p))
    {
        printf("map_alloc contains %p\n", p);
    }
    else
    {
        map_alloc[p] = size;
    }

    return p;
}

void operator delete(void* p) noexcept
{
    printf("delete: p = %p\n", p);

    map_alloc.erase(p);

    free(p);
}
*/
#if 0

void
test()
{

    int *pi = new int;
    short *ps = new short;

    delete pi;
    delete ps;


}

#endif
