#include <iostream>
//#include <vtkConeSource.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkSmartPointer.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>

#include "myChartXY.h"
#include "Fl_Window.h"

static int *x = new int(100);
int main(int argc, char **argv)
{
  int *xx = new int[100];
	//std::cout << " hello " << std::endl;

	//delete []xx;
/*
	//delete x;
*/
	
	//vtkConeSource *cone = vtkConeSource::New();
	//cone->PrintSelf(std::cout, vtkIndent());

	std::cout << " hello " << std::endl;
	std::cout << " hello " << x[2] << std::endl;

	vtkSmartPointer<vtkContextView> view = 
		vtkSmartPointer<vtkContextView>::New();
	view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	view->GetRenderWindow()->SetSize(500, 450);

	//myChartXY *chart = myChartXY::New();
	//view->GetScene()->AddItem(chart);

	Fl_Window *win = Fl_Window::New();
	view->GetScene()->AddItem(win);

	//chart->AddPlot(vtkChart::LINE);

	view->GetInteractor()->Initialize();
	view->GetInteractor()->Start();

	return 0;
};

