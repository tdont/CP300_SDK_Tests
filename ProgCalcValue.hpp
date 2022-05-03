#ifndef PROGCALC_VALUE_H
#define PROGCALC_VALUE_H

#include "ClassPad.h"
#include "progCalcShared.h"

class ProgClassValue
{
    public:
    ProgClassValue(DWORD value, mode_signed_t mode, length_t length);
    virtual ~ProgClassValue();

    private:
    DWORD m_value;
    mode_signed_t m_mode;
    length_t m_length;

};

#endif
