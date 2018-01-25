#include "MyVector3D.h"
#define PI 3.14159265358979323846


MyVector3D::MyVector3D():
	m_x{ 0.0 },
	m_y{ 0.0 },
	m_z{ 0.0 }
{
}

MyVector3D::MyVector3D(double x, double y, double z) :
	m_x{ x },
	m_y{ y },
	m_z{ z }
{
}

MyVector3D::MyVector3D(sf::Vector3f sfVector) :
	m_x{ static_cast<double>(sfVector.x) },
	m_y{static_cast<double>(sfVector.y) },
	m_z{static_cast<double>(sfVector.z) }
{
}

MyVector3D::~MyVector3D()
{
}

std::string MyVector3D::toString()
{
	char tmpbuf[256];	
	sprintf_s(tmpbuf, "[ %g, %g, %g ]", m_x, m_y, m_z);
	return tmpbuf;
}

double MyVector3D::X()const
{
	return m_x;
}

double MyVector3D::Y()const
{
	return m_y;
}

double MyVector3D::Z()const
{
	return m_z;
}

MyVector3D MyVector3D::operator+(const MyVector3D right) const
{
	return MyVector3D(m_x + right.m_x, m_y + right.m_y, m_z + right.m_z);
}

MyVector3D MyVector3D::operator-(const MyVector3D right) const
{
	return MyVector3D(m_x - right.m_x, m_y - right.m_y, m_z - right.m_z);
}

MyVector3D MyVector3D::operator*(const double scalar) const
{
	return MyVector3D(m_x * scalar, m_y * scalar, m_z * scalar);
}

MyVector3D MyVector3D::operator/(const double divisor) const
{
	if (divisor != 0)
	{
		return MyVector3D(m_x / divisor, m_y / divisor, m_z / divisor);
	}
	else
	{
		return MyVector3D();
	}
}

MyVector3D MyVector3D::operator+=(const MyVector3D right)
{
	m_x += right.m_x;
	m_y += right.m_y;
	m_z += right.m_z;
	return MyVector3D(m_x, m_y, m_z);
}

MyVector3D MyVector3D::operator-=(const MyVector3D right)
{
	m_x -= right.m_x;
	m_y -= right.m_y;
	m_z -= right.m_z;
	return MyVector3D(m_x, m_y, m_z);	
}

bool MyVector3D::operator==(const MyVector3D right) const
{
	if (m_x == right.m_x && m_y == right.m_y && m_z == right.m_z)
	{
		return true;
	}
	return false;
}

bool MyVector3D::operator!=(const MyVector3D right) const
{
	return !(this->operator==(right));
}

MyVector3D MyVector3D::operator-()
{
	return MyVector3D(-m_x, -m_y, -m_z);
}

double MyVector3D::length() const
{
	const double result = std::sqrt(m_x*m_x + m_y*m_y + m_z* m_z) ;
	return result;
}

double MyVector3D::lengthSquared() const
{
	const double result = std::pow(m_x, 2) + std::pow(m_y, 2) + std::pow(m_z, 2);
	return result;
}

void MyVector3D::normalise()
{
	const double orignalLenght = length();
	m_x /= orignalLenght;
	m_y /= orignalLenght;
	m_z /= orignalLenght;
}
