// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

//#include "Camera.h"
#include "Vector.cxx"
#include <cmath>
#include <GL/glu.h>

class Camera
{
public:
  //! Memory management
  //@{
  Camera( );
  virtual ~Camera( );
  //@}

  void move( const Vector& dir );
  void rotX( float a );
  void rotY( float a );
  void rotZ( float a );

  void forward( float d );
  void upward( float d );
  void strafe( float d );

  void getReference( int& dx, int& dy, int x, int y );
  void setReference( int x, int y );

  void loadCameraMatrix( );

  void setFOV( float a );
  void setPlanes( float n, float f );
  void setWindow( int w, int h );
  void loadProjectionMatrix( );

protected:
  float m_FOV;
  float m_Near;
  float m_Far;
  int m_WindowWidth;
  int m_WindowHeight;

  Vector m_Focus;
  Vector m_RightVector; 
  Vector m_UpVector;
  Vector m_Position;
  Vector m_Rotations;

  int m_RefX;
  int m_RefY;
};

// -------------------------------------------------------------------------
Camera::
Camera( )
{
  setFOV( 45 );
  setWindow( 1, 1 );
  setPlanes( 1e-2, 10000 );

  m_Position = Vector( );
  m_Focus = Vector( 0, 0, -1 );
  m_RightVector = Vector ( 1 );
  m_UpVector = Vector( 0, 1 );
  m_Rotations = Vector( );
  m_RefX = m_RefY = 0;
}

// -------------------------------------------------------------------------
Camera::
~Camera( )
{
}

// -------------------------------------------------------------------------
void Camera::
move( const Vector& dir )
{
  m_Position += dir;
}

// -------------------------------------------------------------------------
void Camera::
rotX( float a )
{
  m_Rotations[ 0 ] = a;
        
  float o = a * _PI_180;
  m_Focus = 
    ( m_Focus * std::cos( o ) ) +
    ( m_UpVector * std::sin( o ) );
  m_Focus.normalize( );
  
  m_UpVector = ( m_Focus * m_RightVector ) * -1.0;
}

// -------------------------------------------------------------------------
void Camera::
rotY( float a )
{
  m_Rotations[ 1 ] = a;
        
  float o = a * _PI_180;
  m_Focus =
    ( m_Focus * std::cos( o ) ) -
    ( m_RightVector * std::sin( o ) );
  m_Focus.normalize( );

  m_RightVector = m_Focus * m_UpVector;
}

// -------------------------------------------------------------------------
void Camera::
rotZ( float a )
{
  m_Rotations[ 2 ] = a;
        
  float o = a * _PI_180;
  m_RightVector =
    ( m_RightVector * std::cos( o ) ) +
    ( m_UpVector * std::sin( o ) );
  m_RightVector.normalize( );
  
  m_UpVector = ( m_Focus * m_RightVector ) * -1.0;
}

// -------------------------------------------------------------------------
void Camera::
forward( float d )
{
  m_Position += m_Focus * d;
}

// -------------------------------------------------------------------------
void Camera::
upward( float d )
{
  m_Position += m_UpVector * d;
}

// -------------------------------------------------------------------------
void Camera::
strafe( float d )
{
  m_Position += m_RightVector * d;
}

// -------------------------------------------------------------------------
void Camera::
getReference( int& dx, int& dy, int x, int y )
{
  dx = x - m_RefX;
  dy = y - m_RefY;
}

// -------------------------------------------------------------------------
void Camera::
setReference( int x, int y )
{
  m_RefX = x;
  m_RefY = y;
}

// -------------------------------------------------------------------------
void Camera::
loadCameraMatrix( )
{
  Vector f = m_Position + m_Focus;

  gluLookAt(
    m_Position[ 0 ], m_Position[ 1 ], m_Position[ 2 ], 
    f[ 0 ], f[ 1 ], f[ 2 ], 
    m_UpVector[ 0 ], m_UpVector[ 1 ], m_UpVector[ 2 ]
    );
}

// -------------------------------------------------------------------------
void Camera::
setFOV( float a )
{
  m_FOV = std::fmod( a, 360 );
}

// -------------------------------------------------------------------------
void Camera::
setPlanes( float n, float f )
{
  m_Near = n;
  m_Far = f;
}

// -------------------------------------------------------------------------
void Camera::
setWindow( int w, int h )
{
  m_WindowWidth = ( w > 0 )? w: 1;
  m_WindowHeight = ( h > 0 )? h: 1;
}

// -------------------------------------------------------------------------
void Camera::
loadProjectionMatrix( )
{
  glViewport( 0, 0, m_WindowWidth, m_WindowHeight );
  gluPerspective(
    m_FOV,
    float( m_WindowWidth ) / float( m_WindowHeight ),
    m_Near,
    m_Far
    );
}

// eof - Camera.cxx
