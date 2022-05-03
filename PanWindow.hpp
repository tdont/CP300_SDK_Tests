#ifndef PAN_WINDOW_H
#define PAN_WINDOW_H

#include "ClassPad.h"

class PanWindow : public CPWindow
{
    public:
    PanWindow(PegRect rect);
    ~PanWindow() {}
	
	void AddText(PEGCHAR* txt);

   	virtual void OnPointerMove(const PegPoint & p);
   	virtual void OnLButtonDown(const PegPoint& p);
   	virtual void OnLButtonUp(const PegPoint& p); 
	
private:
    PegRect m_promptRect;
    bool m_pen_down;
    int m_diffx, m_diffy;
   	PegPoint m_lastPoint;
};    

#endif