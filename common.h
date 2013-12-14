#ifndef VIVO_COMMON_H_
#define VIVO_COMMON_H_
#include "log.h"

typedef unsigned char           ubyte_t;
typedef unsigned int            uint32_t;
typedef unsigned short int      uint16_t;
typedef unsigned long long int  uint64_t;

#define UNLIKELY(x)      __builtin_expect((x), 0)
#define LIKELY(x)        __builtin_expect((x), 1)

#define _CHECK(op1, op2, op) \
    do{\
        if(!(UNLIKELY(op1 op op2))){\
            std::cout<<__FILE__<<":"<<__LINE__<<":"<<#op1<<" "<<#op<<" "<<#op2<<std::endl;\
            *(int*)(0) = 0;\
        }\
    }while(0)


#ifdef VIVO_DEBUG
#define DECHECK(e)              DECHECKNE((e), NULL)
#define DECHECKEQ(e, op2)       CHECK((e), (op2), ==)
#define DECHECKNE(e, op2)       CHECK((e), (op2), !=)

#define CHECK(op1, op2, op)     _CHECK(op1, op2, op)

#else
#define DECHECK(e)
#endif

#endif
