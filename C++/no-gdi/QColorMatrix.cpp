#include "QColorMatrix.h"

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

#include <math.h>
#include <string.h> // for memset, memcpy

namespace ColorEffects
{

const REAL pi = 4.0f * (REAL) atan(1.0);
const REAL rad = pi / 180.0f;

// The luminance weight factors for the RGB color space.
// These values are actually preferable to the better known factors of
// Y = 0.30R + 0.59G + 0.11B, the formula which is used in color television technique.
const REAL lumR = 0.3086f;
const REAL lumG = 0.6094f;
const REAL lumB = 0.0820f;

// statics
bool QColorMatrix::initialized = false;
QColorMatrix QColorMatrix::preHue;
QColorMatrix QColorMatrix::postHue;


QColorMatrix::Color::Color()
{
	p[0] = p[1] = p[2] = 0.0f;
	p[3] = 255;
}

void QColorMatrix::Color::Normalize()
{
	for(int i = 0; i < 4; i++)
	{
		if(p[i] < 0.0f) p[i] = 0.0f;
		else if(p[i] > 255.0f) p[i] = 255.0f;
	}
}

void QColorMatrix::Reset()
{
	::memset(m, 0, 25 * sizeof(REAL));
	for (int i = 0; i < 5; i++) m[i][i] = 1.0f;
}

void QColorMatrix::Multiply(const QColorMatrix * matrix, MatrixOrder order /* = MatrixOrderPrepend */)
{
	if (!matrix) return;

	REAL (* a)[5];
	REAL (* b)[5];

	if (order == MatrixOrderAppend)
	{
		a = (REAL (*)[5]) matrix->m;
		b = m;
	}
	else
	{
		a = m;
		b = (REAL (*)[5]) matrix->m;
	}

	REAL temp[5][5];

	for (int y = 0; y < 5 ; y++)
	{
        for (int x = 0; x < 5; x++)
		{
			REAL t = 0;
			for (int i = 0; i < 5; i++)
			{
				t += b[y][i] * a[i][x];
			}
            temp[y][x] = t;
        }
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
            m[y][x] = temp[y][x];
		}
	}
}

// Assumes that v points to (at least) four REALs.
void QColorMatrix::TransformVector(REAL * v) const
{
	if (! v) return;
	REAL temp[4];
	for (int x = 0; x < 4; x++)
	{
		temp[x] = 255.0f * m[4][x];
		for (int y = 0; y < 4; y++) temp[x] += v[y] * m[y][x];
	}
	for (int x = 0; x < 4; x++) v[x] = temp[x];
}

void QColorMatrix::TransformColors(Color * colors, int count /* = 1 */) const
{
	if (! colors) return;
	for (int i = 0; i < count; i++)
	{
		TransformVector(colors[i].p);
		colors[i].Normalize();
	}
}

// phi is in degrees
// x and y are the indices of the value to receive the sin(phi) value
void QColorMatrix::RotateColor(REAL phi, int x, int y, MatrixOrder order /* = MatrixOrderPrepend */)
{
	phi *= rad;
	QColorMatrix qm;

	qm.m[x][x] = qm.m[y][y] = (REAL) cos(phi);

	REAL s = (REAL) sin(phi);
	qm.m[y][x] = s;
	qm.m[x][y] = - s;

	Multiply(&qm, order);
}

void QColorMatrix::ShearColor(int x, int y1, REAL d1, int y2, REAL d2, MatrixOrder order /* = MatrixOrderPrepend */)
{
	QColorMatrix qm;
	qm.m[y1][x] = d1;
	qm.m[y2][x] = d2;
	Multiply(&qm, order);
}

void QColorMatrix::Scale(REAL scaleRed, REAL scaleGreen,
					 REAL scaleBlue, REAL scaleOpacity, MatrixOrder order /* = MatrixOrderPrepend */)
{
	QColorMatrix qm;

	qm.m[0][0] = scaleRed;
	qm.m[1][1] = scaleGreen;
	qm.m[2][2] = scaleBlue;
	qm.m[3][3] = scaleOpacity;

	return Multiply(&qm, order);
}

void QColorMatrix::Translate(REAL offsetRed, REAL offsetGreen,
				   REAL offsetBlue, REAL offsetOpacity, MatrixOrder order /* = MatrixOrderPrepend */)
{
	QColorMatrix qm;

	qm.m[4][0] = offsetRed;
	qm.m[4][1] = offsetGreen;
	qm.m[4][2] = offsetBlue;
	qm.m[4][3] = offsetOpacity;

	return Multiply(&qm, order);
}

void QColorMatrix::SetSaturation(REAL saturation, MatrixOrder order /* = MatrixOrderPrepend */)
{
	// For the theory behind this, see the web sites at the top of this file.
	// In short: if saturation is 1.0f, m becomes the identity matrix, and this matrix is
	// unchanged. If saturation is 0.0f, each color is scaled by it's luminance weight.
	REAL satCompl = 1.0f - saturation;
	REAL satComplR = lumR * satCompl;
	REAL satComplG = lumG * satCompl;
	REAL satComplB = lumB * satCompl;

	QColorMatrix qm;
	qm.m[0][0] = satComplR + saturation;
	qm.m[0][1] = satComplR;
	qm.m[0][2] = satComplR;
	
	qm.m[1][0] = satComplG;
	qm.m[1][1] = satComplG + saturation;
	qm.m[1][2] = satComplG;

	qm.m[2][0] = satComplB;
	qm.m[2][1] = satComplB;
	qm.m[2][2] = satComplB + saturation;
	/*
	{
		satComplR + saturation,	satComplR,	satComplR,	0.0f, 0.0f,
		satComplG,	satComplG + saturation,	satComplG,	0.0f, 0.0f,
		satComplB,	satComplB,	satComplB + saturation,	0.0f, 0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	0.0f,	1.0f
	};
	*/
	return Multiply(&qm, order);
}

void QColorMatrix::RotateHue(REAL phi)
{
	InitHue();

	// Rotate the grey vector to the blue axis.
	Multiply(&preHue, MatrixOrderAppend);

	// Rotate around the blue axis
	RotateBlue(phi, MatrixOrderAppend);

	Multiply(&postHue, MatrixOrderAppend);
}

void QColorMatrix::Copy(const QColorMatrix& mat)
{
	::memcpy(m, mat.m, 25 * sizeof(REAL));
}

/* static */
void QColorMatrix::InitHue()
{
	//const REAL greenRotation = 35.0f;
	const REAL greenRotation = 39.182655f;

	// NOTE: theoretically, greenRotation should have the value of 39.182655 degrees,
	// being the angle for which the sine is 1/(sqrt(3)), and the cosine is sqrt(2/3).
	// However, I found that using a slightly smaller angle works better.
	// In particular, the greys in the image are not visibly affected with the smaller
	// angle, while they deviate a little bit with the theoretical value.
	// An explanation escapes me for now.
	// If you rather stick with the theory, change the comments in the previous lines.


	if (! initialized)
	{
		initialized = true;
		// Rotating the hue of an image is a rather convoluted task, involving several matrix
		// multiplications. For efficiency, we prepare two static matrices.
		// This is by far the most complicated part of this class. For the background
		// theory, refer to the sgi-sites mentioned at the top of this file.

		// Prepare the preHue matrix.
		// Rotate the grey vector in the green plane.
		preHue.RotateRed(45.0f);

		// Next, rotate it again in the green plane, so it coincides with the blue axis.
		preHue.RotateGreen(-greenRotation, MatrixOrderAppend);

		// Hue rotations keep the color luminations constant, so that only the hues change
		// visible. To accomplish that, we shear the blue plane.
		REAL lum[4] = { lumR, lumG, lumB, 1.0f };

		// Transform the luminance vector.
		preHue.TransformVector(lum);

		// Calculate the shear factors for red and green.
		REAL red = lum[0] / lum[2];
		REAL green = lum[1] / lum[2];

		// Shear the blue plane.
		preHue.ShearBlue(red, green, MatrixOrderAppend);

		// Prepare the postHue matrix. This holds the opposite transformations of the
		// preHue matrix. In fact, postHue is the inversion of preHue.
		postHue.ShearBlue(-red, -green);
		postHue.RotateGreen(greenRotation, MatrixOrderAppend);
		postHue.RotateRed(-45.0f, MatrixOrderAppend);
	}
}

}
