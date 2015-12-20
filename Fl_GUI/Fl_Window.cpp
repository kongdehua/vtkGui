#include "Fl_Window.h"

#include <vtkContext2D.h>
#include <vtkPen.h>
#include <vtkBrush.h>

#include <vtkObjectFactory.h>

#include <iostream>
#include <sstream>
#include "Fl.h"

//-----------------------------------------------------------------------------
vtkStandardNewMacro(Fl_Window);

//-----------------------------------------------------------------------------
Fl_Window::Fl_Window()
{
}

//-----------------------------------------------------------------------------
Fl_Window::~Fl_Window()
{
}

//-----------------------------------------------------------------------------
bool Fl_Window::Paint(vtkContext2D *painter)
{
	Fl::SetPainter(painter);
  //this->Pen = vtkPen::New();
  //painter->GetPen()->SetColor(0, 0, 0);
  //painter->GetPen()->SetWidth(1.0);
	//painter->GetPen()->SetLineType(vtkPen::NO_PEN);

  // Draw this axis
	std::cout << "FL_FREE_BOXTYPE: " <<  FL_FREE_BOXTYPE << std::endl;
	//fl_rectbound  
	Fl::draw_box(FL_EMBOSSED_BOX, 6, 6, 430, 430, 17);

	for	(int i = 0; i < 4; i++)
	{
		for	(int j = 0; j < 14; j++)
		{
			std::ostringstream o;
			o << "abc";
			o << i;
			o << "_";
			o << j;

			Fl::draw_box( (Fl_Boxtype)(FL_NO_BOX + i*14 + j), 10 + 100 * i, 10 + 30 * j, 80, 25, 19);
			Fl::draw_string( o.str(), (Fl_Boxtype)(FL_NO_BOX + i*14 + j), 10 + 100 * i, 10 + 30 * j, 80, 25, 19);
		}
	}

	//Fl::draw_box( (Fl_Boxtype)(FL_NO_BOX + 56), 10 + 100 * 4, 10 , 80, 25, 19);
	//Fl::draw_box(FL_BORDER_BOX, 5, 5, 150, 120, 17);
	//Fl::draw_box(FL_FLAT_BOX, 5, 5, 150, 120, 17);
  //painter->DrawLine(100, 100, 200, 200);

	/*
  painter->DrawLine(100, 300, 200, 200);

	painter->GetBrush()->SetColorF(1, 0, 1, 0);

	painter->DrawRect(200, 200, 300, 300);
	painter->DrawEllipse(200, 200, 30, 20);
	*/

  return true;
}





//-----------------------------------------------------------------------------
void Fl_Window::PrintSelf(ostream &os, vtkIndent indent)
{

}
