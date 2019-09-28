/* 
 *g++ -std=c++17 main.cxx -lm -lGL -lGLU -lglut -o ejecutable
 */

  

#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include "Camera.cxx"
#include "arm.cxx"

#define _G 9.807

// -------------------------------------------------------------------------
Camera myCamera;
Arm* myArm = nullptr;
GLUquadricObj* lineObject = nullptr;
GLUquadricObj* fillObject = nullptr;
bool artSelected = false;
bool axisSelected = false;
int artSel;
int artAct = 0;
float* endArmPosition;
float* ballPos;
int rBall = 2.5; 
float* colorBall;
unsigned char axis;
unsigned char axisAct = ' ';
bool near = false;
bool grabbed = false;
bool moving = false;
bool falling = false;
float yi;
float vi;
float yt;
float vt;
std::chrono::time_point< std::chrono::high_resolution_clock > starMoving;
double t;
// -------------------------------------------------------------------------
Arm* initWorld( int argc, char* argv[] );
void destroyWorld( Arm* star );

// -------------------------------------------------------------------------
void displayCbk( );
void idleCbk( );
void resizeCbk( int w, int h );
void keyboardCbk( unsigned char key, int x, int y );
void mouseClickCbk( int button, int state, int x, int y );
void mouseMoveCbk( int x, int y );
std::istringstream readFirstLine(Arm* arm, const std::string& fname);
void drawFloor();
void drawBall();
void grabValidation();
// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  // Init OpenGL context
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1024, 768 );
  glutCreateWindow( "Brazo" );
  glEnable(GL_DEPTH_TEST);//Para permitir efecto de superposición

  // Init world
  try
  {
    myArm = initWorld( argc, argv );

    glutDisplayFunc( displayCbk );
    glutIdleFunc( idleCbk );
    glutReshapeFunc( resizeCbk );
    glutKeyboardFunc( keyboardCbk );
    glutMouseFunc( mouseClickCbk );
    glutMotionFunc( mouseMoveCbk );
    glutMainLoop( );

    destroyWorld( myArm );
    return( 0 );
  }
  catch( std::exception& err )
  {
    std::cerr << err.what( ) << std::endl;
    return( 1 );
  } // end if
}
std::istringstream readFirstLine(Arm* arm, const std::string& fname ){
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
  arm->m_Name = name;
  return buffer;
}
void drawBall(){
  if(!grabbed){
    glPushMatrix();
      glColor3f(colorBall[0],colorBall[1],colorBall[2]);
      glTranslatef(ballPos[0],ballPos[1],ballPos[2]);
      glScalef(rBall,rBall,rBall);
      gluSphere( lineObject, 1, 50, 50 );
    glPopMatrix();  
  }
}
void drawFloor(){
  glPushMatrix();
  glTranslatef(0,-2,0);
  glScalef(1,4,1);
  glRotatef(-90,1,0,0);
  glColor3f(0.5,0.5,0.5);
  gluDisk( fillObject, 0, 300, 10, 10 );
  glPopMatrix();
}

void grabValidation(){
  float distance = std::sqrt(((ballPos[0] - endArmPosition[0])*(ballPos[0] - endArmPosition[0]))+
                             ((ballPos[1] - endArmPosition[1])*(ballPos[1] - endArmPosition[1]))+
                            ((ballPos[2] - endArmPosition[2])*(ballPos[2] - endArmPosition[2])));

  if(distance < rBall && !grabbed){
    colorBall[0] = 1.0;
    colorBall[1] = 1.0;
    colorBall[2] = 1.0;
    near = true;
  }else{
    colorBall[0] = 1.0;
    colorBall[1] = 1.0;
    colorBall[2] = 0.0;
    near = false;
  }

}

// -------------------------------------------------------------------------
Arm* initWorld( int argc, char* argv[] )
{
  // Initialize camera//
  myCamera.setFOV( 45 );
  myCamera.setPlanes( 1e-2, 100000 );
  myCamera.move( Vector( 0, 40, 150 ) );
  
  


  // OpenGL initialization
  glClearColor( 0.75, 0.75, 0.75, 0 );

  // Check input arguments
  if( argc < 2 )
    throw std::runtime_error(
      std::string( "Usage: " ) + argv[ 0 ] + " world_description"
      );

  
  Arm* arm = new Arm();
  std::istringstream buffer = readFirstLine(arm, argv[ 1 ]);
  arm->_strIn(buffer);
  lineObject = gluNewQuadric( );
  gluQuadricDrawStyle( lineObject, GLU_LINE );
  fillObject = gluNewQuadric( );
  gluQuadricDrawStyle( fillObject, GLU_FILL);

  ballPos = new float[3];
  ballPos[0] = 70.0; 
  ballPos[1] = rBall; 
  ballPos[2] = 0.0;

  colorBall = new float[3];

  colorBall[0] = 1.0;
  colorBall[1] = 1.0;
  colorBall[2] = 0.0;
  return( arm );
}

// -------------------------------------------------------------------------
void destroyWorld( Arm* star )
{
  if( star != nullptr )
    delete star;

  if( lineObject != nullptr )
    gluDeleteQuadric( lineObject );
  lineObject = nullptr;

  if( fillObject != nullptr )
    gluDeleteQuadric( fillObject );
  fillObject = nullptr;

  delete ballPos;
}

// -------------------------------------------------------------------------
void displayCbk( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  // Prepare model matrix
  myCamera.loadCameraMatrix( );

  endArmPosition = new float[3];
  

  endArmPosition[0] = 0.0;
  endArmPosition[1] = 0.0;
  endArmPosition[2] = 0.0;
  // Draw the scene
  drawFloor();
  if(moving){
    t = std::chrono::duration_cast< std::chrono::microseconds >(
        std::chrono::high_resolution_clock::now( ) - starMoving
        ).count( )/1000000.0;

    if(falling){
      yt = yi - 0.5*_G*(t*t);
      ballPos[1] = yt;
      if(yt <= rBall){
        vi = _G*t*0.8;
        starMoving = std::chrono::high_resolution_clock::now( );
        falling = false;
      }
    }else{
      yt = vi*t-0.5*_G*(t*t);
      vt = vi -_G*t;
      ballPos[1] = yt;
      if(vt <= 0.0){
        yi = yt;
        starMoving = std::chrono::high_resolution_clock::now( );
        falling = true;
        if(yt <= rBall){
          moving = false;
          falling = false;
        }
      }
    }
  }
  drawBall();
  myArm->drawBase();

  myArm->drawInOpenGLContext( GL_LINE_LOOP, false ,0.0,' ',
  endArmPosition, artAct,  axisAct, fillObject, grabbed
    ,colorBall,rBall,lineObject);

  if(grabbed){
    ballPos[0] = endArmPosition[0];
    ballPos[1] = endArmPosition[1];
    ballPos[2] = endArmPosition[2];
  }

  grabValidation();

  delete endArmPosition;

  // Finish
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
void idleCbk( )
{
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void resizeCbk( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  myCamera.setWindow( w, h );
  myCamera.loadProjectionMatrix( );
}
//--------------------------------------------------------------------------
void SpecialKeyboardCbk( int key, int x, int y ) // id tecla especial, GLUT_F1 GLUT_UP, etc -
{

  
}
// -------------------------------------------------------------------------
void keyboardCbk( unsigned char key, int x, int y )
{
  switch( key ) 
  {
  case 'w': case 'W':
  {
    myCamera.forward( 10 ) ;
  }
    break;
  case 's': case 'S':
  {
    myCamera.forward( -10 ) ;
  }
    break;
  case 'a': case 'A':
  {
    myCamera.strafe( -10 ) ;
  }
    break;
  case 'd': case 'D':
  {
    myCamera.strafe( 10 ) ;
  }
    break;
  case '1':
  {
    if(!artSelected){
      artSelected = true;
      artSel=1;
      artAct=1;
    }
  }
    break;
  case '2':
  {
    if(!artSelected){
      artSelected = true;
      artAct=2;
      artSel=2;
    } 
  }
    break;
  case '3':
  {
    if(!artSelected){
      artSelected = true;
      artAct=3;
      artSel=3;
    }
  }
    break;
  case '4':
  {
    if(!artSelected){
      artSelected = true;
      artAct=4;
      artSel=4;
    }
  }
    break;
  case '5':
  {
    if(!artSelected){
      artSelected = true;
      artAct=5;
      artSel=5;
    }
  }
    break;
  case '6':
  {
    if(!artSelected){
      artSelected = true;
      artAct=6;
      artSel=6;
    }
  }
    break;
  case '7':
  {
    if(!artSelected){
      artSelected = true;
      artAct=7;
      artSel=7;
    }
  }
    break;
  case '8':
  {
    if(!artSelected){
      artSelected = true;
      artAct=8;
      artSel=8;
    }
  }
    break;
  case '9':
  {
    if(!artSelected){
      artSelected = true;
      artAct=9;
      artSel=9;
    }
  }
    break;
    case 'p': case 'P':
  {
    if(grabbed){
      moving = true;
      falling = true;
      yi = ballPos[1];
      vi = 0; 
      grabbed = false;
      starMoving = std::chrono::high_resolution_clock::now( );
    }else if (near){
      grabbed = true;
    }
  }
    break;
  case '-':
  {
    if(axisSelected){
      myArm->moveArt(artSel, axis, -1);
      artAct = artSel;
    }
  }
    break;
  case '+':
  {
    if(axisSelected){
      myArm->moveArt(artSel, axis, 1);
      artAct = artSel;
    } 
  }
    break;
  case 'q':case 'Q':
  {
    artSelected = false;
    axisSelected = false;
    artAct = 0;
    axisAct = ' ';
  }
    break;
  case 'x':case 'X':case 'y':case 'Y':case 'z':case 'Z':
  {
    if(artSelected && !axisSelected){
      axis = key;
      axisAct = axis;
      axisSelected = true;
    }
  }
    break;
  case 27: // ESC
    std::exit( 0 );
    break;
  default:
    break;
  } // end switch
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void mouseClickCbk( int button, int state, int x, int y )
{
  if( state == GLUT_DOWN )
    myCamera.setReference( x, y );
  else
    myCamera.setReference( 0, 0 );
}

// -------------------------------------------------------------------------
void mouseMoveCbk( int x, int y )
{
  int dx, dy;
  myCamera.getReference( dx, dy, x, y );
  myCamera.setReference( x, y );

  // Apply rotations
  if( dx > 0 )      myCamera.rotY( -0.5 );
  else if( dx < 0 ) myCamera.rotY( 0.5 );
  if( dy > 0 )      myCamera.rotX( 0.5 );
  else if( dy < 0 ) myCamera.rotX( -0.5 );

  // Redraw
  glutPostRedisplay( );
}
