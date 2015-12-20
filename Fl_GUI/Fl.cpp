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

#include "Fl.h"
#include <math.h>
#include <vtkContext2D.h>
#include <vtkPen.h>
#include <vtkBrush.h>
#include <vtkPoints2D.h>

#define BORDER_WIDTH 2

#define FL_GRAY 17
#define FL_BLACK 0

typedef void (Fl_Box_Draw_F)(int x, int y, int w, int h, Fl_Color color);

static const unsigned char active_ramp[24] = {
  0, 1, 2, 3,
  4, 5, 6, 7,
  8, 9, 10,11,
  12,13,14,15,
  16,17,18,19,
  20,21,22,23};
static const unsigned char inactive_ramp[24] = {
  11, 11, 12, 12,
  12, 13, 13, 14,
  14, 14, 15, 15,
  16, 16, 16, 17,
  17, 17, 18, 18,
  19, 19, 20, 20};

static int draw_it_active = 1;
 
Fl_Color fl_inactive(Fl_Color c) {
  return (Fl_Color)(c*0.33 + 0.67 * FL_GRAY);
}   
 
/**
  Determines if the current draw box is active or inactive. 
  If inactive, the box color is changed by the inactive color.
*/
int Fl::draw_box_active() 
{ 
	return draw_it_active; 
}

const unsigned char *Fl::fl_gray_ramp() 
{
	return (draw_it_active?active_ramp:inactive_ramp)-'A';
}

/**
  Draws a series of line segments around the given box.
  The string \p s must contain groups of 4 letters which specify one of 24
  standard grayscale values, where 'A' is black and 'X' is white.
  The order of each set of 4 characters is: top, left, bottom, right.
  The result of calling fl_frame() with a string that is not a multiple
  of 4 characters in length is undefined.
  The only difference between this function and fl_frame2() is the order
  of the line segments.
  \param[in] s sets of 4 grayscale values in top, left, bottom, right order
  \param[in] x, y, w, h position and size
*/
void Fl::fl_frame(const char* s, int x, int y, int w, int h) 
{
  const uchar *g = fl_gray_ramp();
  if (h > 0 && w > 0) for (;*s;) {
    // draw top line:
    fl_line_color(g[(int)*s++]);
    fl_xyline(x, y+h, x+w);
    y++; if (--h <= 0) break;
    // draw left line:
    fl_line_color(g[(int)*s++]);
    fl_yxline(x, y+h, y);
    x++; if (--w <= 0) break;
    // draw bottom line:
    fl_line_color(g[(int)*s++]);
    fl_xyline(x, y, x+w);
    if (--h <= 0) break;
    // draw right line:
    fl_line_color(g[(int)*s++]);
    fl_yxline(x+w, y+h, y);
    if (--w <= 0) break;
  }
}

/**
  Draws a series of line segments around the given box.
  The string \p s must contain groups of 4 letters which specify one of 24
  standard grayscale values, where 'A' is black and 'X' is white.
  The order of each set of 4 characters is: bottom, right, top, left.
  The result of calling fl_frame2() with a string that is not a multiple
  of 4 characters in length is undefined.
  The only difference between this function and fl_frame() is the order
  of the line segments.
  \param[in] s sets of 4 grayscale values in bottom, right, top, left order
  \param[in] x, y, w, h position and size
*/
void Fl::fl_frame2(const char* s, int x, int y, int w, int h) 
{
  const uchar *g = fl_gray_ramp();
  if (h > 0 && w > 0) for (;*s;) {
    // draw bottom line:
    fl_line_color(g[(int)*s++]);
    fl_xyline(x, y, x+w);
    // draw right line:
    fl_line_color(g[(int)*s++]);
    fl_yxline(x+w, y+h, y);
    // draw top line:
    fl_line_color(g[(int)*s++]);
    fl_xyline(x, y+h, x+w);
    // draw left line:
    fl_line_color(g[(int)*s++]);
    fl_yxline(x, y+h, y);

    y++; x++; 
		h -= 2; w-= 2;
		if (w <= 0) break;
    if (h <= 0) break;
  }
}

/** Draws a box of type FL_NO_BOX */
void Fl::fl_no_box(int, int, int, int, Fl_Color) 
{}

void Fl::fl_rectf(int x, int y, int w, int h, Fl_Color c)
{
	fl_color(c);
	fl_rectf(x, y, w, h);
}

/** Draws a frame of type FL_THIN_DOWN_FRAME */
void Fl::fl_thin_down_frame(int x, int y, int w, int h, Fl_Color) 
{
  fl_frame2("WWHH",x,y,w,h);
}

/** Draws a box of type FL_THIN_DOWN_BOX */
void Fl::fl_thin_down_box(int x, int y, int w, int h, Fl_Color c) 
{
  fl_thin_down_frame(x,y,w,h,c); 
  fl_color(draw_it_active ? c : fl_inactive(c));
  fl_rectf(x+1, y+1, w-2, h-2);
}

/** Draws a frame of type FL_THIN_UP_FRAME */
void Fl::fl_thin_up_frame(int x, int y, int w, int h, Fl_Color) 
{
  fl_frame2("HHWW",x,y,w,h);
}

/** Draws a box of type FL_THIN_UP_BOX */
void Fl::fl_thin_up_box(int x, int y, int w, int h, Fl_Color c) 
{
  fl_thin_up_frame(x,y,w,h,c);
  fl_color(draw_it_active ? c : fl_inactive(c));
  fl_rectf(x+1, y+1, w-2, h-2);
}

/** Draws a frame of type FL_UP_FRAME */
void Fl::fl_up_frame(int x, int y, int w, int h, Fl_Color) 
{
#if BORDER_WIDTH == 1
  fl_frame2("HHWW",x,y,w,h);
#else
#if BORDER_WIDTH == 2
  //fl_frame2("AAWWMMTT",x,y,w,h);
  fl_frame2("AAWWMMTT",x,y,w,h);
#else
  fl_frame("AAAAWWJJUTNN",x,y,w,h);
#endif
#endif
}

#define D1 BORDER_WIDTH
#define D2 (BORDER_WIDTH+BORDER_WIDTH)

/** Draws a box of type FL_UP_BOX */
void Fl::fl_up_box(int x, int y, int w, int h, Fl_Color c) 
{
  fl_up_frame(x,y,w,h,c);
  //fl_color(draw_it_active ? c : fl_inactive(c));
  fl_color(c);
  fl_rectf(x+D1, y+D1, w-D2, h-D2);
}

/** Draws a frame of type FL_DOWN_FRAME */
void Fl::fl_down_frame(int x, int y, int w, int h, Fl_Color) 
{
#if BORDER_WIDTH == 1
  fl_frame2("WWHH",x,y,w,h);
#else
#if BORDER_WIDTH == 2
  fl_frame2("WWMMPPAA",x,y,w,h);
#else
  fl_frame("NNTUJJWWAAAA",x,y,w,h);
#endif
#endif
}

/** Draws a box of type FL_DOWN_BOX */
void Fl::fl_down_box(int x, int y, int w, int h, Fl_Color c) 
{
  fl_down_frame(x,y,w,h,c);
  fl_color(c); fl_rectf(x+D1, y+D1, w-D2, h-D2);
}

/** Draws a frame of type FL_ENGRAVED_FRAME */
void Fl::fl_engraved_frame(int x, int y, int w, int h, Fl_Color) 
{
  fl_frame("HHWWWWHH",x,y,w,h);
}

/** Draws a box of type FL_ENGRAVED_BOX */
void Fl::fl_engraved_box(int x, int y, int w, int h, Fl_Color c) 
{
  fl_engraved_frame(x,y,w,h,c);
  fl_color(draw_it_active ? c : fl_inactive(c));
  fl_rectf(x+2, y+2, w-4, h-4);
}

/** Draws a frame of type FL_EMBOSSED_FRAME */
void Fl::fl_embossed_frame(int x, int y, int w, int h, Fl_Color) 
{
  fl_frame("WWHHHHWW",x,y,w,h);
}

/** Draws a box of type FL_EMBOSSED_BOX */
void Fl::fl_embossed_box(int x, int y, int w, int h, Fl_Color c) 
{
  fl_color(draw_it_active ? c : fl_inactive(c));
  fl_rectf(x, y, w, h);

  fl_embossed_frame(x,y,w,h,c);
}

/**
  Draws a bounded rectangle with a given position, size and color.
  Equivalent to drawing a box of type FL_BORDER_BOX.
*/
void Fl::fl_rectbound(int x, int y, int w, int h, Fl_Color bgcolor) 
{
  //fl_color(draw_it_active ? FL_BLACK : fl_inactive(FL_BLACK));
  fl_color(FL_BLACK);
  fl_rectf(x, y, w, h);
  //fl_color(draw_it_active ? bgcolor : fl_inactive(bgcolor));
  fl_color(bgcolor);
  fl_rectf(x+2, y+2, w-4, h-4);
}
#define fl_border_box fl_rectbound  /**< allow consistent naming */

/**
  Draws a frame of type FL_BORDER_FRAME.
*/
void Fl::fl_border_frame(int x, int y, int w, int h, Fl_Color c) 
{
  fl_color(draw_it_active ? c : fl_inactive(c));
  fl_rectf(x, y, w, h);
}

////////////////////////////////////////////////////////////////
static struct 
{
  Fl_Box_Draw_F *f;
  uchar dx, dy, dw, dh;
  int set;
} 
fl_box_table[256] = 
{
// must match list in Enumerations.H!!!
  {Fl::fl_no_box,   0,0,0,0,1},
  {Fl::fl_rectf,    0,0,0,0,1}, // FL_FLAT_BOX
  {Fl::fl_up_box,   D1,D1,D2,D2,1},
  {Fl::fl_down_box,   D1,D1,D2,D2,1},
  {Fl::fl_up_frame,   D1,D1,D2,D2,1},
  {Fl::fl_down_frame, D1,D1,D2,D2,1},
  {Fl::fl_thin_up_box,  1,1,2,2,1},
  {Fl::fl_thin_down_box,  1,1,2,2,1},
  {Fl::fl_thin_up_frame,  1,1,2,2,1},
  {Fl::fl_thin_down_frame,  1,1,2,2,1},
  {Fl::fl_engraved_box, 2,2,4,4,1},
  {Fl::fl_embossed_box, 2,2,4,4,1},
  {Fl::fl_engraved_frame, 2,2,4,4,1},
  {Fl::fl_embossed_frame, 2,2,4,4,1},
  {Fl::fl_border_box, 1,1,2,2,1},
  {Fl::fl_border_box, 1,1,5,5,0}, // _FL_SHADOW_BOX,
  {Fl::fl_border_frame, 1,1,2,2,1},
  {Fl::fl_border_frame, 1,1,5,5,0}, // _FL_SHADOW_FRAME,
  {Fl::fl_border_box, 1,1,2,2,0}, // _FL_ROUNDED_BOX,
  {Fl::fl_border_box, 1,1,2,2,0}, // _FL_RSHADOW_BOX,
  {Fl::fl_border_frame, 1,1,2,2,0}, // _FL_ROUNDED_FRAME
  {Fl::fl_rectf,    0,0,0,0,0}, // _FL_RFLAT_BOX,
  {Fl::fl_up_box,   3,3,6,6,0}, // _FL_ROUND_UP_BOX
  {Fl::fl_down_box,   3,3,6,6,0}, // _FL_ROUND_DOWN_BOX,
  {Fl::fl_up_box,   0,0,0,0,0}, // _FL_DIAMOND_UP_BOX
  {Fl::fl_down_box,   0,0,0,0,0}, // _FL_DIAMOND_DOWN_BOX
  {Fl::fl_border_box, 1,1,2,2,0}, // _FL_OVAL_BOX,
  {Fl::fl_border_box, 1,1,2,2,0}, // _FL_OVAL_SHADOW_BOX,
  {Fl::fl_border_frame, 1,1,2,2,0}, // _FL_OVAL_FRAME
  {Fl::fl_rectf,    0,0,0,0,0}, // _FL_OVAL_FLAT_BOX,
  {Fl::fl_up_box,   4,4,8,8,0}, // _FL_PLASTIC_UP_BOX,
  {Fl::fl_down_box,   2,2,4,4,0}, // _FL_PLASTIC_DOWN_BOX,
  {Fl::fl_up_frame,   2,2,4,4,0}, // _FL_PLASTIC_UP_FRAME,
  {Fl::fl_down_frame, 2,2,4,4,0}, // _FL_PLASTIC_DOWN_FRAME,
  {Fl::fl_up_box,   2,2,4,4,0}, // _FL_PLASTIC_THIN_UP_BOX,
  {Fl::fl_down_box,   2,2,4,4,0}, // _FL_PLASTIC_THIN_DOWN_BOX,
  {Fl::fl_up_box,   2,2,4,4,0}, // _FL_PLASTIC_ROUND_UP_BOX,
  {Fl::fl_down_box,   2,2,4,4,0}, // _FL_PLASTIC_ROUND_DOWN_BOX,
  {Fl::fl_up_box,   2,2,4,4,0}, // _FL_GTK_UP_BOX,
  {Fl::fl_down_box,   2,2,4,4,0}, // _FL_GTK_DOWN_BOX,
  {Fl::fl_up_frame,   2,2,4,4,0}, // _FL_GTK_UP_FRAME,
  {Fl::fl_down_frame, 2,2,4,4,0}, // _FL_GTK_DOWN_FRAME,
  {Fl::fl_up_frame,   1,1,2,2,0}, // _FL_GTK_THIN_UP_FRAME,
  {Fl::fl_down_frame, 1,1,2,2,0}, // _FL_GTK_THIN_DOWN_FRAME,
  {Fl::fl_up_box,   1,1,2,2,0}, // _FL_GTK_THIN_ROUND_UP_BOX,
  {Fl::fl_down_box,   1,1,2,2,0}, // _FL_GTK_THIN_ROUND_DOWN_BOX,
  {Fl::fl_up_box,   2,2,4,4,0}, // _FL_GTK_ROUND_UP_BOX,
  {Fl::fl_down_box,   2,2,4,4,0}, // _FL_GTK_ROUND_DOWN_BOX,
  {Fl::fl_up_box,   3,3,6,6,0}, // FL_FREE_BOX+0
  {Fl::fl_down_box,   3,3,6,6,0}, // FL_FREE_BOX+1
  {Fl::fl_up_box,   3,3,6,6,0}, // FL_FREE_BOX+2
  {Fl::fl_down_box,   3,3,6,6,0}, // FL_FREE_BOX+3
  {Fl::fl_up_box,   3,3,6,6,0}, // FL_FREE_BOX+4
  {Fl::fl_down_box,   3,3,6,6,0}, // FL_FREE_BOX+5
  {Fl::fl_up_box,   3,3,6,6,0}, // FL_FREE_BOX+6
  {Fl::fl_down_box,   3,3,6,6,0}, // FL_FREE_BOX+7
};

void Fl::draw_box(Fl_Boxtype t, int X, int Y, int W, int H, Fl_Color c) 
{
	//draw_it_active = active_r(); 
	fl_box_table[t].f(X, Y, W, H, c);
	//draw_it_active = 1;
}

void Fl::draw_string(const std::string &str, Fl_Boxtype t, int X, int Y, int W, int H, Fl_Color c)
{
	vtkPoints2D *rect = vtkPoints2D::New();
	rect->InsertNextPoint(X, Y);
	rect->InsertNextPoint(X+W, Y+H);

	if (g_Painter) 
	{
		float bounds[4] = {0};
		g_Painter->ComputeStringBounds( str.c_str(), bounds);
		/*
		std::cout << "bounds: " 
			<< bounds[0] << ", " 
			<< bounds[1] << ", " 
			<< bounds[2] << ", "
			<< bounds[3] << std::endl;
			*/
		g_Painter->DrawString( 
				(int)(X + W / 2 - bounds[2] / 2),
				(int)(Y + H / 2 - bounds[3] / 2),
			 	str.c_str());
	}

	rect->Delete();
  //void DrawStringRect(vtkPoints2D *rect, const char* string);
}

void Fl::fl_color(int nIndex)
{
	/*
  if (g_Painter) g_Painter->GetPen()->SetColor( 
			CMap[nIndex][0],
			CMap[nIndex][1],
			CMap[nIndex][2]);
			*/
	vtkColor4ub color(CMap[nIndex][0],
			CMap[nIndex][1],
			CMap[nIndex][2]);
  if (g_Painter) g_Painter->GetBrush()->SetColor(color);
}

void Fl::fl_line_color(int nIndex)
{
  if (g_Painter) g_Painter->GetPen()->SetColor( 
			CMap[nIndex][0],
			CMap[nIndex][1],
			CMap[nIndex][2]);
}

void Fl::fl_xyline(int x, int y, int x1)
{
  if (g_Painter) g_Painter->DrawLine( x, y, x1, y);
}

void Fl::fl_yxline(int x, int y, int y1)
{
  if (g_Painter) g_Painter->DrawLine(x, y, x, y1);
}

void Fl::fl_rectf(int x, int y, int w, int h)
{
  if (g_Painter) g_Painter->DrawRect(x, y, w, h);
}

short Fl::CMap[FL_NUM_GRAY][3]={0};
vtkContext2D *Fl::g_Painter=0;

Fl* Fl::g_Fl = new Fl();
Fl::Fl()
{
	background(0xc0, 0xc0, 0xc0);
}

Fl::~Fl()
{
}

void Fl::SetPainter(vtkContext2D *context)
{
	g_Painter = context;
}

void Fl::background(uchar r, uchar g, uchar b)
{
  // replace the gray ramp so that color 47 (by default 2/3) is this color
  if (!r) r = 1; else if (r==255) r = 254;
  double powr = log(r/255.0)/log((FL_GRAY)/(FL_NUM_GRAY-1.0));
  if (!g) g = 1; else if (g==255) g = 254;
  double powg = log(g/255.0)/log((FL_GRAY)/(FL_NUM_GRAY-1.0));
  if (!b) b = 1; else if (b==255) b = 254;
  double powb = log(b/255.0)/log((FL_GRAY)/(FL_NUM_GRAY-1.0));
  for (int i = 0; i < FL_NUM_GRAY; i++) {
    double gray = i/(FL_NUM_GRAY-1.0);
    CMap[i][0] = uchar(pow(gray,powr)*255+.5); 
    CMap[i][1] = uchar(pow(gray,powg)*255+.5); 
    CMap[i][2] = uchar(pow(gray,powb)*255+.5); 
  } 
}
