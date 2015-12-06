#include "myContextView.h"

#include <vtkContext2D.h>

vtkStandardNewMacro(myContextView);

vtkCxxSetObjectMacro(myContextView, Context, vtkContext2D);
vtkCxxSetObjectMacro(myContextView, Scene, vtkContextScene);

myContextView::myContextView()
{
	Context = vtkSmartPointer<vtkContext2D>::New();
	vtkOpenGLContextDevice2D *pd = vtkOpenGLContextDevice2D::New();
	Context->Begin(pd);
}


