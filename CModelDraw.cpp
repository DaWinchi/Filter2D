#include "stdafx.h"
#include "CModelDraw.h"
#include <math.h>

using namespace Gdiplus;
ULONG_PTR token1;
CModelDraw::CModelDraw()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token1, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"Îøèáêà", MB_ICONERROR);
	}
}


CModelDraw::~CModelDraw()
{
	GdiplusShutdown(token1);
}


void CModelDraw::DrawItem(LPDRAWITEMSTRUCT RECT)
{
	
	Graphics gr(RECT->hDC);
	Bitmap bmp(RECT->rcItem.right, RECT->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);
	grBmp.SetSmoothingMode(SmoothingModeHighSpeed);
	grBmp.Clear(Color::White);
	
	if (_image!=nullptr)
	{
		size_t width = _image[0][0].size();
		size_t height = _image->size();
		xmin = 0;
		xmax = width;
		ymin = 0;
		ymax = height;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				double val = _image[0][i][j];
				Color color;
				color = Color::MakeARGB(255 - val, 0, 0, 0);
				SolidBrush brush(color);
				grBmp.FillRectangle(&brush, X(RECT, j), Y(RECT, i), Width(RECT, 1), Height(RECT, 1));
			}
		}
	}

	if (_R != nullptr)
	{
		Pen pen(Color::Red, 2);
		grBmp.DrawEllipse(&pen, X(RECT, xmax / 2.f - (double)*_R), Y(RECT, ymax / 2.f + (double)*_R),
			Width(RECT, (float)*_R*2.f), Height(RECT, (float)*_R*2.f));
	}
	gr.DrawImage(&bmp, 0, 0);
}


REAL CModelDraw::X(LPDRAWITEMSTRUCT RECT, float x)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*((x)-xmin);
}

REAL CModelDraw::Y(LPDRAWITEMSTRUCT RECT, float y)
{
	return -(REAL)(RECT->rcItem.bottom) / (ymax - ymin)*((y)-ymax);
}

REAL CModelDraw::Width(LPDRAWITEMSTRUCT RECT, float width)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*width;
}

REAL CModelDraw::Height(LPDRAWITEMSTRUCT RECT, float height)
{
	return (REAL)(RECT->rcItem.bottom) / (ymax - ymin)*height;
}

void CModelDraw::Update()
{
	Invalidate();
}