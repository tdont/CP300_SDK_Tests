#include "PanWindow.hpp"
#include <stdlib.h>
#ifdef WIN32
#include <stdio.h>
#endif

PanWindow::PanWindow(PegRect rect):CPWindow(rect)
{
	m_pen_down = false;
    PegPrompt *text;
    m_lastPoint.x = 0;
    m_lastPoint.y = 0;
    
    // Add the first PegPrompt and set the promptRect equal to its mReal
    text = new PegPrompt(2,2, (PEGCHAR*)"Hello.");
    m_promptRect = text->mReal;
	AddR(text);
}


//This Function is called any time the ClassPad receives a Pen Down Message  
void PanWindow::OnLButtonDown(const PegPoint &p)
{
    // this boolean garuntees that if the pen down even didn't oringate inside
    // of PanWindow, that the window is not moved
    m_pen_down = true;

    //Capturing the pointer garuntees that even if the pen leaves PanWindow,
    //PanWindow will continue to hold the pointer and receive its messages
    CapturePointer();

	m_diffx=0; 
 	m_diffy=0; 
  	m_lastPoint.x=p.x; 
   	m_lastPoint.y=p.y;

}    

//This Function is called any time the ClassPad receives a Pen up Message
void PanWindow::OnLButtonUp(const PegPoint &p)
{
	//Set this back to false on a pen up
    m_pen_down = false;
    
    //Release the pointer so we do not continue to receive pen 
    // messages even after the pen up
    ReleasePointer();
	m_diffx=0; 
 	m_diffy=0; 
  	m_lastPoint.x=0; 
   	m_lastPoint.y=0;
}    

void PanWindow::OnPointerMove(const PegPoint &p)
{
    // Only move the window if the pendown came from inside of PanWindow and
    // m_lastPoint is set.
    if(m_pen_down && m_lastPoint.x != 0 && m_lastPoint.y != 0 && m_lastPoint != p)
    {
        BeginDraw();
        PegRect rect;
     
     	//Find out how much the pen has moved in the x and y direction
        m_diffx += p.x - m_lastPoint.x;
        m_diffy += p.y - m_lastPoint.y;
    
    	//Create a rectangle that is PanWindow's mReal shifted by the amount 
    	//that the pen was moved
    	rect = mReal;
    	rect.Shift(m_diffx,m_diffy);
     	
		// Resize invalidates the old rect and new one for us
		// It also shifts all children in the window (so we don't have to worry
		// about repositioning the PegPrompts)
		Resize(rect);

		// Calling Resize with the same size is used as a "trick" to force the
  		// parent to check for and add or remove scrollbars
    	Parent()->Resize(Parent()->mReal);
 		Parent()->Draw();
 		EndDraw();
    }    
    m_lastPoint = p;
}    

void PanWindow::AddText(PEGCHAR* txt)
{
    PegPrompt* text;   
    
    //since we will place the next prompt 25 pixels below the previous, check
    // to see if the current promptRect + 25 is off the screen
    if(m_promptRect.Height() + 10 > mReal.Height())
    {
        //Create a new PegPrompt 25 pixels below where the last PegPrompt was creater
        //take the union of its mReal and the  and running rectangle of all the 
        //other PegPrompts that have been added
    	text = new PegPrompt(4, m_promptRect.Height()+10, txt);
		m_promptRect |= text->mReal;
 		AddR(text);   
 		
        BeginDraw();
      
        //mReal should not be modified directly, so create a new PegRect and
        //set it equal to mReal.  Add the height of the new PegPrompt that was
        //just added and the 25 pixels of spacing
		PegRect new_rect = mReal;
		new_rect.wBottom += ( 10 + text->mReal.Height());
		Resize(new_rect);
		
		// Calling Resize with the same size is used as a "trick" to force the
  		// parent to check for and add or remove scrollbars
 		Parent()->Resize(Parent()->mReal);
		Parent()->Draw();

 		EndDraw();
    }    
    else
    {
        //Create a new PegPrompt 25 pixels below where the last PegPrompt was creater
        //take the union of its mReal and the  and running rectangle of all the 
        //other PegPrompts that have been added
        text = new PegPrompt(4, m_promptRect.Height()+10, txt);
		m_promptRect |= text->mReal;   
 		AddR(text);  
   	}   	
       
}    
  
