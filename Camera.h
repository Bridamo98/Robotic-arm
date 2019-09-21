// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Camera__h__
#define __Camera__h__

#include "Vector.h"

/**
 */
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

#endif // __Camera__h__

// eof - Camera.h
