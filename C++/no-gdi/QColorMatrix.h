#pragma once

// QColorMatrix
//
// Extension of the GDI+ struct ColorMatrix.
// Adds some member functions so you can actually do something with it.
// Use QColorMatrix like ColorMatrix to update the ImmageAttributes class.
// Use at your own risk. Comments welcome.
//
// See: http://www.sgi.com/grafica/matrix/
// http://www.sgi.com/software/opengl/advanced98/notes/node182.html
//
// (c) 2003, Sjaak Priester, Amsterdam.
// mailto:sjaak@sjaakpriester.nl
//
//
// Removed GDI+ code and cleaned up: 
// (c) 2010, Vasian Cepa
// 
// How to use:
//
// ColorEffects::QColorMatrix qm;
// qm.SetHue(45);
// qm.SetSaturation2(0.9f);
// qm.SetBrightness(0.9f);
//
// for(each pixel(rgb) in image)
// {
//  ColorEffects::QColorMatrix::Color c(r, g, b);
//  qm.TransformColors(&c);
//  // set back c.GetR(), etc ...
// }

namespace ColorEffects
{

typedef float REAL;

class QColorMatrix
{
public:

	enum MatrixOrder
	{
		MatrixOrderPrepend    = 0,
		MatrixOrderAppend     = 1
	};

	struct Color
	{
	public:
		Color();
		Color(REAL r, REAL g, REAL b)
		{
			Init(r, g, b);
		}
		Color(REAL a, REAL r, REAL g, REAL b)
		{
			Init(a, r, g, b);
		}

		void Init(REAL r, REAL g, REAL b)
		{
			Init(255, r, g, b);
		}

		void Init(REAL a, REAL r, REAL g, REAL b)
		{
			SetA(a);
			SetR(r);
			SetG(g);
			SetB(b);
		}

		float GetA(){ return p[3]; }
		float GetR(){ return p[0]; }
		float GetG(){ return p[1]; }
		float GetB(){ return p[2]; }

		void SetA(REAL v){ p[3] = v; }
		void SetR(REAL v){ p[0] = v; }
		void SetG(REAL v){ p[1] = v; }
		void SetB(REAL v){ p[2] = v; }

		void Normalize();

		REAL p[4];
	};//EOC

	QColorMatrix()
	{ Reset(); }
	QColorMatrix(const QColorMatrix& m)
	{ Copy(m); }
	~QColorMatrix()
	{ }

	QColorMatrix& operator=(const QColorMatrix& m)
	{ if (this != &m) Copy(m); return *this; }

	// Create a new QColorMatrix that is a copy.	
	QColorMatrix* Clone()
	{ return new QColorMatrix(*this); }

	// Update matrix to the identity matrix (1.0f on diagonal, rest 0.0f)
	void Reset();

	// Multiply the vector by the matrix. v points to an array of four values,
	// representing R, G, B and A.
	void TransformVector(REAL* v) const;

	// Multiply each color by the matrix. count is the number of colors.
	void TransformColors(Color* colors, int count = 1) const;

	// Update this matrix with the product of itself and another matrix.
	void Multiply(const QColorMatrix* matrix, MatrixOrder order = MatrixOrderPrepend);

	// Update this matrix with the product of itself and a scaling vector.
	void Scale(REAL scaleRed, REAL scaleGreen, REAL scaleBlue,
				REAL scaleOpacity = 1.0f, MatrixOrder order = MatrixOrderPrepend);

	// Scale just the three colors with the same amount, leave opacity unchanged.
	void ScaleColors(REAL scale, MatrixOrder order = MatrixOrderPrepend)
	{ return Scale(scale, scale, scale, 1.0f, order); }

	// Scale just the opacity, leave R, G and B unchanged.
	void ScaleOpacity(REAL scaleOpacity, MatrixOrder order = MatrixOrderPrepend)
	{ return Scale(1.0f, 1.0f, 1.0f, scaleOpacity, order); }

	// Update this matrix with the product of itself and a translation vector.	
	void Translate(REAL offsetRed, REAL offsetGreen, REAL offsetBlue,
				REAL offsetOpacity, MatrixOrder order = MatrixOrderPrepend);

	// Translate just the three colors with the same amount, leave opacity unchanged.
	void TranslateColors(REAL offset, MatrixOrder order = MatrixOrderPrepend)
	{ return Translate(offset, offset, offset, 0.0f, order); }

	// Translate just the opacity, leave R, G and B unchanged.
	void TranslateOpacity(REAL offsetOpacity, MatrixOrder order = MatrixOrderPrepend)
	{ return Translate(0.0f, 0.0f, 0.0f, offsetOpacity, order); }

	// Rotate the matrix around one of the color axes. The color of the rotation
	// axis is unchanged, the other two colors are rotated in color space.
	// The angle phi is in degrees (-180.0f... 180.0f).
	void RotateRed(REAL phi, MatrixOrder order = MatrixOrderPrepend)
	{ return RotateColor(phi, 2, 1, order); }
	void RotateGreen(REAL phi, MatrixOrder order = MatrixOrderPrepend)
	{ return RotateColor(phi, 0, 2, order); }
	void RotateBlue(REAL phi, MatrixOrder order = MatrixOrderPrepend)
	{ return RotateColor(phi, 1, 0, order); }

	// Shear the matrix in one of the color planes. The color of the color plane
	// is influenced by the two other colors.
	void ShearRed(REAL green, REAL blue, MatrixOrder order = MatrixOrderPrepend)
	{ return ShearColor(0, 1, green, 2, blue, order); }
	void ShearGreen(REAL red, REAL blue, MatrixOrder order = MatrixOrderPrepend)
	{ return ShearColor(1, 0, red, 2, blue, order); }
	void ShearBlue(REAL red, REAL green, MatrixOrder order = MatrixOrderPrepend)
	{ return ShearColor(2, 0, red, 1, green, order); }
	
	// Set the saturation of the matrix. Saturation of 0.0f yields B&W, 1.0f is neutral.
	void SetSaturation(REAL saturation, MatrixOrder order = MatrixOrderPrepend);

	// Rotate the hue around the grey axis, keeping luminance fixed. Greys are fixed,
	// all other colours change.
	void RotateHue(REAL phi);

	void SetContrast(REAL scale)
	{
		ScaleColors(scale);
	}

	void SetBrightness(REAL offset)
	{
		TranslateColors(offset, MatrixOrderAppend);
	}

	void SetSaturation2(REAL saturation)
	{
		SetSaturation(saturation, MatrixOrderAppend);
	}

	void SetHue(REAL phi)
	{
		RotateHue(phi);
	}

public:

	REAL m[5][5];

private:

	void Copy(const QColorMatrix& m);
	void RotateColor(REAL phi, int x, int y, MatrixOrder order = MatrixOrderPrepend);
	void ShearColor(int x, int y1, REAL d1, int y2, REAL d2, MatrixOrder order = MatrixOrderPrepend);

	static void InitHue();
	static bool initialized;
	static QColorMatrix preHue;
	static QColorMatrix postHue;
};//EOC

} //EON