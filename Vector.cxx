// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

//#include "Vector.h"
#include <cmath>
#include <cstring>

#define _PI 3.1415926535897932384626433832795
#define _PI_180 ( _PI / 180.0 )

/**
 */
class Vector
{
public:
  //! Memory management
  //@{
  Vector( const float& x = 0, const float& y = 0, const float& z = 0 );
  Vector( float* p );
  Vector( double* p );
  Vector( const Vector& r );
  Vector& operator=( const Vector& r );
  virtual ~Vector( );
  //@}

  //! Random acces
  //@{
  float& operator[]( const unsigned int& i );
  const float& operator[]( const unsigned int& i ) const;
  //@}

  //! Base arithmetic
  //@{
  Vector operator+( const Vector& r ) const;
  Vector& operator+=( const Vector& r );

  Vector operator-( const Vector& r ) const;
  Vector& operator-=( const Vector& r );
  //@}

  //! Dot product
  //@{
  float operator/( const Vector& r ) const;
  //@}

  //! Cross product
  //@{
  Vector operator*( const Vector& r ) const;
  Vector& operator*=( const Vector& r );
  //@}

  //! Scalar product
  //@{
  Vector operator*( const float& r ) const;
  Vector operator*( const double& r ) const;

  Vector& operator*=( const float& r );
  Vector& operator*=( const double& r );

  Vector operator/( const float& r ) const;
  Vector operator/( const double& r ) const;

  Vector& operator/=( const float& r );
  Vector& operator/=( const double& r );
  //@}

  //! Normalization
  //@{
  float getNorm( ) const;
  void normalize( );
  //@}

protected:
  float m_V[ 3 ];
};
// -------------------------------------------------------------------------
Vector::
Vector( const float& x, const float& y, const float& z )
{
  m_V[ 0 ] = x;
  m_V[ 1 ] = y;
  m_V[ 2 ] = z;
}

// -------------------------------------------------------------------------
Vector::
Vector( float* p )
{
  std::memcpy( m_V, p, 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
Vector::
Vector( double* p )
{
  m_V[ 0 ] = float( p[ 0 ] );
  m_V[ 1 ] = float( p[ 1 ] );
  m_V[ 2 ] = float( p[ 2 ] );
}

// -------------------------------------------------------------------------
Vector::
Vector( const Vector& r )
{
  std::memcpy( m_V, r.m_V, 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator=( const Vector& r )
{
  std::memcpy( m_V, r.m_V, 3 * sizeof( float ) );
  return( *this );
}

// -------------------------------------------------------------------------
Vector::
~Vector( )
{
}

// -------------------------------------------------------------------------
float& Vector::
operator[]( const unsigned int& i )
{
  return( m_V[ i ] );
}

// -------------------------------------------------------------------------
const float& Vector::
operator[]( const unsigned int& i ) const
{
  return( m_V[ i ] );
}

// -------------------------------------------------------------------------
Vector Vector::
operator+( const Vector& r ) const
{
  return(
    Vector(
      m_V[ 0 ] + r.m_V[ 0 ],
      m_V[ 1 ] + r.m_V[ 1 ],
      m_V[ 2 ] + r.m_V[ 2 ]
      )
    );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator+=( const Vector& r )
{
  m_V[ 0 ] += r.m_V[ 0 ];
  m_V[ 1 ] += r.m_V[ 1 ];
  m_V[ 2 ] += r.m_V[ 2 ];
  return( *this );
}

// -------------------------------------------------------------------------
Vector Vector::
operator-( const Vector& r ) const
{
  return(
    Vector(
      m_V[ 0 ] - r.m_V[ 0 ],
      m_V[ 1 ] - r.m_V[ 1 ],
      m_V[ 2 ] - r.m_V[ 2 ]
      )
    );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator-=( const Vector& r )
{
  m_V[ 0 ] -= r.m_V[ 0 ];
  m_V[ 1 ] -= r.m_V[ 1 ];
  m_V[ 2 ] -= r.m_V[ 2 ];
  return( *this );
}

// -------------------------------------------------------------------------
float Vector::
operator/( const Vector& r ) const
{
  float c = m_V[ 0 ] * r.m_V[ 0 ];
  c      += m_V[ 1 ] * r.m_V[ 1 ];
  c      += m_V[ 2 ] * r.m_V[ 2 ];
  return( c );
}

// -------------------------------------------------------------------------
Vector Vector::
operator*( const Vector& r ) const
{
  return(
    Vector(
      ( m_V[ 1 ] * r.m_V[ 2 ] ) - ( m_V[ 2 ] * r.m_V[ 1 ] ),
      ( m_V[ 2 ] * r.m_V[ 0 ] ) - ( m_V[ 0 ] * r.m_V[ 2 ] ),
      ( m_V[ 0 ] * r.m_V[ 1 ] ) - ( m_V[ 1 ] * r.m_V[ 0 ] )
      )
    );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator*=( const Vector& r )
{
  *this = *this * r;
  return( *this );
}

// -------------------------------------------------------------------------
Vector Vector::
operator*( const float& r ) const
{
  return(
    Vector(
      m_V[ 0 ] * r, m_V[ 1 ] * r,m_V[ 2 ] * r
      )
    );
}

// -------------------------------------------------------------------------
Vector Vector::
operator*( const double& r ) const
{
  return( operator*( float( r ) ) );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator*=( const float& r )
{
  m_V[ 0 ] *= r;
  m_V[ 1 ] *= r;
  m_V[ 2 ] *= r;
  return( *this );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator*=( const double& r )
{
  m_V[ 0 ] *= float( r );
  m_V[ 1 ] *= float( r );
  m_V[ 2 ] *= float( r );
  return( *this );
}

// -------------------------------------------------------------------------
Vector Vector::
operator/( const float& r ) const
{
  return(
    Vector(
      m_V[ 0 ] / r, m_V[ 1 ] / r,m_V[ 2 ] / r
      )
    );
}

// -------------------------------------------------------------------------
Vector Vector::
operator/( const double& r ) const
{
  return( operator/( float( r ) ) );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator/=( const float& r )
{
  m_V[ 0 ] /= r;
  m_V[ 1 ] /= r;
  m_V[ 2 ] /= r;
  return( *this );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator/=( const double& r )
{
  m_V[ 0 ] /= float( r );
  m_V[ 1 ] /= float( r );
  m_V[ 2 ] /= float( r );
  return( *this );
}

// -------------------------------------------------------------------------
float Vector::
getNorm( ) const
{
  return( std::sqrt( *this / *this ) );
}

// -------------------------------------------------------------------------
void Vector::
normalize( )
{
  float n = getNorm( );
  *this /= ( ( 1e-5 < n )? n: 1.0 );
}

// eof - Vector.cxx
