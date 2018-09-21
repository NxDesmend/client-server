#include <cstdio>



#ifndef COMMON_H
#define COMMON_H

#define EMP "emp"

#define LOG_INFO(format, ...) printf("%s %s " format "[%s:%d]""\n", \
                                     __DATE__, __TIME__, ##__VA_ARGS__, \
                                     __FILE__, __LINE__)

#endif