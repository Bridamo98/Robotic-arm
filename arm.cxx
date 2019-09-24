//#include "Vector.h"
//#include "Mesh.h"

#include <chrono>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#define _PI 3.1415926535897932384626433832795
#define _180_PI ( 180.0/_PI )

class Arm {       // The class
  public:             // Access specifier
      int m_Name;
	  //float       m_Scale;
	  //Mesh*       m_Mesh;//reemplazar por lo que vimos la ultima clase
	  //Mesh*       m_Mesh2;//.........................................
	  //Mesh*       m_Path;
	  float       r;
	  float*     ang;
	  float*       d;
	  float*       pos;
	  bool ultimo;

	  //float m_Radius1;
	  //float m_Radius2;
	  //Vector m_Normal;

	  //float m_Frequency;
	  //float m_CurrentAngle;
	  //bool m_Animating;
	  int         artSel;
	  //std::chrono::time_point< std::chrono::high_resolution_clock > m_StartAnimation;

	  std::vector< Arm* > m_Children;
    Arm( );
  	Arm(const std::string& fname );
  	void drawInOpenGLContext( GLenum mode );
  	void _strIn( std::istream& in );
  	//Mesh* getMesh( );
//Mesh* getMesh2( );
void addChild( Arm* o );
void setName(int name);
unsigned long getNumberOfChildren( );
Arm* getChild( unsigned long i );
int& getName( );
void moveArt(int name, unsigned char axis, int sense);
};
Arm::Arm( )
    //r(0.0),
    //angx(0.0),
    //angy(0.0),
    //angz(0.0),
    //m_CurrentAngle( 0 ),
    //m_Animating( false )
{
  //_createPath( );
	ang = new float[3];
	d = new float[3];
	pos = new float[3];
  std::string("a");

}

Arm::Arm( const std::string& fname )// se ejecuta este
  : artSel(0)
    //r(0.0),
    //angx(0.0),
    //angy(0.0),
    //angz(0.0),
    //m_CurrentAngle( 0 ),
    //m_Animating( false )
{
	//_createPath( );
  std::cout<<"a"<<std::endl;
  // Open file and put its contents into a string buffer
  std::ifstream in( fname.c_str( ) );
  if( !in )
  {
  //std::cout<<"a"<<std::endl;

    in.close( );
    throw std::runtime_error(
      std::string( "Error: Could not open \"" ) + fname + "\""
      );
  } // end if
  std::istringstream buffer(
    std::string(
      ( std::istreambuf_iterator< char >( in ) ),
      std::istreambuf_iterator< char >( )
      )
    );
  in.close( );

  // Read file
  std::string line;
  int name;
  std::getline( buffer, line );
  std::istringstream a( line );
  a >> name;
  m_Name = name;
  _strIn( buffer );
}


// -------------------------------------------------------------------------
void Arm::addChild( Arm* o )
{
  m_Children.push_back( o );
}
//--------------------------------------------------------------------------
void Arm::setName(int name){
  m_Name = name;
}

// -------------------------------------------------------------------------
unsigned long Arm::getNumberOfChildren( ) 
{
  return( m_Children.size( ) );
}

// -------------------------------------------------------------------------
Arm* Arm::getChild( unsigned long i )
{
  return( m_Children[ i ] );
}
// -------------------------------------------------------------------------
int& Arm::getName( ) 
{
  return( m_Name );
}
//--------------------------------------------------------------------------
void Arm::moveArt(int name, unsigned char axis, int sense){
  if(name == m_Name){
    std::cout<<"entra con nombre "<<m_Name<<std::endl;
    switch(axis){
      case'x':case'X':{
        std::cout<<"entra con nombre-- "<<m_Name<<std::endl;
        artSel = 1*sense;
      }
      break;
      case'y':case'Y':{
        artSel = 2*sense;
        std::cout<<"entra con nombre-- "<<m_Name<<std::endl;
      }
      break;
      case'z':case'Z':{
        artSel = 3*sense;
        std::cout<<"entra con nombre-- "<<m_Name<<std::endl;
      }
      break;
      default:
        std::cout<<"no entra con nombre-- "<<m_Name<<" y eje "<<axis<<std::endl;
      break;
    }
  }else{
    for( Arm* child: m_Children )
      child->moveArt(name, axis, sense);
  }
}

void Arm::drawInOpenGLContext( GLenum mode )
{
  //if( m_Mesh == nullptr )
    //return;

  // Save call matrix
  glPushMatrix( );
  glColor3f(1,1,1);
  

  //glRotatef(angz,0,0,1);
  if(artSel!=0){
    switch(artSel){
      case -3:{
        d[2] = d[2]-1.0;

        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -2:{
        d[1] = d[1] -1.0;

        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -1:{
        d[0] = d[0]-1.0;

        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case 1:{
        d[0] = d[0]+1.0;
        std::cout<<"-------"<<artSel<<std::endl;

      }
        break;
      case 2:{
        d[1] = d[1]+1.0;
        std::cout<<"-------"<<artSel<<std::endl;

      }
        break;
      case 3:{
        d[2] = d[2]+1.0;

        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      default:
        std::cout<<"default"<<std::endl;
        break;
    }
    artSel = 0;
  }
  glRotatef(d[2],0,0,1);
  glRotatef(d[1],0,1,0);
  glRotatef(d[0],1,0,0);

  //std::cout<<angx<<"-"<<angy<<"-"<<angz<<std::endl;

  //glScalef( m_Radius1, m_Radius2, 1 );
  //m_Path->drawInOpenGLContext( GL_LINE_LOOP );

  glutWireCube(1);( mode );//cubo de tamaño 1...................................................................


  // Show spatial body
  /*if( m_Animating && m_Frequency > 0 )
  {
    Compute ellapsed milliseconds since aninamtion has started
    double s =
      std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::high_resolution_clock::now( ) - m_StartAnimation
        ).count( );
    m_CurrentAngle = 2.0 * _PI * s / ( m_Frequency * 1000.0 );
  } // end if*/
  glPushMatrix( );
  glRotatef(ang[1],0,1,0);
  glRotatef(ang[0],1,0,0);
  //glRotatef(angy-(_PI/2.0),0,1,0);
  //glRotatef(angz,0,0,1);

  glTranslatef(0,r/2.0,0);
  glScalef( 1, r, 1 );
  glutWireDodecahedron();//..............................................ESFERA......................................
  glPopMatrix( );

  glTranslatef(pos[0],pos[1],pos[2]);

  //glPushMatrix();
  //m_Mesh->drawInOpenGLContext(mode);
  //glPopMatrix();

  // Show children
  for( Arm* child: m_Children )
    child->drawInOpenGLContext( mode );

  // Get call matrix
  glPopMatrix( );
}

void Arm::_strIn( std::istream& in )
{
  /*typedef std::map< char, std::string > _TMap;

  // Read data for this spatial object//esto no vaaaaaaaaaaaa
  std::string line;
  std::getline( in, line );
  _TMap data;
  while( line.substr( 0, 2 ) != "--" )
  {
    std::istringstream d( line );
    char data_type;
    d >> data_type;

    std::string data_value;
    std::string v;
    d >> data_value;
    while( !d.eof( ) )
    {
      std::string v;
      d >> v;
      data_value += " " + v;
    } // end while
    data[ data_type ] = data_value;
    std::getline( in, line );
  } // end while

  // Check name//yaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  _TMap::const_iterator dIt = data.find( 'N' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"N\" is required." );
  m_Name = 1;

  // Check path//esto no vaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'P' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"P\" is required." );
  std::istringstream path_str( dIt->second );
  std::vector< float > path;
  while( !path_str.eof( ) )
  {
    path.push_back( 0 );
    path_str >> path.back( );
  } // end while
  if( path.size( ) == 4 )
    setPath( path[ 0 ], path[ 0 ], path[ 1 ], path[ 2 ], path[ 3 ] );
  else if( path.size( ) == 5 )
    setPath( path[ 0 ], path[ 1 ], path[ 2 ], path[ 3 ], path[ 4 ] );
  else
    throw std::runtime_error( "Malformed path." );

  // Check base model// yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'M' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"M\" is required." );
  if( m_Mesh != nullptr )
    delete m_Mesh;
  m_Mesh = new Mesh( dIt->second );

  // Check color//yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'C' );
  float r = 1, g = 1, b = 1;
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> r >> g >> b;
  } // end if
  m_Mesh->setColor( r, g, b );

  // Check scale//esto si vaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'S' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> m_Scale;
  }
  else
    m_Scale = 1;

  // Check frequency//esto no vaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'F' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> m_Frequency;
  }
  else
    m_Frequency = 0;

  // Check recursion//yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'D' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    unsigned int nRecs;
    d >> nRecs;
    for( unsigned int i = 0; i < nRecs; ++i )
    {
      Arm* child = new Arm( );
      in >> child;
      addChild( child );
    } // end for
  } // end if*/
  //--------------------------------------------------------------
  std::string line;
  float x, y, z;
  std::getline( in, line );
  std::istringstream b( line );
  b >> x >> y >> z;
  std::cout<< x <<" "<< y <<" "<< z <<std::endl;
  std::cout<<"1"<<std::endl;

  pos[0]=x;
  std::cout<<"1"<<std::endl;
  pos[1]=y;
  pos[2]=z;
  d[0]=0.0;
  d[1]=0.0;
  d[2]=0.0;
  float r = std::sqrt((x*x)+(y*y)+(z*z));
  r = r;
  std::cout<<r<<std::endl;
  float theta = 0.0, phi = 0.0;
  if(y > 0.0){
    theta = std::atan(std::sqrt((z*z)+(x*x))/y);
    std::cout<<"y mayor a 0"<<std::endl;
  }
  if(y == 0.0){
    std::cout<<"y igual a 0"<<std::endl;
    theta = _PI/2.0;
  }
  if(y < 0.0){
    std::cout<<"y menor a 0"<<std::endl;
    theta = _PI + std::atan(std::sqrt((z*z)+(x*x))/y);
  }
  if(z > 0.0 && x > 0.0){
    std::cout<<"z mayor a 0 y x mayor a 0"<<std::endl;
    phi = std::atan(x/z);
  }
  if (z > 0.0 && x < 0.0){
    std::cout<<"z mayor a 0 y x menor a 0"<<std::endl;
    phi = (2*_PI)+std::atan(x/z);
  }
  if(z == 0.0){
    std::cout<<"z igual a 0"<<std::endl;
    if(x < 0.0){
      std::cout<<"x menor a 0"<<std::endl;
      phi = (_PI/2.0)*(-1.0);
    }else{
      std::cout<<"x mayor o igual a 0"<<std::endl;
      phi = (_PI/2.0);
    }
  }
  if(z < 0.0){
    std::cout<<"z menor a 0"<<std::endl;
    phi = _PI + std::atan(x/z);
  }

  ang[0] = theta*_180_PI;
  ang[1] = phi*_180_PI;
  ang[2] = -theta*_180_PI;

  std::cout<<ang[0]<<" "<<ang[1]<<" "<<ang[2]<<std::endl;

  

  if(m_Name >1){
    std::cout<<"1"<<std::endl;
    Arm* child = new Arm( );
    std::cout<<"1"<<std::endl;
    child->setName(m_Name - 1);
    std::cout<<"1"<<std::endl;
    child->_strIn(in);
    std::cout<<"1"<<std::endl;
    addChild( child );
    std::cout<<"1"<<std::endl;
  }



}