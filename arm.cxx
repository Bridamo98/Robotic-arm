#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#define _PI 3.1415926535897932384626433832795
#define _180_PI ( 180.0/_PI )
//--------------------------------------------------------------------------
class Arm {
  public:             
    int m_Name;
	float*       posa;	
	float*	   rotx;
	float*	   roty;
	float*	   rotz;
	int         artSel;
	std::vector< Arm* > m_Children;
    Arm( );
  	Arm(const std::string& fname );
  	void drawInOpenGLContext( GLenum mode, bool rotated, float rotAng, char axisRot,float* posAct, int artAct, 
  							char axisAct, GLUquadricObj* myObject, bool grabbed, float* colorBall, int rBall, 
  							GLUquadricObj* ball);
  	void _strIn( std::istream& in );
	void addChild( Arm* o );
	void setName(int name);
	unsigned long getNumberOfChildren( );
	Arm* getChild( unsigned long i );
	int& getName( );
	void moveArt(int name, unsigned char axis, int sense);
	void rotVect	(float* vect,char axis,float angl);
	void drawBase( );
};
//--------------------------------------------------------------------------
Arm::Arm( )
{
	posa = new float[3];
	rotx = new float[3];
	roty = new float[3];
	rotz = new float[3];
	artSel = 0;
}
//--------------------------------------------------------------------------
Arm::Arm( const std::string& fname ): artSel(0)
{
  // Open file and put its contents into a string buffer
  std::ifstream in( fname.c_str( ) );
  if( !in )
  {
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
//--------------------------------------------------------------------------
void Arm::drawBase( )
{
  glLineWidth(1);
  glBegin( GL_LINES );
  {
    glColor3f( 1, 0, 0 );
    glVertex3f(  0, 1, 0 );
    glVertex3f( rotx[0]*1000, rotx[1]*1000 + 1, rotx[2]*1000 );

    glColor3f( 0, 1, 0 );
    glVertex3f( 0,  0, 0 );
    glVertex3f( roty[0]*1000, roty[1]*1000, roty[2]*1000 );

    glColor3f( 0, 0, 1 );
    glVertex3f( 0, 1,  0 );
    glVertex3f( rotz[0]*1000, rotz[1]*1000 + 1, rotz[2]*1000);
  }
  glEnd( );
}
//--------------------------------------------------------------------------
void Arm::rotVect	(float* vect, char axis, float angl) 
{ 
    
    float** mat1 = new float*[4];
    float** mat2 = new float*[4];
    float** res = new float*[4];

    for(int i = 0; i < 4; ++i)
    	mat1[i] = new float[4];

    for(int i = 0; i < 4; ++i)
    	mat2[i] = new float[1];

    for(int i = 0; i < 4; ++i)
    	res[i] = new float[1];

    mat2[0][0]=vect[0];
	mat2[1][0]=vect[1];
	mat2[2][0]=vect[2];
    mat2[3][0]=1;

    switch(axis){
    	case 'x':{
    		mat1[0][0]=1.0;
    		mat1[0][1]=0.0;
    		mat1[0][2]=0.0;
    		mat1[0][3]=0.0;
    		mat1[1][0]=0.0;
    		mat1[1][1]=std::cos(angl);
    		mat1[1][2]=-std::sin(angl);
    		mat1[1][3]=0.0;
    		mat1[2][0]=0.0;
    		mat1[2][1]=std::sin(angl);
    		mat1[2][2]=std::cos(angl);
    		mat1[2][3]=0.0;
    		mat1[3][0]=0.0;
    		mat1[3][1]=0.0;
    		mat1[3][2]=0.0;
    		mat1[3][3]=1.0;	
    	}break;
    	case 'y':{
    		mat1[0][0]=std::cos(angl);
    		mat1[0][1]=0.0;
    		mat1[0][2]=std::sin(angl);
    		mat1[0][3]=0.0;
    		mat1[1][0]=0.0;
    		mat1[1][1]=1.0;
    		mat1[1][2]=0.0;
    		mat1[1][3]=0.0;
    		mat1[2][0]=-std::sin(angl);
    		mat1[2][1]=0.0;
    		mat1[2][2]=std::cos(angl);
    		mat1[2][3]=0.0;
    		mat1[3][0]=0.0;
    		mat1[3][1]=0.0;
    		mat1[3][2]=0.0;
    		mat1[3][3]=1.0;
    	}break;
    	case 'z':{
    		mat1[0][0]=std::cos(angl);
    		mat1[0][1]=-std::sin(angl);
    		mat1[0][2]=0.0;
    		mat1[0][3]=0.0;
    		mat1[1][0]=std::sin(angl);
    		mat1[1][1]=std::cos(angl);
    		mat1[1][2]=0.0;
    		mat1[1][3]=0.0;
    		mat1[2][0]=0.0;
    		mat1[2][1]=0.0;
    		mat1[2][2]=1.0;
    		mat1[2][3]=0.0;
    		mat1[3][0]=0.0;
    		mat1[3][1]=0.0;
    		mat1[3][2]=0.0;
    		mat1[3][3]=1.0;
    	}break;
    	default:
    	break;
    }

    int i, j, k; 

    for (i = 0; i < 4; i++) 
    { 
        for (j = 0; j < 1; j++) 
        { 
            res[i][j] = 0; 
            for (k = 0; k < 4; k++) 
                res[i][j] += mat1[i][k] *  
                             mat2[k][j]; 
        } 
    } 

    vect[0]=res[0][0];
	vect[1]=res[1][0];
	vect[2]=res[2][0];

    for(int i = 0; i < 4; ++i) {
    	delete [] mat1[i];
    	delete [] mat2[i];
    	delete [] res[i];	
	}
    delete [] mat1;
    delete [] mat2;
    delete [] res;
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
    switch(axis){
      case'x':case'X':{
        artSel = 1*sense;
      }
      break;
      case'y':case'Y':{
        artSel = 2*sense;
      }
      break;
      case'z':case'Z':{
        artSel = 3*sense;
      }
      break;
      default:
      break;
    }
  }else{
    for( Arm* child: m_Children )
      child->moveArt(name, axis, sense);
  }
}
//--------------------------------------------------------------------------
void Arm::drawInOpenGLContext( GLenum mode, bool rotated, float rotAng, char axisRot, float* posAct, 
							int artAct, char axisAct, GLUquadricObj* arti, bool grabbed, 
							float* colorBall, int rBall, GLUquadricObj* ball)
{
  // Save call matrix
  glPushMatrix( );
  
  if(artSel!=0){
    switch(artSel){
      case -3:{
        rotAng=-1.0;
        axisRot = 'z';
      }
        break;
      case -2:{
        rotAng = -1.0;
        axisRot = 'y';
      }
        break;
      case -1:{
        rotAng = -1.0;
        axisRot = 'x';
      }
        break;
      case 1:{
        rotAng = 1.0;
        axisRot = 'x';
      }
        break;
      case 2:{
        rotAng = 1.0;
        axisRot = 'y';
      }
        break;
      case 3:{
        rotAng = 1.0;
        axisRot = 'z';
      }
        break;
      default:
        break;
    }
    rotated = true;   
    artSel = 0;
  }

  if(rotated){
  	switch(axisRot){
  		case'x':{
    		rotVect(posa,'x',rotAng*_PI_180);    		
  		}
  		break;
  		case'y':{
    		rotVect(posa,'y',rotAng*_PI_180);
  		}
  		break;
  		case'z':{	
    		rotVect(posa,'z',rotAng*_PI_180);
  		}
  		break;
  		default:
  		break;
  	}
  }

  posAct[0] += posa[0]; 
  posAct[1] += posa[1]; 
  posAct[2] += posa[2]; 
  	
  if(artAct == m_Name){
  	if(axisAct != ' '){
  		switch(axisAct){
	  		case'x':case'X':{
  				glColor3f(1,0,0);    		
	  		}
	  		break;
	  		case'y':case'Y':{
  				glColor3f(0,1,0);    		
	  		}
	  		break;
	  		case'z':case'Z':{
  				glColor3f(0,0,1);    		
	  		}
	  		break;
	  		default:
	  		break;
  		}
  	}else{
  		glColor3f(1,1,1);
  	}
  		
  }else{	
  	glColor3f(0,0,0);	
  }
  
  glLineWidth(1);

  gluSphere( arti, 2, 10, 10 );

  glPushMatrix( );

	  glLineWidth(8);
	  glColor3f(0.25,0.25,0.25);

	  glBegin(GL_LINES);
	  	glVertex3f(0.0,0.0,0.0);
	  	glVertex3f(posa[0],posa[1],posa[2]);
	  glEnd();

  glPopMatrix( );

  glTranslatef(posa[0],posa[1],posa[2]);

  // Show children
  bool atLeastOneChild = false;
  for( Arm* child: m_Children ){
  	child->drawInOpenGLContext( mode, rotated, rotAng, axisRot, posAct, artAct, axisAct, arti, grabbed,colorBall,rBall,ball);
  	atLeastOneChild = true;
  }

  if(!atLeastOneChild){
  	if(grabbed){
  		glPushMatrix();
	      glColor3f(colorBall[0],colorBall[1],colorBall[2]);
	      glScalef(rBall,rBall,rBall);
	      gluSphere( ball, 1, 50, 50 );
    	glPopMatrix();  
  	}
  }
  
  // Get call matrix
  glPopMatrix( );
}
//--------------------------------------------------------------------------
void Arm::_strIn( std::istream& in )
{
  std::string line;
  float x, y, z;
  std::getline( in, line );
  std::istringstream b( line );
  b >> x >> y >> z;

  posa[0]=x;
  posa[1]=y;
  posa[2]=z;

  rotx[0] = 1.0;
  rotx[1] = 0.0;
  rotx[2] = 0.0;

  roty[0] = 0.0;
  roty[1] = 1.0;
  roty[2] = 0.0;

  rotz[0] = 0.0;
  rotz[1] = 0.0;
  rotz[2] = 1.0;

  if(m_Name >1){
    Arm* child = new Arm( );
    child->setName(m_Name - 1);
    child->_strIn(in);
    addChild( child );
  }
}
//--------------------------------------------------------------------------
