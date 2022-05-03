#include "ProgCalcValue.hpp"
#include "progCalcShared.h"

ProgClassValue::ProgClassValue(DWORD value, mode_signed_t mode, length_t length)
{
    m_value = value;
    m_mode = mode;
    m_length = length;
}

ProgClassValue::~ProgClassValue()
{

}


