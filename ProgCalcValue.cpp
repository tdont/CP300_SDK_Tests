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


DWORD ProgClassValue::get_value()
{
    return m_value;
}

mode_signed_t ProgClassValue::get_mode()
{
    return m_mode;
}

length_t ProgClassValue::get_length()
{
    return m_length;
}

