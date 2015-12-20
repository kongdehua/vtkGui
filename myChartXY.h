#ifndef __myChartXY_h
#define __myChartXY_h

#include "vtkAbstractContextItem.h" // For export macro

class myChartXY : public vtkAbstractContextItem
{
public:
  vtkTypeMacro(myChartXY, vtkAbstractContextItem);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  static myChartXY *New();

  virtual bool Paint(vtkContext2D *painter);

//BTX
protected:
  myChartXY();
  ~myChartXY();

private:
  myChartXY(const myChartXY &); // Not implemented.
  void operator=(const myChartXY &);   // Not implemented.

};


#endif //__myChartXY_h
