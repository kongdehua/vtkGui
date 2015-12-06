#ifndef _MY_CONTEXT_VIEW_H
#define _MY_CONTEXT_VIEW_H

#include <vtkRenderViewBase.h>

class vtkContextScene;
class vtkContext2D;

class myContextView : public vtkRenderViewBase
{
public:
	void PrintSelf(ostream &os, vtkIndent indent);
	vtkTypeMacro(myContextView, vtkRenderViewBase);

	static myContextView *New();

protected:
	myContextView();
	~myContextView();

	vtkSmartPointer<vtkContextScene> Scene;
	vtkSmartPointer<vtkContext2D> Context;

private:
	myContextView(const myContextView&); // Not Imp
	void operator=(const myContextView&);// Not Imp
};

#endif
