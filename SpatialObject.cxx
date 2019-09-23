// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "SpatialObject.h"
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>

#define _PI 3.1415926535897932384626433832795
#define _180_PI ( 180.0/_PI )

// -------------------------------------------------------------------------
SpatialObject::
SpatialObject( )
  : m_Mesh( nullptr ),
    m_Mesh2( nullptr ),
    artSel(0)
    //r(0.0),
    //angx(0.0),
    //angy(0.0),
    //angz(0.0),
    //m_CurrentAngle( 0 ),
    //m_Animating( false )
{
  //this->_createPath( );
  std::string("a");

}

// -------------------------------------------------------------------------
SpatialObject::
SpatialObject( const std::string& fname )// se ejecuta este
  : m_Mesh( nullptr ),
    m_Mesh2( nullptr ),
    artSel(0)
    //r(0.0),
    //angx(0.0),
    //angy(0.0),
    //angz(0.0),
    //m_CurrentAngle( 0 ),
    //m_Animating( false )
{
  //this->_createPath( );
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
  this->m_Name = name;
  buffer >> this;
}

// -------------------------------------------------------------------------
SpatialObject::
~SpatialObject( )
{
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  if( this->m_Mesh2 != nullptr )
    delete this->m_Mesh2;
  for( SpatialObject* c: this->m_Children )
    delete c;
  this->m_Children.clear( );
}

// -------------------------------------------------------------------------
Mesh* SpatialObject::
getMesh( )
{
  return( this->m_Mesh );
}

// -------------------------------------------------------------------------
const Mesh* SpatialObject::
getMesh( ) const
{
  return( this->m_Mesh );
}
// -------------------------------------------------------------------------
Mesh* SpatialObject::
getMesh2( )
{
  return( this->m_Mesh2 );
}

// -------------------------------------------------------------------------
const Mesh* SpatialObject::
getMesh2( ) const
{
  return( this->m_Mesh2 );
}

// -------------------------------------------------------------------------
void SpatialObject::
addChild( SpatialObject* o )
{
  this->m_Children.push_back( o );
}
//--------------------------------------------------------------------------
void SpatialObject::
setName(int name){
  this->m_Name = name;
}

// -------------------------------------------------------------------------
unsigned long SpatialObject::
getNumberOfChildren( ) const
{
  return( this->m_Children.size( ) );
}

// -------------------------------------------------------------------------
SpatialObject* SpatialObject::
getChild( unsigned long i )
{
  return( this->m_Children[ i ] );
}

// -------------------------------------------------------------------------
const SpatialObject* SpatialObject::
getChild( unsigned long i ) const
{
  return( this->m_Children[ i ] );
}

// -------------------------------------------------------------------------
const int& SpatialObject::
getName( ) const
{
  return( this->m_Name );
}

// -------------------------------------------------------------------------
/*const float& SpatialObject::
getScale( ) const
{
  return( this->m_Scale );
}*/

// -------------------------------------------------------------------------
/*void SpatialObject::
setPath( float r1, float r2, float nx, float ny, float nz )
{
  this->m_Radius1 = r1;
  this->m_Radius2 = r2;
  this->m_Normal[ 0 ] = nx;
  this->m_Normal[ 1 ] = ny;
  this->m_Normal[ 2 ] = nz;
  this->m_Normal.normalize( );
}*/

// -------------------------------------------------------------------------
void SpatialObject::
startAnimation( )
{
  //this->m_Animating = true;
  //this->m_StartAnimation = std::chrono::high_resolution_clock::now( );
  //for( SpatialObject* child: this->m_Children )
    //child->startAnimation( );
}

// -------------------------------------------------------------------------
void SpatialObject::
stopAnimation( )
{
  //this->m_Animating = false;
  //for( SpatialObject* child: this->m_Children )
    //child->stopAnimation( );
}
//--------------------------------------------------------------------------
void SpatialObject::
moveArt(int name, unsigned char axis, int sense){
  if(name == this->m_Name){
    std::cout<<"entra con nombre "<<this->m_Name<<std::endl;
    switch(axis){
      case'x':case'X':{
        std::cout<<"entra con nombre-- "<<this->m_Name<<std::endl;
        this->artSel = 1*sense;
      }
      break;
      case'y':case'Y':{
        this->artSel = 2*sense;
        std::cout<<"entra con nombre-- "<<this->m_Name<<std::endl;
      }
      break;
      case'z':case'Z':{
        this->artSel = 3*sense;
        std::cout<<"entra con nombre-- "<<this->m_Name<<std::endl;
      }
      break;
      default:
        std::cout<<"no entra con nombre-- "<<this->m_Name<<" y eje "<<axis<<std::endl;
      break;
    }
  }else{
    for( SpatialObject* child: this->m_Children )
      child->moveArt(name, axis, sense);  
  }
  
}

// -------------------------------------------------------------------------
void SpatialObject::
drawInOpenGLContext( GLenum mode )
{
  if( this->m_Mesh == nullptr )
    return;

  // Save call matrix
  glPushMatrix( );

  //glRotatef(this->angz,0,0,1);
  if(this->artSel!=0){
    switch(this->artSel){
      case -3:{
        this->angz = this->angz-1.0;
        glRotatef(this->angz,0,0,1);
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -2:{
        this->angy = this->angy -1.0;
        glRotatef(this->angy,0,1,0);
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -1:{
        this->angx = this->angx-1.0;
        glRotatef(this->angx,1,0,0);
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case 1:{
        this->angx = this->angx+1.0;
        std::cout<<"-------"<<artSel<<std::endl;
        glRotatef(this->angx,1,0,0);
      }        
        break;
      case 2:{
        this->angy = this->angy+1.0;
        std::cout<<"-------"<<artSel<<std::endl;
        glRotatef(this->angy,0,1,0);
      }        
        break;
      case 3:{
        this->angz = this->angz+1.0;
        glRotatef(this->angz,0,0,1); 
        std::cout<<"-------"<<artSel<<std::endl;
      }        
        break;
      default:
        std::cout<<"default"<<std::endl;
        break;
    }
    this->artSel = 0;
  }

  //std::cout<<this->angx<<"-"<<this->angy<<"-"<<this->angz<<std::endl;

  //glScalef( this->m_Radius1, this->m_Radius2, 1 );
  //this->m_Path->drawInOpenGLContext( GL_LINE_LOOP );
  this->m_Mesh->drawInOpenGLContext( mode );


  // Show spatial body
  /*if( this->m_Animating && this->m_Frequency > 0 )
  {
    Compute ellapsed milliseconds since aninamtion has started
    double s =
      std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::high_resolution_clock::now( ) - this->m_StartAnimation
        ).count( );
    this->m_CurrentAngle = 2.0 * _PI * s / ( this->m_Frequency * 1000.0 );
  } // end if*/
  glPushMatrix( );
  glRotatef(this->angy,0,1,0);
  glRotatef(this->angx,1,0,0);
  glTranslatef(0,this->r/2.0,0);
  glScalef( 1, this->r, 1 );
  this->m_Mesh2->drawInOpenGLContext( mode );
  glPopMatrix( );

  glTranslatef(pos[0],pos[1],pos[2]);

  //glPushMatrix();
  //this->m_Mesh->drawInOpenGLContext(mode);
  //glPopMatrix();

  // Show children
  for( SpatialObject* child: this->m_Children )
    child->drawInOpenGLContext( mode );

  // Get call matrix
  glPopMatrix( );
}

// -------------------------------------------------------------------------
/*void SpatialObject::
_createPath( )
{
  if( this->m_Path != nullptr )
    delete this->m_Path;
  this->m_Path = new Mesh( );

  unsigned int nSamples = 100;
  std::vector< unsigned int > face;
  for( unsigned int i = 0; i < nSamples; ++i )
  {
    float a = 2.0 * _PI * float( i ) / float( nSamples );
    this->m_Path->addPoint( std::cos( a ), std::sin( a ), 0 );
    face.push_back( i + 1 );
  } // end for
    face.push_back( 1 );
  this->m_Path->addFace( face );
}*/

// -------------------------------------------------------------------------
void SpatialObject::
_strIn( std::istream& in )
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
  this->m_Name = 1;

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
    this->setPath( path[ 0 ], path[ 0 ], path[ 1 ], path[ 2 ], path[ 3 ] );
  else if( path.size( ) == 5 )
    this->setPath( path[ 0 ], path[ 1 ], path[ 2 ], path[ 3 ], path[ 4 ] );
  else
    throw std::runtime_error( "Malformed path." );

  // Check base model// yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'M' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"M\" is required." );
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  this->m_Mesh = new Mesh( dIt->second );

  // Check color//yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'C' );
  float r = 1, g = 1, b = 1;
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> r >> g >> b;
  } // end if
  this->m_Mesh->setColor( r, g, b );

  // Check scale//esto si vaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'S' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> this->m_Scale;
  }
  else
    this->m_Scale = 1;

  // Check frequency//esto no vaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'F' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> this->m_Frequency;
  }
  else
    this->m_Frequency = 0;

  // Check recursion//yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
  dIt = data.find( 'D' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    unsigned int nRecs;
    d >> nRecs;
    for( unsigned int i = 0; i < nRecs; ++i )
    {
      SpatialObject* child = new SpatialObject( );
      in >> child;
      this->addChild( child );
    } // end for
  } // end if*/
  //--------------------------------------------------------------
  std::string line;
  float x, y, z;
  std::getline( in, line );
  std::istringstream b( line );
  b >> x >> y >> z;
  std::cout<< x <<" "<< y <<" "<< z <<std::endl;
  this->pos[0]=x;
  this->pos[1]=y;
  this->pos[2]=z;
  float r = std::sqrt((x*x)+(y*y)+(z*z));
  this->r = r;
  std::cout<<this->r<<std::endl;
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

  this->angx = theta*_180_PI;
  this->angy = phi*_180_PI;
  this->angz = -theta*_180_PI;

  std::cout<<this->angx<<" "<<this->angy<<" "<<this->angz<<std::endl;
  
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  this->m_Mesh = new Mesh( "dodecaedro.obj" );
  if( this->m_Mesh2 != nullptr )
    delete this->m_Mesh2;
  this->m_Mesh2 = new Mesh( "cube.obj" );
  this->m_Mesh->setColor( 1, 1, 1 );//articulación
  this->m_Mesh2->setColor( 0.5, 0.5, 0.5 );//brazo

  if(this->m_Name >1){
    SpatialObject* child = new SpatialObject( );
    child->setName(this->m_Name - 1);
    in >> child;
    this->addChild( child );
  }



}

// -------------------------------------------------------------------------
void SpatialObject::
_strOut( std::ostream& out ) const
{
}

// eof - SpatialObject.cxx
