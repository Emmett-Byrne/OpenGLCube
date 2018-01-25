#include "MyMatrix3.h"

MyMatrix3::MyMatrix3():
	m11{ 0.0 },
	m12{ 0.0 },
	m13{ 0.0 },
	m21{ 0.0 },
	m22{ 0.0 },
	m23{ 0.0 },
	m31{ 0.0 },
	m32{ 0.0 },
	m33{ 0.0 }
{
}

MyMatrix3::MyMatrix3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33) :
	m11{ a11 },
	m12{ a12 },
	m13{ a13 },
	m21{ a21 },
	m22{ a22 },
	m23{ a23 },
	m31{ a31 },
	m32{ a32 },
	m33{ a33 }
{
}

MyMatrix3::MyMatrix3(MyVector3D row1, MyVector3D row2, MyVector3D row3)
{
	m11 = row1.X();
	m12 = row1.Y();
	m13 = row1.Z();
	m21 = row2.X();
	m22 = row2.Y();
	m23 = row2.Z();
	m31 = row3.X();
	m32 = row3.Y();
	m33 = row3.Z();
}

MyMatrix3::~MyMatrix3()
{
}

std::string MyMatrix3::toString()
{
	char tmpbuf[512];
	sprintf_s(tmpbuf, "{ [ %g, %g, %g ] [ %g, %g, %g ] [ %g, %g, %g ] }", m11, m12, m13, m21, m22, m23, m31, m32, m33);
	return tmpbuf;
}

MyMatrix3 MyMatrix3::operator+(const MyMatrix3 other) const
{
	return MyMatrix3(m11 + other.m11, m12 + other.m12, m13 + other.m13, m21 + other.m21, m22 + other.m22, m23 + other.m23, m31 + other.m31, m32 + other.m32, m33 + other.m33 );
}

MyMatrix3 MyMatrix3::operator-(const MyMatrix3 other) const
{
	return MyMatrix3(m11 - other.m11, m12 - other.m12, m13 - other.m13, m21 - other.m21, m22 - other.m22, m23 - other.m23, m31 - other.m31, m32 - other.m32, m33 - other.m33);
}

MyMatrix3 MyMatrix3::operator*(const MyMatrix3 other) const
{
	double a11 = m11 * other.m11 + m12*other.m21 + m13 * other.m31;
	double a12 = m11 * other.m12 + m12*other.m22 + m13 * other.m32;
	double a13 = m11 * other.m13 + m12*other.m23 + m13 * other.m33;
	double a21 = m21 * other.m11 + m22*other.m21 + m23 * other.m31;
	double a22 = m21 * other.m12 + m22*other.m22 + m23 * other.m32;
	double a23 = m21 * other.m13 + m22*other.m23 + m23 * other.m33;
	double a31 = m31 * other.m11 + m32*other.m21 + m33 * other.m31;
	double a32 = m31 * other.m12 + m32*other.m22 + m33 * other.m32;
	double a33 = m31 * other.m13 + m32*other.m23 + m33 * other.m33;
	return MyMatrix3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
}

MyVector3D MyMatrix3::operator*(const MyVector3D vector) const
{
	return MyVector3D(m11*vector.X() + m12 * vector.Y() + m13 * vector.Z(), m21*vector.X() + m22 * vector.Y() + m23 * vector.Z(), m31*vector.X() + m32 * vector.Y() + m33 * vector.Z());
}

MyMatrix3 MyMatrix3::operator*(const double scale) const
{
	return MyMatrix3(m11 * scale, m12 * scale, m13 * scale, m21 * scale, m22 * scale, m23 * scale, m31 * scale, m32 * scale, m33 * scale);
}

MyMatrix3 MyMatrix3::transpose() const
{
	double a11 = m11;
	double a12 = m21;
	double a13 = m31;
	double a21 = m12;
	double a22 = m22;
	double a23 = m32;
	double a31 = m13;
	double a32 = m23;
	double a33 = m33;
	return MyMatrix3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
}

double MyMatrix3::determinant() const
{
	return (m11 * ((m22 * m33) - (m23 * m32))) - (m12 * ((m21 * m33) - (m23 * m31))) + (m13 * ((m21 * m32) - (m22 * m31)));
}

MyMatrix3 MyMatrix3::Inverse() const
{

	MyMatrix3 adjugate(	m33 * m22 - m32 * m23, m32 * m13 - m33 * m12, m23 * m12 - m22 * m13,
						m31 * m23 - m33 * m21, m33 * m11 - m31 * m13, m21 * m13 - m23 * m11,
						m32 * m21 - m31 * m22, m31 * m12 - m32 * m11, m22 * m11 - m21 * m12);

	return adjugate * (1 / this->determinant());
}

MyVector3D MyMatrix3::row(int row) const
{
	if (row == 1)
	{
		return MyVector3D(m11, m12, m13);
	}
	if (row == 2)
	{
		return MyVector3D(m21, m22, m23);
	}
	if (row == 3)
	{
		return MyVector3D(m31, m32, m33);
	}

	return MyVector3D(0,0,0);
}

MyVector3D MyMatrix3::column(int column) const
{
	if (column == 1)
	{
		return MyVector3D(m11, m21, m31);
	}
	if (column == 2)
	{
		return MyVector3D(m12, m22, m32);
	}
	if (column == 3)
	{
		return MyVector3D(m13, m23, m33);
	}

	return MyVector3D(0, 0, 0);
}

bool MyMatrix3::operator==(const MyMatrix3 other) const
{
	if (m11 == other.m11 && m12 == other.m12 && m13 == other.m13 &&
		m21 == other.m21 && m22 == other.m22 && m23 == other.m23 &&
		m31 == other.m31 && m32 == other.m32 && m33 == other.m33)
	{
		return true;
	}
	return false;
}

bool MyMatrix3::operator!=(const MyMatrix3 other) const
{
	return !(this->operator==(other));
}

MyMatrix3 MyMatrix3::rotationZ(double angleRadians)
{
	return MyMatrix3	(cos(angleRadians), -sin(angleRadians),0,
						sin(angleRadians), cos(angleRadians),0,
						0,0,1);
}

MyMatrix3 MyMatrix3::rotationY(double angleRadians)
{
	return MyMatrix3	(cos(angleRadians), 0, sin(angleRadians),
						0, 1, 0,
						-sin(angleRadians), 0, cos(angleRadians));
}

MyMatrix3 MyMatrix3::rotationX(double angleRadians)
{
	return MyMatrix3	(1, 0, 0,
						0, cos(angleRadians), -sin(angleRadians),
						0, sin(angleRadians), cos(angleRadians));
}

MyMatrix3 MyMatrix3::translation(int x, int y)
{

	MyMatrix3 answer;
	answer.m11 = 1;
	answer.m12 = 0;
	answer.m13 = 0;
	answer.m21 = 0;
	answer.m22 = 1;
	answer.m23 = 0;
	answer.m31 = x;
	answer.m32 = y;
	answer.m33 = 1;

	return answer;
}

MyMatrix3 MyMatrix3::scale(int x, int y)
{
	MyMatrix3 answer;
	answer.m11 = (double)x / 100;
	answer.m12 = 0;
	answer.m13 = 0;
	answer.m21 = 0;
	answer.m22 = (double)y / 100;
	answer.m23 = 0;
	answer.m31 = 0;
	answer.m32 = 0;
	answer.m33 = 1;

	return answer;
}
