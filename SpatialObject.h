// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __SpatialObject__h__
#define __SpatialObject__h__

#include "Vector.h"
#include "Mesh.h"
#include <chrono>

/**
 */
class SpatialObject
{
public:
  //! Streaming methods
  //@{
  friend std::istream& operator>>( std::istream& i, SpatialObject& s )
    {
      s._strIn( i );
      return( i );
    }

  friend std::istream& operator>>( std::istream& i, SpatialObject* s )
    {
      s->_strIn( i );
      return( i );
    }

  friend std::ostream& operator<<( std::ostream& o, const SpatialObject& s )
    {
      s._strOut( o );
      return( o );
    }

  friend std::ostream& operator<<( std::ostream& o, const SpatialObject* s )
    {
      s->_strOut( o );
      return( o );
    }
  //@}

public:
  //! Memory management
  //@{
  SpatialObject( );
  SpatialObject( const std::string& fname );
  virtual ~SpatialObject( );
  //@}

  //! Mesh-related methods
  //@{
  Mesh* getMesh( );
  const Mesh* getMesh( ) const;
  Mesh* getMesh2( );
  const Mesh* getMesh2( ) const;
  //@}

  //! All the magic happens here
  //@{
  void addChild( SpatialObject* o );
  void setName( int name);
  unsigned long getNumberOfChildren( ) const;
  SpatialObject* getChild( unsigned long i );
  const SpatialObject* getChild( unsigned long i ) const;
  //@}

  //! Other methods
  //@{
  const int& getName( ) const;
  //const float& getScale( ) const;
  //@}

  //void setPath( float r1, float r2, float nx, float ny, float nz );//Esto no va

  //! All the magic happens here
  virtual void startAnimation( );//esto no va
  virtual void moveArt(int name, unsigned char axis, int sense);
  virtual void stopAnimation( );//esto no va
  virtual void drawInOpenGLContext( GLenum mode );//esto va

protected:
  //void _createPath( );//esto no va

  //! Here's where the real streaming is done
  //@{
  void _strIn( std::istream& in );
  void _strOut( std::ostream& out ) const;
  //@}

protected:
  int m_Name;
  //float       m_Scale;
  Mesh*       m_Mesh;
  Mesh*       m_Mesh2;
  //Mesh*       m_Path;
  float       r;
  float       ang[3];
  float       d[3];
  float       pos[3];
  bool ultimo;

  //float m_Radius1;
  //float m_Radius2;
  //Vector m_Normal;

  //float m_Frequency;
  //float m_CurrentAngle;
  //bool m_Animating;
  int         artSel;
  //std::chrono::time_point< std::chrono::high_resolution_clock > m_StartAnimation;

  std::vector< SpatialObject* > m_Children;
};

#endif // __SpatialObject__h__

// eof - SpatialObject.h
