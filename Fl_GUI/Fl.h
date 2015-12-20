#ifndef __Fl_h
#define __Fl_h

#include <string>

typedef unsigned char uchar;
typedef int Fl_Color;

enum Fl_Boxtype { // boxtypes (if you change these you must fix fl_boxtype.C):
    
  FL_NO_BOX = 0,    ///< nothing is drawn at all, this box is invisible
  FL_FLAT_BOX,      ///< a flat box
  FL_UP_BOX,      ///< see figure 1
  FL_DOWN_BOX,      ///< see figure 1
  FL_UP_FRAME,      ///< see figure 1
  FL_DOWN_FRAME,    ///< see figure 1
  FL_THIN_UP_BOX,   ///< see figure 1
  FL_THIN_DOWN_BOX,   ///< see figure 1
  FL_THIN_UP_FRAME,   ///< see figure 1
  FL_THIN_DOWN_FRAME,   ///< see figure 1
  FL_ENGRAVED_BOX,    ///< see figure 1
  FL_EMBOSSED_BOX,    ///< see figure 1
  FL_ENGRAVED_FRAME,    ///< see figure 1
  FL_EMBOSSED_FRAME,    ///< see figure 1
  FL_BORDER_BOX,    ///< see figure 1
  _FL_SHADOW_BOX,   ///< see figure 1
  FL_BORDER_FRAME,    ///< see figure 1
  _FL_SHADOW_FRAME,   ///< see figure 1
  _FL_ROUNDED_BOX,    ///< see figure 1
  _FL_RSHADOW_BOX,    ///< see figure 1
  _FL_ROUNDED_FRAME,    ///< see figure 1
  _FL_RFLAT_BOX,    ///< see figure 1
  _FL_ROUND_UP_BOX,   ///< see figure 1
  _FL_ROUND_DOWN_BOX,   ///< see figure 1
  _FL_DIAMOND_UP_BOX,   ///< see figure 1
  _FL_DIAMOND_DOWN_BOX,   ///< see figure 1
  _FL_OVAL_BOX,     ///< see figure 1
  _FL_OSHADOW_BOX,    ///< see figure 1
  _FL_OVAL_FRAME,   ///< see figure 1
  _FL_OFLAT_BOX,    ///< see figure 1
  _FL_PLASTIC_UP_BOX,   ///< plastic version of FL_UP_BOX
  _FL_PLASTIC_DOWN_BOX,   ///< plastic version of FL_DOWN_BOX
  _FL_PLASTIC_UP_FRAME,   ///< plastic version of FL_UP_FRAME
  _FL_PLASTIC_DOWN_FRAME, ///< plastic version of FL_DOWN_FRAME
  _FL_PLASTIC_THIN_UP_BOX,  ///< plastic version of FL_THIN_UP_BOX
  _FL_PLASTIC_THIN_DOWN_BOX,  ///< plastic version of FL_THIN_DOWN_BOX
  _FL_PLASTIC_ROUND_UP_BOX, ///< plastic version of FL_ROUND_UP_BOX
  _FL_PLASTIC_ROUND_DOWN_BOX, ///< plastic version of FL_ROUND_DOWN_BOX
  _FL_GTK_UP_BOX,   ///< gtk+ version of FL_UP_BOX
  _FL_GTK_DOWN_BOX,   ///< gtk+ version of FL_DOWN_BOX
  _FL_GTK_UP_FRAME,   ///< gtk+ version of FL_UP_FRAME
  _FL_GTK_DOWN_FRAME,   ///< gtk+ version of FL_DOWN_RAME
  _FL_GTK_THIN_UP_BOX,    ///< gtk+ version of FL_THIN_UP_BOX
  _FL_GTK_THIN_DOWN_BOX,  ///< gtk+ version of FL_THIN_DOWN_BOX
  _FL_GTK_THIN_UP_FRAME,  ///< gtk+ version of FL_UP_FRAME
  _FL_GTK_THIN_DOWN_FRAME,  ///< gtk+ version of FL_THIN_DOWN_FRAME
  _FL_GTK_ROUND_UP_BOX,   ///< gtk+ version of FL_ROUND_UP_BOX
  _FL_GTK_ROUND_DOWN_BOX, ///< gtk+ version of FL_ROUND_DOWN_BOX
  _FL_GLEAM_UP_BOX,   ///< gleam version of FL_GLEAM_UP_BOX
  _FL_GLEAM_DOWN_BOX,   ///< gleam version of FL_GLEAM_DOWN_BOX
  _FL_GLEAM_UP_FRAME,     ///< gleam version of FL_GLEAM_UP_FRAME
  _FL_GLEAM_DOWN_FRAME,   ///< gleam version of FL_GLEAM_DOWN_FRAME
  _FL_GLEAM_THIN_UP_BOX,      ///< gleam version of FL_GLEAM_THIN_UP_BOX
  _FL_GLEAM_THIN_DOWN_BOX,  ///< gleam version of FL_GLEAM_THIN_DOWN_BOX
  _FL_GLEAM_ROUND_UP_BOX,     ///< gleam version of FL_GLEAM_ROUND_UP_BOX
  _FL_GLEAM_ROUND_DOWN_BOX, ///< gleam version of FL_GLEAM_ROUND_DOWN_BOX
  FL_FREE_BOXTYPE   ///< the first free box type for creation of new box types
};

class vtkContext2D;
class Fl 
{
public:
	static void fl_xyline(int x, int y, int x1);
	static void fl_yxline(int x, int y, int y1);
	static void fl_rectf(int x, int y, int w, int h);
	static void draw_box(Fl_Boxtype t, int X, int Y, int W, int H, Fl_Color c) ;
	//static void draw_string(Fl_Boxtype t, int X, int Y, int W, int H, Fl_Color c) ;
	static void draw_string(const std::string &str, 
			Fl_Boxtype t, int X, int Y, int W, int H, Fl_Color c);

public:
	static int draw_box_active();
	static void fl_color(int nIndex);
	static void fl_line_color(int nIndex);
	static const unsigned char *fl_gray_ramp() ;

	static void fl_frame(const char* s, int x, int y, int w, int h);
	static void fl_frame2(const char* s, int x, int y, int w, int h);
	static void fl_no_box(int, int, int, int, Fl_Color) ;
	static void fl_rectf(int x, int y, int w, int h, Fl_Color);
	static void fl_thin_down_frame(int x, int y, int w, int h, Fl_Color) ;
	static void fl_thin_down_box(int x, int y, int w, int h, Fl_Color c) ;
	static void fl_thin_up_frame(int x, int y, int w, int h, Fl_Color) ;
	static void fl_thin_up_box(int x, int y, int w, int h, Fl_Color c) ;

	static void fl_up_frame(int x, int y, int w, int h, Fl_Color) ;
	static void fl_up_box(int x, int y, int w, int h, Fl_Color c) ;
	static void fl_down_frame(int x, int y, int w, int h, Fl_Color) ;
	static void fl_down_box(int x, int y, int w, int h, Fl_Color c) ;
	static void fl_engraved_frame(int x, int y, int w, int h, Fl_Color) ;
	static void fl_engraved_box(int x, int y, int w, int h, Fl_Color c) ;
	static void fl_embossed_frame(int x, int y, int w, int h, Fl_Color) ;
	static void fl_embossed_box(int x, int y, int w, int h, Fl_Color c) ;
	static void fl_rectbound(int x, int y, int w, int h, Fl_Color bgcolor) ;
	static void fl_border_frame(int x, int y, int w, int h, Fl_Color c) ;

public:
	static const int FL_NUM_GRAY = 24;
  static short CMap[FL_NUM_GRAY][3];
  static vtkContext2D *g_Painter;
	static Fl* g_Fl;

public:
	Fl();
	~Fl();

	static void SetPainter(vtkContext2D *context);
	static void background(uchar r, uchar g, uchar b);

};


#endif //__Fl_h
