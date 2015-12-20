#ifndef __Fl_Widget_h
#define __Fl_Widget_h

/** Fl_Widget is the base class for all widgets in vtkGui
	*
	* You can't create one of these because the constructor is not public.
	* 
	* It's up to the user code to call redraw() after setting mothods.
	*/
class Fl_Widget 
{
	int x_, y_, w_, h_;

  Fl_Widget(const Fl_Widget &); // Not implemented.
  void operator=(const Fl_Widget &);   // Not implemented.

public:
  virtual bool draw();

//BTX
protected:

  /** Creates a widget at the given position and size.

      The Fl_Widget is a protected constructor, but all derived widgets have a 
      matching public constructor. It takes a value for x(), y(), w(), h(), and 
      an optional value for label().
    
      \param[in] x, y the position of the widget relative to the enclosing window
      \param[in] w, h size of the widget in pixels
      \param[in] label optional text for the widget label
   */
  Fl_Widget(int x, int y, int w, int h, const char *label=0L);

  /** Internal use only. Use position(int,int), size(int,int) or resize(int,int,int,int) instead. */
  void x(int v) {x_ = v;}
  /** Internal use only. Use position(int,int), size(int,int) or resize(int,int,int,int) instead. */
  void y(int v) {y_ = v;}
  /** Internal use only. Use position(int,int), size(int,int) or resize(int,int,int,int) instead. */
  void w(int v) {w_ = v;}
  /** Internal use only. Use position(int,int), size(int,int) or resize(int,int,int,int) instead. */
  void h(int v) {h_ = v;}

  ~Fl_Widget();
};


#endif //__Fl_Window_h
