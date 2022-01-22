#include "calclib.h"

CalcLib::CalcLib()
{
}

double CalcLib::DoIt(int TypeWork, double OperandA, double OperandB, int &errCode)
{
    enum ERR_TYPE{ BAD_OPERATION=1, DIVISION_ZERO };
    enum OPER{SUB,ADD,MULT,DIV};

    if(OperandB == 0){
        errCode = DIVISION_ZERO;
        return 0;
    }

    errCode = 0;

    if( TypeWork == SUB )
    {
        return OperandA-OperandB;
    }
    else if( TypeWork == ADD )
    {
        return OperandA+OperandB;
    }
    else if(TypeWork == MULT)
    {
        return OperandA*OperandB;
    }
    else if(TypeWork == DIV)
    {
        return OperandA/OperandB;
    }

    errCode = BAD_OPERATION;
    return 0;
}

