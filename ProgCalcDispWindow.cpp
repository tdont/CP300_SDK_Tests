#include "ProgCalcDispWindow.hpp"
#include <stdlib.h>
#ifdef WIN32
#include <stdio.h>
#endif


#define VALDISP_VERTICAL_INTERVAL (15)
#define VALDISP_VERTICAL_OFFSET (32)
#define VALDISP_HORIZ_INTERVAL  (34)


ProgCalcDisplayWindow::ProgCalcDisplayWindow(PegRect rect):CPWindow(rect)
{
    PegThing *valueDisplayer = new PegThing(rect);
    m_rdbtn_hex = new PegRadioButton(2, VALDISP_VERTICAL_OFFSET, "HEX");
    valueDisplayer->Add(m_rdbtn_hex);
    m_pgprmt_hex = new PegPrompt(VALDISP_HORIZ_INTERVAL, 2 + VALDISP_VERTICAL_OFFSET, (PEGCHAR*)"HEX Value");
    valueDisplayer->Add(m_pgprmt_hex);

    m_rdbtn_dec = new PegRadioButton(2, VALDISP_VERTICAL_OFFSET + 1* VALDISP_VERTICAL_INTERVAL, "DEC");
    valueDisplayer->Add(m_rdbtn_dec);  
    m_pgprmt_dec = new PegPrompt(VALDISP_HORIZ_INTERVAL, 2 + VALDISP_VERTICAL_OFFSET + 1* VALDISP_VERTICAL_INTERVAL, (PEGCHAR*)"DEC Value");
    valueDisplayer->Add(m_pgprmt_dec);

    m_rdbtn_oct = new PegRadioButton(2, VALDISP_VERTICAL_OFFSET + 2* VALDISP_VERTICAL_INTERVAL , "OCT");
    valueDisplayer->Add(m_rdbtn_oct);
    m_pgprmt_oct = new PegPrompt(VALDISP_HORIZ_INTERVAL, 2 + VALDISP_VERTICAL_OFFSET + 2* VALDISP_VERTICAL_INTERVAL, (PEGCHAR*)"OCT Value");
    valueDisplayer->Add(m_pgprmt_oct);

    m_rdbtn_bin = new PegRadioButton(2, VALDISP_VERTICAL_OFFSET + 3* VALDISP_VERTICAL_INTERVAL, "BIN");
    valueDisplayer->Add(m_rdbtn_bin);
    m_pgprmt_bin = new PegPrompt(VALDISP_HORIZ_INTERVAL, 2 + VALDISP_VERTICAL_OFFSET + 3* VALDISP_VERTICAL_INTERVAL, (PEGCHAR*)"BIN Value");
    valueDisplayer->Add(m_pgprmt_bin);

    AddR(valueDisplayer);

    /* Select by default Decimal entry */
    m_rdbtn_dec->SetSelected(true);
}

ProgCalcDisplayWindow::~ProgCalcDisplayWindow()
{
    // if(m_rdbtn_dec != NULL)
    // {
    //     delete m_rdbtn_dec;
    // }
    // if(m_rdbtn_hex != NULL)
    // {
    //     delete m_rdbtn_hex;
    // }
    // if(m_rdbtn_oct != NULL)
    // {
    //     delete m_rdbtn_oct;
    // }
    // if(m_rdbtn_bin != NULL)
    // {
    //     delete m_rdbtn_bin;
    // }
    
    // if(m_pgprmt_hex != NULL)
    // {
    //     delete m_pgprmt_hex;
    // }
    // if(m_pgprmt_dec != NULL)
    // {
    //     delete m_pgprmt_dec;
    // }
    // if(m_pgprmt_oct != NULL)
    // {
    //     delete m_pgprmt_oct;
    // }
    // if(m_pgprmt_bin != NULL)
    // {
    //     delete m_pgprmt_bin;
    // }
}

void ProgCalcDisplayWindow::display_value(ProgClassValue& value)
{
    return;
}

typingmode_t ProgCalcDisplayWindow::getSelectedInputType()
{
    typingmode_t ret_val = TYPING_MODE_UNKNOWN;
    if(m_rdbtn_bin && m_rdbtn_bin->IsSelected())
    {
        ret_val = TYPING_MODE_BIN;
    }
    else if(m_rdbtn_hex && m_rdbtn_hex->IsSelected())
    {
        ret_val = TYPING_MODE_HEX;
    }
    else if(m_rdbtn_oct && m_rdbtn_oct->IsSelected())
    {
        ret_val = TYPING_MODE_OCT;
    }
    else if(m_rdbtn_dec && m_rdbtn_dec->IsSelected())
    {
        ret_val = TYPING_MODE_DEC;
    }

    return ret_val;
}