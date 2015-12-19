/*=========================================================================

  Program:   Visualization Toolkit
  Module:    myChartXY.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "myChartXY.h"

#include "vtkContext2D.h"
#include "vtkPen.h"
#include "vtkBrush.h"
#include "vtkColorSeries.h"
#include "vtkInformation.h"
//#include "vtkChartSelectionHelper.h"

#include "vtkMath.h"
#include "vtkTransform2D.h"
#include "vtkContextScene.h"
#include "vtkContextMouseEvent.h"
#include "vtkContextKeyEvent.h"
#include "vtkContextTransform.h"
#include "vtkContextClip.h"
#include "vtkPoints2D.h"
#include "vtkVector.h"
#include "vtkVectorOperators.h"

#include "vtkPlotBar.h"
#include "vtkPlotBag.h"
#include "vtkPlotFunctionalBag.h"
#include "vtkPlotStacked.h"
#include "vtkPlotLine.h"
#include "vtkPlotPoints.h"
#include "vtkContextMapper2D.h"

#include "vtkAxis.h"
#include "vtkPlotGrid.h"
#include "vtkChartLegend.h"
#include "vtkTooltipItem.h"

#include "vtkTable.h"
#include "vtkIdTypeArray.h"

#include "vtkAnnotationLink.h"
#include "vtkSelection.h"
#include "vtkSelectionNode.h"
#include "vtkSmartPointer.h"

#include "vtkObjectFactory.h"
#include "vtkCommand.h"

#include "vtkStdString.h"
#include "vtkTextProperty.h"

#include "vtkDataArray.h"
#include "vtkStringArray.h"

// My STL containers
#include <vector>
#include <algorithm>

//-----------------------------------------------------------------------------
class myChartXYPrivate
{
public:
  myChartXYPrivate()
    {
    this->Colors = vtkSmartPointer<vtkColorSeries>::New();
    this->Clip = vtkSmartPointer<vtkContextClip>::New();
    this->Borders[0] = 60;
    this->Borders[1] = 50;
    this->Borders[2] = 20;
    this->Borders[3] = 20;
    }

  std::vector<vtkPlot *> plots; // Charts can contain multiple plots of data
  std::vector<vtkContextTransform *> PlotCorners; // Stored by corner...
  std::vector<vtkAxis *> axes; // Charts can contain multiple axes
  vtkSmartPointer<vtkColorSeries> Colors; // Colors in the chart
  vtkSmartPointer<vtkContextClip> Clip; // Colors in the chart
  int Borders[4];
};

//-----------------------------------------------------------------------------
vtkStandardNewMacro(myChartXY);

//-----------------------------------------------------------------------------
myChartXY::myChartXY()
{
/*
  this->ChartPrivate = new myChartXYPrivate;

  this->AutoAxes = true;
  this->HiddenAxisBorder = 20;

  // The grid is drawn first.
  vtkPlotGrid *grid1 = vtkPlotGrid::New();
  this->AddItem(grid1);
  grid1->Delete();

  // The second grid for the far side/top axis
  vtkPlotGrid *grid2 = vtkPlotGrid::New();
  this->AddItem(grid2);
  grid2->Delete();
	*/

  // The plots are drawn on top of the grid, in a clipped, transformed area.
  //this->AddItem(this->ChartPrivate->Clip);
  // Set up the bottom-left transform, the rest are often not required (set up
  // on demand if used later). Add it as a child item, rendered automatically.
	/* vtkSmartPointer<vtkContextTransform> corner = vtkSmartPointer<vtkContextTransform>::New();
  this->ChartPrivate->PlotCorners.push_back(corner);
  this->ChartPrivate->Clip->AddItem(corner); // Child list maintains ownership.
	*/

/*
  // Next is the axes
  for (int i = 0; i < 4; ++i)
    {
    this->ChartPrivate->axes.push_back(vtkAxis::New());
    // By default just show the left and bottom axes
    this->ChartPrivate->axes.back()->SetVisible(i < 2 ? true : false);
    this->AttachAxisRangeListener(this->ChartPrivate->axes.back());
    this->AddItem(this->ChartPrivate->axes.back());
    }
  this->ChartPrivate->axes[vtkAxis::LEFT]->SetPosition(vtkAxis::LEFT);
  this->ChartPrivate->axes[vtkAxis::BOTTOM]->SetPosition(vtkAxis::BOTTOM);
  this->ChartPrivate->axes[vtkAxis::RIGHT]->SetPosition(vtkAxis::RIGHT);
  this->ChartPrivate->axes[vtkAxis::TOP]->SetPosition(vtkAxis::TOP);

  // Set up the x and y axes - should be configured based on data
  this->ChartPrivate->axes[vtkAxis::LEFT]->SetTitle("Y Axis");
  this->ChartPrivate->axes[vtkAxis::BOTTOM]->SetTitle("X Axis");
	*/

/*
  grid1->SetXAxis(this->ChartPrivate->axes[vtkAxis::BOTTOM]);
  grid1->SetYAxis(this->ChartPrivate->axes[vtkAxis::LEFT]);
  grid2->SetXAxis(this->ChartPrivate->axes[vtkAxis::TOP]);
  grid2->SetYAxis(this->ChartPrivate->axes[vtkAxis::RIGHT]);
	*/

/*
  // Then the legend is drawn
  this->Legend = vtkSmartPointer<vtkChartLegend>::New();
  this->Legend->SetChart(this);
  this->Legend->SetVisible(false);
  this->AddItem(this->Legend);

  this->PlotTransformValid = false;

  this->DrawBox = false;
  this->DrawSelectionPolygon = false;
  this->DrawNearestPoint = false;
  this->DrawAxesAtOrigin = false;
  this->BarWidthFraction = 0.8f;

  this->Tooltip = vtkSmartPointer<vtkTooltipItem>::New();
  this->Tooltip->SetVisible(false);
  this->AddItem(this->Tooltip);
*/

  this->LayoutChanged = true;
  this->ForceAxesToBounds = false;
}

//-----------------------------------------------------------------------------
myChartXY::~myChartXY()
{
  for (unsigned int i = 0; i < this->ChartPrivate->plots.size(); ++i)
    {
    this->ChartPrivate->plots[i]->Delete();
    }
  for (size_t i = 0; i < 4; ++i)
    {
    this->ChartPrivate->axes[i]->Delete();
    }
  delete this->ChartPrivate;
  this->ChartPrivate = 0;
}

//-----------------------------------------------------------------------------
bool myChartXY::Paint(vtkContext2D *painter)
{
/*
  vtkVector2i geometry(0, 0);
  bool recalculateTransform = false;
  if (this->LayoutStrategy == vtkChart::FILL_SCENE)
    {
    geometry = vtkVector2i(this->GetScene()->GetSceneWidth(),
                           this->GetScene()->GetSceneHeight());
    this->SetSize(vtkRectf(0.0, 0.0, geometry.GetX(), geometry.GetY()));
    }
		*/

  //this->GetBoundingRect(painter);
  this->Pen = vtkPen::New();
  this->Pen->SetColor(0, 0, 0);
  this->Pen->SetWidth(1.0);

  painter->ApplyPen(this->Pen);
  // Draw this axis
  painter->DrawLine(100, 100, 200, 200);

  painter->DrawLine(100, 300, 200, 200);

  vtkSmartPointer<vtkBrush> BackgroundBrush = vtkSmartPointer<vtkBrush>::New();
	BackgroundBrush->SetColorF(1, 0, 1, 0);

	//painter->GetPen()->SetLineType(vtkPen::NO_PEN);
	painter->ApplyBrush(BackgroundBrush);
	painter->DrawRect(200, 200, 300, 300);
	painter->DrawEllipse(200, 200, 30, 20);


/*
	this->SetSize(vtkRectf(0.0, 0.0, 500, 400 ));

  this->UpdateLayout(painter);

  // Use the scene to render most of the chart.
  this->PaintChildren(painter);
	*/

  return true;
}





//-----------------------------------------------------------------------------
void myChartXY::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Axes: " << endl;
  for (int i = 0; i < 4; ++i)
    {
    this->ChartPrivate->axes[i]->PrintSelf(os, indent.GetNextIndent());
    }
  if (this->ChartPrivate)
    {
    os << indent << "Number of plots: " << this->ChartPrivate->plots.size()
       << endl;
    for (unsigned int i = 0; i < this->ChartPrivate->plots.size(); ++i)
      {
      os << indent << "Plot " << i << ":" << endl;
      this->ChartPrivate->plots[i]->PrintSelf(os, indent.GetNextIndent());
      }
    }

}
