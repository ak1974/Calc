#ifndef CALCLIB_H
#define CALCLIB_H

#include "calclib_global.h"

class CALCLIBSHARED_EXPORT CalcLib
{

public:
    CALCLIBSHARED_EXPORT CalcLib();
    CALCLIBSHARED_EXPORT double DoIt(int TypeWork, double OperandA, double OperandB, int &ErrorCode );
};

#endif // CALCLIB_H
