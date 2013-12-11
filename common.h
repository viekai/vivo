#ifndef VIVO_COMMON_H_
#define VIVO_COMMON_H_
#include "log.h"

#define _CHECK(op1, op2, op, msg) \
    do{\
        if(!(UNLIKELY(op1 op op2))){\
            Log::LOGE(msg);\
            *(int*)(0) = 0;\
        }\
    }while(0)


#ifdef VIVO_DEBUG
#define DECHECK(e, msg)      CHECK(e, NULL, !=, msg)
#define CHECK(op1, op2, op, msg) _CHECK(op1, op2, op, msg)
#else
#define DECHECK(e)
#endif

//#define DECHECK_EQ()
#endif
