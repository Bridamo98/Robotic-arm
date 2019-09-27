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
	  float*	   rotx;
	  float*	   roty;
	  float*	   rotz;
	  float*	   color;
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
  	void drawInOpenGLContext( GLenum mode, bool rotated, float rotAng, char axisRot,float* posAct, int artAct, char axisAct);
  	void _strIn( std::istream& in );
  	//Mesh* getMesh( );
//Mesh* getMesh2( );
void addChild( Arm* o );
void setName(int name);
unsigned long getNumberOfChildren( );
Arm* getChild( unsigned long i );
int& getName( );
void moveArt(int name, unsigned char axis, int sense);
void rotVect	(float* vect,char axis,float angl);
void drawBase( );
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
	rotx = new float[3];
	roty = new float[3];
	rotz = new float[3];
	color = new float[3];
	artSel = 0;
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
//--------------------------------------------------------------------------
void Arm::drawBase( )
{
  glLineWidth(1);
  glBegin( GL_LINES );
  {
    glColor3f( 1, 0, 0 );
    glVertex3f(  0, 0, 0 );
    glVertex3f( rotx[0]*1000, rotx[1]*1000, rotx[2]*1000 );

    glColor3f( 0, 1, 0 );
    glVertex3f( 0,  0, 0 );
    glVertex3f( roty[0]*1000, roty[1]*1000, roty[2]*1000 );

    glColor3f( 0, 0, 1 );
    glVertex3f( 0, 0,  0 );
    glVertex3f( rotz[0]*1000, rotz[1]*1000, rotz[2]*1000);
  }
  glEnd( );
}
void Arm::rotVect	(
			  //int mat1[4][4],  
              //int mat2[4][1],  
              //int res[4][1]
				float* vect,
				char axis,
				float angl
              ) 
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

    std::cout<<"mat1----------------------"<<std::endl;
    for (i = 0; i < 4; i++) 
    { 
        for (j = 0; j < 4; j++) 
        	std::cout << mat1[i][j] << " "; 
        std::cout << "\n"; 
    }
    std::cout<<"mat2----------------------"<<std::endl;
    for (i = 0; i < 4; i++) 
    { 
        for (j = 0; j < 1; j++) 
        	std::cout << mat2[i][j] << " "; 
        std::cout << "\n"; 
    }


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

    std::cout<<"res----------------------"<<std::endl;
    for (i = 0; i < 4; i++) 
    { 
        for (j = 0; j < 1; j++) 
        	std::cout << res[i][j] << " "; 
        std::cout << "\n"; 
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



void Arm::drawInOpenGLContext( GLenum mode, bool rotated, float rotAng, char axisRot, float* posAct, int artAct, char axisAct/*esto no sirve*/)
{
 
  // Save call matrix
  glPushMatrix( );
  
  if(artSel!=0){
    switch(artSel){
      case -3:{
        //d[2] = d[2]-1.0;
        //_theta += 1.0;
        rotAng=-1.0;
        axisRot = 'z';
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -2:{
        //d[1] = d[1] -1.0;
        //_phi -=1.0;
        rotAng = -1.0;
        axisRot = 'y';
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case -1:{
        //d[0] = d[0]-1.0;
        //_theta -= 1.0;
        rotAng = -1.0;
        axisRot = 'x';
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      case 1:{
        //d[0] = d[0]+1.0;
        //_theta += 1.0;
        rotAng = 1.0;
        axisRot = 'x';
        std::cout<<"-------"<<artSel<<std::endl;

      }
        break;
      case 2:{
        //d[1] = d[1]+1.0;
        //_phi += 1.0;
        rotAng = 1.0;
        axisRot = 'y';
        std::cout<<"-------"<<artSel<<std::endl;

      }
        break;
      case 3:{
        //d[2] = d[2]+1.0;
        //_theta -= 1.0;
        rotAng = 1.0;
        axisRot = 'z';
        std::cout<<"-------"<<artSel<<std::endl;
      }
        break;
      default:
        std::cout<<"default"<<std::endl;
        break;
    }
    rotated = true;   
    artSel = 0;
  }


  //rotPad[0] += d[0];
  //rotPad[1] += d[1];
  //rotPad[2] += d[2];
  

  	//glRotatef(d[2],rotz[0],rotz[1],rotz[2]);
  	//glRotatef(d[1],roty[0],roty[1],roty[2]);
  	//glRotatef(d[0],rotx[0],rotx[1],rotx[2]);



  //posa[0] = r * std::sin(_theta) * std::sin(_phi);//REVISAR...
  //posa[1] = r * std::cos(_theta);//REVISAR...
  //posa[2] = r * std::sin(_theta) * std::cos(_phi);//REVISAR...



  if(rotated){
  	switch(axisRot){
  		case'x':{
    		//rotVect(roty,'x',-rotAng*_PI_180);
    		//rotVect(rotz,'x',-rotAng*_PI_180);
    		rotVect(posa,'x',rotAng*_PI_180);    		
  		}
  		break;
  		case'y':{
		  	//rotVect(rotx,'y',-rotAng*_PI_180);
    		//rotVect(rotz,'y',-rotAng*_PI_180);
    		rotVect(posa,'y',rotAng*_PI_180);

  		}
  		break;
  		case'z':{
  			//rotVect(rotx,'z',-rotAng*_PI_180);
    		//rotVect(roty,'z',-rotAng*_PI_180);	
    		rotVect(posa,'z',rotAng*_PI_180);

  		}
  		break;
  		default:
  		break;
  	}
    //std::cout<<"Luego de rotación(x): "<<rotx[0]<<" "<<rotx[1]<<" "<<rotx[2]<<std::endl;
    //std::cout<<"Luego de rotación(y): "<<roty[0]<<" "<<roty[1]<<" "<<roty[2]<<std::endl;
    //std::cout<<"Luego de rotación(z): "<<rotz[0]<<" "<<rotz[1]<<" "<<rotz[2]<<std::endl;
	//std::cout<<"pos acumnulada en "<<m_Name<<" = "<<posa[0] << " "<<posa[1] <<" "<<posa[2]<<std::endl;

  }

  posAct[0] += posa[0]; 
  posAct[1] += posa[1]; 
  posAct[2] += posa[2]; 

  	
  if(artAct == m_Name){//PARA VISUALIZAR QUE ARTICULACIÓN SE TIENE SELECCIONADA Y CUAL DE LOS EJES
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

  glutWireSphere( 2, 10, 10 );//..............................................ESFERA......................................

  glPushMatrix( );
  //glRotatef(rotPad[2],rotz[0],rotz[1],rotz[2]);
  //glRotatef(rotPad[1],roty[0],roty[1],roty[2]);
  //glRotatef(rotPad[0],rotx[0],rotx[1],rotx[2]);

  //glRotatef(d[2],rotz[0],rotz[1],rotz[2]);
  //glRotatef(d[1],roty[0],roty[1],roty[2]);
  //glRotatef(d[0],rotx[0],rotx[1],rotx[2]);
  //glRotatef(ang[1],0,1,0);
  //glRotatef(ang[0],1,0,0);
  //glColor3f(1,1,0);
  //glTranslatef(0,r/2.0,0);
  //glScalef( 1, r, 1 );
  //glutWireCube(1);//cubo de tamaño 1...................................................................
  glLineWidth(5);

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
  	child->drawInOpenGLContext( mode, rotated, rotAng, axisRot, posAct, artAct, axisAct);
  	atLeastOneChild = true;
  }
    

  if(atLeastOneChild && rotated){
  	//posa[0] = posa[0] + m_Children[0]->posa[0];
	//posa[1] = posa[1] + m_Children[0]->posa[1];
	//posa[2] = posa[2] + m_Children[0]->posa[2];


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
  //std::cout<<"1"<<std::endl;

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

  rotx[0] = 1.0;
  rotx[1] = 0.0;
  rotx[2] = 0.0;

  roty[0] = 0.0;
  roty[1] = 1.0;
  roty[2] = 0.0;

  rotz[0] = 0.0;
  rotz[1] = 0.0;
  rotz[2] = 1.0;

  ///ASIGNAR VALORES AL VECTOR rotAng PARA PASARSELO AL HIJO
  //ang[2] = -theta*_180_PI;//Angulo en z, por el momento no se necesita.

  std::cout<<ang[0]<<" "<<ang[1]<<std::endl;

  if(m_Name >1){
    //std::cout<<"1"<<std::endl;
    Arm* child = new Arm( );
    //std::cout<<"1"<<std::endl;
    child->setName(m_Name - 1);
    //std::cout<<"1"<<std::endl;
    child->_strIn(in);
    //std::cout<<"1"<<std::endl;
    addChild( child );
    //std::cout<<"1"<<std::endl;
  }
}