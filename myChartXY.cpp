#include "myChartXY.h"

#include <vtkContext2D.h>
#include <vtkPen.h>
#include <vtkBrush.h>

#include <vtkObjectFactory.h>

//-----------------------------------------------------------------------------
vtkStandardNewMacro(myChartXY);

//-----------------------------------------------------------------------------
myChartXY::myChartXY()
{
}

//-----------------------------------------------------------------------------
myChartXY::~myChartXY()
{
}

//-----------------------------------------------------------------------------
bool myChartXY::Paint(vtkContext2D *painter)
{
  //this->Pen = vtkPen::New();
  painter->GetPen()->SetColor(0, 0, 0);
  painter->GetPen()->SetWidth(1.0);
	//painter->GetPen()->SetLineType(vtkPen::NO_PEN);

  // Draw this axis
  painter->DrawLine(100, 100, 200, 200);

  painter->DrawLine(100, 300, 200, 200);

	painter->GetBrush()->SetColorF(1, 0, 1, 0);

	painter->DrawRect(200, 200, 300, 300);
	painter->DrawEllipse(200, 200, 30, 20);

  return true;
}





//-----------------------------------------------------------------------------
void myChartXY::PrintSelf(ostream &os, vtkIndent indent)
{

}
