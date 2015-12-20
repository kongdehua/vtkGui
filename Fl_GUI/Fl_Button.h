#ifndef __Fl_Window_h
#define __Fl_Window_h

#include "vtkAbstractContextItem.h" // For export macro

class Fl_Window : public vtkAbstractContextItem
{
public:
  vtkTypeMacro(Fl_Window, vtkAbstractContextItem);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  static Fl_Window *New();

  virtual bool Paint(vtkContext2D *painter);

//BTX
protected:
  Fl_Window();
  ~Fl_Window();

private:
  Fl_Window(const Fl_Window &); // Not implemented.
  void operator=(const Fl_Window &);   // Not implemented.

};


#endif //__Fl_Window_h
