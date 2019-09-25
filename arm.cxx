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
	  float        r;
	  float		   _theta;
	  float		   _phi;
	  float*       ang;
	  float*       d;
	  float*       posi;
	  float*       posa;	
	  //bool ultimo;

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
	ang = new float[2];
	d = new float[3];
	posi = new float[3];
	posa = new float[3];
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
  glColor3f(1,1,1);
  glPushMatrix( );
  

  //glRotatef(angz,0,0,1);
  if(artSel!=0){
    switch(artSel){
      case -3:{
        d[2] = d[2]-1.0;
        _theta += 1.0;
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -2:{
        d[1] = d[1] -1.0;
        _phi -=1.0;
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -1:{
        d[0] = d[0]-1.0;
        _theta -= 1.0;
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case 1:{
        d[0] = d[0]+1.0;
        _theta += 1.0;
        std::cout<<"-------"<<artSel<<std::endl;

      }
        break;
      case 2:{
        d[1] = d[1]+1.0;
        _phi += 1.0;
        std::cout<<"-------"<<artSel<<std::endl;

      }
        break;
      case 3:{
        d[2] = d[2]+1.0;
        _theta -= 1.0;
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      default:
        std::cout<<"default"<<std::endl;
        break;
    }
    artSel = 0;
  }
  posa[0] = r * std::sin(_theta) * std::sin(_phi);
  posa[1] = r * std::cos(_theta);
  posa[2] = r * std::sin(_theta) * std::cos(_phi);

  glRotatef(d[2],0,0,1);
  glRotatef(d[1],0,1,0);
  glRotatef(d[0],1,0,0);

  glutWireSphere( 1, 10, 10 );//..............................................ESFERA......................................

  glPushMatrix( );
  glRotatef(ang[1],0,1,0);
  glRotatef(ang[0],1,0,0);
  glColor3f(1,1,0);
  glTranslatef(0,r/2.0,0);
  glScalef( 1, r, 1 );
  glutWireCube(1);//cubo de tamaño 1...................................................................
  glPopMatrix( );

  glTranslatef(posi[0],posi[1],posi[2]);

  // Show children
  bool atLeastOneChild = false;
  for( Arm* child: m_Children ){
  	child->drawInOpenGLContext( mode );
  	atLeastOneChild = true;
  }
    

  if(atLeastOneChild){
  	posa[0] = posa[0] + m_Children[0]->posa[0];
	posa[1] = posa[1] + m_Children[0]->posa[1];
	posa[2] = posa[2] + m_Children[0]->posa[2];

	std::cout<<"pos acumnulada en "<<m_Name<<" = "<<posa[0] << " "<<posa[1] <<" "<<posa[2]<<std::endl;

  }
  
  // Get call matrix
  glPopMatrix( );
}

void Arm::_strIn( std::istream& in )
{
  std::string line;
  float x, y, z;
  std::getline( in, line );
  std::istringstream b( line );
  b >> x >> y >> z;
  std::cout<< x <<" "<< y <<" "<< z <<std::endl;
  std::cout<<"1"<<std::endl;

  posi[0]=x;
  posi[1]=y;
  posi[2]=z;
  posa[0]=x;
  posa[1]=y;
  posa[2]=z;
  d[0]=0.0;
  d[1]=0.0;
  d[2]=0.0;
  float rr = std::sqrt((x*x)+(y*y)+(z*z));
  r = rr;
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
  _theta = theta;
  _phi = phi;
  //ang[2] = -theta*_180_PI;//Angulo en z, por el momento no se necesita.

  std::cout<<ang[0]<<" "<<ang[1]<<std::endl;

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