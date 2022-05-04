#include "ClassPad.h"

#include "ProgCalcMainWindow.hpp"
#include "progCalcShared.h"
#include "ProgCalcDispWindow.hpp"
#include "PanWindow.hpp"

#include <stdlib.h>
#ifdef WIN32
#include <time.h>
#include <stdio.h>
#endif

/* SubMendu definitions */
PegMenuDescriptionML SubMenuMode[] = 
{
    {"Signed", CMN_NO_ID, CSTM_EVENT_MODE_SIGNED, AF_ENABLED, NULL },
    {"Unsigned", CMN_NO_ID, CSTM_EVENT_MODE_UNSIGNED, AF_ENABLED, NULL },
    {"", CMN_NO_ID, 0, 0, 0}
};

PegMenuDescriptionML SubMenuLength[] = 
{
    {" 8 bits", CMN_NO_ID, CSTM_EVENT_TYPE_BYTE, AF_ENABLED, NULL },
    {"16 bits", CMN_NO_ID, CSTM_EVENT_TYPE_WORD, AF_ENABLED, NULL },
    {"32 bits", CMN_NO_ID, CSTM_EVENT_TYPE_DWORD, AF_ENABLED, NULL },
    {"", CMN_NO_ID, 0, 0, 0}
};

/* Menu Definition */
PegMenuDescriptionML MainMenu[] =
{
    {"Mode", CMN_NO_ID, 0, AF_ENABLED, SubMenuMode },
    {"Length", CMN_NO_ID, 0, AF_ENABLED, SubMenuLength },
    {"", CMN_NO_ID, 0, 0, 0}
};



ProgCalcMainWindow::ProgCalcMainWindow(PegRect rect, CPMainFrame *frame) :CPModuleWindow(rect,0,0,frame)
{
  m_selectedLength = LENGTH_32BIT;
  m_selectedMode = MODE_UNSIGNED;
  HasLines = false;
	//SetScrollMode(WSM_AUTOSCROLL);

  PegRect rectValDisplayer = mClient;
  m_dispWin = new ProgCalcDisplayWindow(rectValDisplayer);
  Add(m_dispWin);

  PegRect r = mClient;
	r -= 20; // make the pan window a bit smaller
	m_panWin = new PanWindow(r);
	Add(m_panWin);
}    

ProgCalcMainWindow::~ProgCalcMainWindow()
{
  // if (m_panWin != NULL)
  // {
  //   delete m_panWin;
  // }
  // if(m_dispWin != NULL)
  // {
  //   delete m_dispWin;
  // }
}

PegMenuDescriptionML* ProgCalcMainWindow::GetMenuDescriptionML()
{
    return MainMenu;    
}

//Add UI creates the toolbar buttons "Add Text" and "Toggle Lines"
void ProgCalcMainWindow::AddUI()
{
	// PegRect rr = GetToolbarButtonRect();

    // PegRect ListRect;

    // ListRect.Set(rr.wLeft, rr.wTop, rr.wLeft + 10, rr.wBottom);
    // PEGCHAR cTemp[20];
    // PegComboBox *pComboBoxType = new PegComboBox(ListRect);
    // strcpy(cTemp, "8b");
    // pComboBoxType->Add(new PegPrompt(0, 0, cTemp, 3,
    //           FF_NONE|TJ_LEFT|AF_ENABLED|TT_COPY));
    // strcpy(cTemp, "16b");
    // pComboBoxType->Add(new PegPrompt(0, 0, cTemp, 2,
    //           FF_NONE|TJ_LEFT|AF_ENABLED|TT_COPY));
    // strcpy(cTemp, "32b");
    // pComboBoxType->Add(new PegPrompt(0, 0, cTemp, 1,
    //           FF_NONE|TJ_LEFT|AF_ENABLED|TT_COPY));

    // // strcpy(cTemp, "Select");
    // // for (int iLoop = 20; iLoop > 0; iLoop--)
    // // {
    // //     CP_IntToString(iLoop, (CP_CHAR*)(cTemp + 6));
    // //     //itoa(iLoop, cTemp + 6, 10);
    // //     pComboBoxType->Add(new PegPrompt(0, 0, cTemp, iLoop,
    // //           FF_NONE|TJ_LEFT|AF_ENABLED|TT_COPY));
    // // }
    // pComboBoxType->SetScrollMode(WSM_VSCROLL);
    // //pComboBoxType->SetSelected(5);
    // //AddR(pComboBoxType);
    // m_ui->AddToolbarButton(pComboBoxType);
	
	// PegTextButton *b = new PegTextButton(4,0,"Add T",CSTM_EVENT_ADD_TEXT);
	// m_ui->AddToolbarButton(b);
	// b = new PegTextButton(4,0,"T Lines",CSTM_EVENT_TOGGLE_LINES);
	// m_ui->AddToolbarButton(b);
	PegTextButton *b = NULL;
	b = new PegTextButton(4,0,"AND",CSTM_EVENT_OP_AND);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,"OR",CSTM_EVENT_OP_OR);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,"NOT",CSTM_EVENT_OP_NOT);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,"XOR",CSTM_EVENT_OP_XOR);
	m_ui->AddToolbarButton(b);
    b = new PegTextButton(4,0,"<<",CSTM_EVENT_LSH);
	m_ui->AddToolbarButton(b);
	b = new PegTextButton(4,0,">>",CSTM_EVENT_RSH);
	m_ui->AddToolbarButton(b);

}

//The overridden drawn function.
//All drawing is done before the call to DrawChildren() to Draw PanWindow
void ProgCalcMainWindow::Draw()
{
	BeginDraw();
	DrawFrame();
	DrawLines();  
    DrawWidget();
    updateStatusBar();
	DrawChildren();
	EndDraw();
}    

SIGNED ProgCalcMainWindow::Message(const PegMessage &Mesg)
{
	switch(Mesg.wType)
    {
    	case SIGNAL( CSTM_EVENT_ADD_TEXT, PSF_CLICKED):	
    		m_panWin->AddText("AddText");
    		break;
    	case SIGNAL( CSTM_EVENT_TOGGLE_LINES, PSF_CLICKED):
            HasLines = !HasLines;	
			      DrawLines();
            m_panWin->AddText("Toogle");
    		break;
        case SIGNAL( CSTM_EVENT_TYPE_BYTE, PSF_CLICKED):	
    		m_panWin->AddText("8Bits");
        m_selectedLength = LENGTH_8BIT;
    		break;
        case SIGNAL( CSTM_EVENT_TYPE_WORD, PSF_CLICKED):	
    		m_panWin->AddText("16Bits");
        m_selectedLength = LENGTH_16BIT;
    		break;
        case SIGNAL( CSTM_EVENT_TYPE_DWORD, PSF_CLICKED):	
    		m_panWin->AddText("32bits");
        m_selectedLength = LENGTH_32BIT;
    		break;
        case SIGNAL( CSTM_EVENT_MODE_SIGNED, PSF_CLICKED):	
    		m_panWin->AddText("Signed");
        m_selectedMode = MODE_SIGNED;
    		break;
        case SIGNAL( CSTM_EVENT_MODE_UNSIGNED, PSF_CLICKED):	
    		m_panWin->AddText("Unsigned");
        m_selectedMode = MODE_UNSIGNED;
    		break;
        case SIGNAL( CSTM_EVENT_OP_AND, PSF_CLICKED):	
    		m_panWin->AddText("AND");
    		break;
        case SIGNAL( CSTM_EVENT_OP_OR, PSF_CLICKED):	
    		m_panWin->AddText("OR");
    		break;
        case SIGNAL( CSTM_EVENT_OP_NOT, PSF_CLICKED):	
    		m_panWin->AddText("NOT");
    		break;
        case SIGNAL( CSTM_EVENT_OP_XOR, PSF_CLICKED):	
    		m_panWin->AddText("XOR");
    		break;
        case SIGNAL( CSTM_EVENT_RSH, PSF_CLICKED):	
    		m_panWin->AddText("Rsh");
    		break;
        case SIGNAL( CSTM_EVENT_LSH, PSF_CLICKED):	
    		m_panWin->AddText("Lsh");
    		break;
    	default:								
            return CPModuleWindow::Message(Mesg);
            break;
    }
    updateStatusBar();
    return 0;
}

void ProgCalcMainWindow::DrawWidget(void)
{


}

void ProgCalcMainWindow::DrawLines(void)
{
    PegColor Color(BLACK, WHITE, CF_FILL);
    SIGNED yPos = mClient.wTop;

	//Since this function can be called outside of the Draw() function, 
	//the screen must be invalidated before drawing is allowed
    Invalidate(); 
    
    // A loop that just draws black lines 4 pixels apart
    BeginDraw(); 
    Rectangle(mClient, Color); 
    if(HasLines)
    {
        while(yPos <= mClient.wBottom)
        {
            Line(mClient.wLeft, yPos, mClient.wRight, yPos, Color);
            yPos += 4;
        }
    }    
    EndDraw();
}

void ProgCalcMainWindow::updateStatusBar()
{
    static PEGCHAR statusText[20];
    for (int i = 0; i < 20; i++)
    {
      statusText[i] = ' ';
    }

    switch(m_selectedMode)
    {
      case MODE_UNSIGNED:
        memcpy(statusText, "unsigned", 8);
        break;
      case MODE_SIGNED:
        memcpy(statusText, "  signed", 8);
        break;
      default:
        memcpy(statusText, " unknown", 8);
      break;
    }  

    switch(m_selectedLength)
    {
      case LENGTH_8BIT:
        memcpy(&statusText[12], " 8 bits", 7);
        break;
      case LENGTH_16BIT:
        memcpy(&statusText[12], "16 bits", 7);
        break;
      case LENGTH_32BIT:
        memcpy(&statusText[12], "32 bits", 7);
      break;
      default:
        memcpy(&statusText[12], " unknown", 8);
      break;
    }  
    
    /* Set end of string */
    statusText[sizeof(statusText) - 1] = 0;
   
    PegStatusBar* bar = GetStatusBar();
    if (bar != 0)
    {
      bar->SetTextField(1, statusText);
    }
    // Set the text
    //SetStatusBar(statusText);
}
 
