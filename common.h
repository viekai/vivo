#ifndef VIVO_COMMON_H_
#define VIVO_COMMON_H_
#include "log.h"
#include <unistd.h>

typedef unsigned char           ubyte_t;
typedef unsigned int            uint32_t;
typedef unsigned short int      uint16_t;
typedef unsigned long long int  uint64_t;
typedef int                     int32_t;

#define UNLIKELY(x)      __builtin_expect((x), 0)
#define LIKELY(x)        __builtin_expect((x), 1)

// DISALLOW_COPY_AND_ASSIGN disallows the copy and operator= functions.
// It goes in the private: declarations in a class.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

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

#define ABORT() \
    do{\
        std::cout<<__FILE__<<":"<<__LINE__<<":"<<"+++++++++abort+++++++++"<<std::endl;\
        (*(int*)0 = 0);\
    }while(0)

#else
#define DECHECK(e)
#endif

#define MANAGED __attribute__((aligned(4)))
#endif
