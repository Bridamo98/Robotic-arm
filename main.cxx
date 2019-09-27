/* -------------------------------------------------------------------------
 * @brief Simulation of a simple solar system
 * @author Leonardo Flórez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 *g++ -std=c++17 main.cxx -lm -lGL -lGLU -lglut -o yolo
 */

  

#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include "Camera.cxx"
#include "arm.cxx"

#define _G 9.807

// -------------------------------------------------------------------------
Camera myCamera;//esto va
Arm* myStar = nullptr;//cambiar el nombre
GLUquadricObj* myObject = nullptr;
GLUquadricObj* myObject2 = nullptr;
bool articulacionSeleccionada = false;
bool ejeSeleccionado = false;
int artSel;
int artAct = 0;
float* posActualDePunta;
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
Arm* initWorld( int argc, char* argv[] );//esto va
void destroyWorld( Arm* star );//esto va

// -------------------------------------------------------------------------
void displayCbk( );//esto va
void idleCbk( );//esto va
void resizeCbk( int w, int h );//esto va
void keyboardCbk( unsigned char key, int x, int y );//esto va
void mouseClickCbk( int button, int state, int x, int y );//esto va
void mouseMoveCbk( int x, int y );// esto va
std::istringstream readFirstLine(Arm* arm, const std::string& fname);
void drawFloor();
void drawBall();
void grabValidation();
// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  // Init OpenGL context
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1024, 768 );
  glutCreateWindow( "A solar system..." );//cambiar nombre
  glEnable(GL_DEPTH_TEST);//Para permitir efecto de superposición

  // Init world
  try
  {
    myStar = initWorld( argc, argv );// cambiar nombre

    glutDisplayFunc( displayCbk );// esto va
    glutIdleFunc( idleCbk );// esto va
    glutReshapeFunc( resizeCbk );// esto va
    glutKeyboardFunc( keyboardCbk );// esto va
    glutMouseFunc( mouseClickCbk );// esto va
    glutMotionFunc( mouseMoveCbk );// esto va
    glutMainLoop( );// esto va

    destroyWorld( myStar );// esto va
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
  arm->m_Name = name;
  return buffer;
}
void drawBall(){
  if(!grabbed){
    glPushMatrix();
      glColor3f(colorBall[0],colorBall[1],colorBall[2]);
      glTranslatef(ballPos[0],ballPos[1],ballPos[2]);
      glScalef(rBall,rBall,rBall);
      gluSphere( myObject, 1, 50, 50 );
    glPopMatrix();  
  }
}
void drawFloor(){
  glPushMatrix();
  glRotatef(-90,1,0,0);
  glColor3f(0.5,0.5,0.5);
  gluDisk( myObject2, 0, 300, 10, 10 );
  glPopMatrix();
}

void grabValidation(){
  float distance = std::sqrt(((ballPos[0] - posActualDePunta[0])*(ballPos[0] - posActualDePunta[0]))+
                             ((ballPos[1] - posActualDePunta[1])*(ballPos[1] - posActualDePunta[1]))+
                            ((ballPos[2] - posActualDePunta[2])*(ballPos[2] - posActualDePunta[2])));

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
Arm* initWorld( int argc, char* argv[] )//cambiar tipo de retorno y función
{
  // Initialize camera//cambiar--Listo
  myCamera.setFOV( 45 );
  myCamera.setPlanes( 1e-2, 100000 );
  myCamera.move( Vector( 0, 40, 150 ) );
  //myCamera.rotY(90);
  //myCamera.rotZ(90);
  


  // OpenGL initialization
  glClearColor( 0.75, 0.75, 0.75, 0 );

  // Check input arguments
  if( argc < 2 )
    throw std::runtime_error(
      std::string( "Usage: " ) + argv[ 0 ] + " world_description"
      );

  // Read world and keep the star of this solar system
  Arm* arm = new Arm();
  std::istringstream buffer = readFirstLine(arm, argv[ 1 ]);
  arm->_strIn(buffer);
  myObject = gluNewQuadric( );
  gluQuadricDrawStyle( myObject, GLU_LINE );
  myObject2 = gluNewQuadric( );
  gluQuadricDrawStyle( myObject2, GLU_FILL);

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

  if( myObject != nullptr )
    gluDeleteQuadric( myObject );
  myObject = nullptr;

  if( myObject2 != nullptr )
    gluDeleteQuadric( myObject2 );
  myObject2 = nullptr;

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

  posActualDePunta = new float[3];
  

  posActualDePunta[0] = 0.0;
  posActualDePunta[1] = 0.0;
  posActualDePunta[2] = 0.0;
  // Draw the scene
  drawFloor();
  if(moving){
    t = std::chrono::duration_cast< std::chrono::microseconds >(
        std::chrono::high_resolution_clock::now( ) - starMoving
        ).count( )/1000000.0;
    std::cout<<"tiempo transcurrido "<< t <<std::endl;

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
  myStar->drawBase();

  myStar->drawInOpenGLContext( GL_LINE_LOOP, false ,0.0,' ',
  /*IMPORTANTE*/posActualDePunta, /*PARA DIFERENCIARLA DE LAS DEMÁS*/artAct, /*CREO QUE NO SE NECESITA*/ axisAct, myObject2, grabbed
    ,colorBall,rBall,myObject);

  if(grabbed){
    ballPos[0] = posActualDePunta[0];
    ballPos[1] = posActualDePunta[1];
    ballPos[2] = posActualDePunta[2];
  }

  grabValidation();

  std::cout<<"Pos actual de bola "<<ballPos[0]<<" "<<ballPos[1]<<" "<< ballPos[2]<<std::endl;
  std::cout<<"Pos actual de punta "<<posActualDePunta[0]<<" "<<posActualDePunta[1]<<" "<< posActualDePunta[2]<<std::endl;

  delete posActualDePunta;

  //delete ballPos;

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
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=1;
      artAct=1;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '2':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=2;
      artSel=2;
      std::cout<<"entra "<<key<<std::endl;
    } 
  }
    break;
  case '3':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=3;
      artSel=3;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '4':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=4;
      artSel=4;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '5':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=5;
      artSel=5;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '6':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=6;
      artSel=6;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '7':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=7;
      artSel=7;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '8':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=8;
      artSel=8;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '9':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artAct=9;
      artSel=9;

      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
    case 'p': case 'P':
  {
    if(grabbed){//CASO DE BORRAR LA ESFERA DEL ULTIMO HIJO Y COMENZAR CON LA CAIDA LIBRE
      moving = true;
      falling = true;
      yi = ballPos[1];
      std::cout<<"yi en evento "<<yi<<std::endl;
      vi = 0; 
      grabbed = false;
      starMoving = std::chrono::high_resolution_clock::now( );
      //std::cout<<"entra a soltar"<<std::endl;
    }else if (near){//CASO DE BORRAR ESFERA DE ESTE ARCHIVO Y PINTARLA EN EL ÚLTIMO HIJO
      grabbed = true;
    }
  }
    break;
  case '-':
  {
    if(ejeSeleccionado){
      myStar->moveArt(artSel, axis, -1);
      std::cout<<"entra "<<key<<std::endl;
      artAct = artSel;
      
    }
  }
    break;
  case '+':
  {
    if(ejeSeleccionado){
      myStar->moveArt(artSel, axis, 1);
      std::cout<<"entra "<<key<<std::endl;
      artAct = artSel;
    } 
  }
    break;
  case 'q':case 'Q':
  {
    articulacionSeleccionada = false;
    ejeSeleccionado = false;
    artAct = 0;
    axisAct = ' ';
    std::cout<<"entra "<<key<<std::endl;
  }
    break;
  case 'x':case 'X':case 'y':case 'Y':case 'z':case 'Z':
  {
    if(articulacionSeleccionada && !ejeSeleccionado){
      axis = key;
      axisAct = axis;
      ejeSeleccionado = true;
      std::cout<<"entra "<<key<<std::endl;
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
    
  /* TODO
   void KeyDown(unsigned char key, int x, int y)
   {
   switch (key) 
   {
   case 27:             //ESC
   // PostQuitMessage(0);
   break;
   case 'a':            
   Camera.RotateY(5.0);
   Display();
   break;
   case 'd':               
   Camera.RotateY(-5.0);
   Display();
   break;
   case 'w':               
   Camera.MoveForward( -0.1 ) ;
   Display();
   break;
   case 's':               
   Camera.MoveForward( 0.1 ) ;
   Display();
   break;
   case 'x':               
   Camera.RotateX(5.0);
   Display();
   break;
   case 'y':               
   Camera.RotateX(-5.0);
   Display();
   break;
   case 'c':               
   Camera.StrafeRight(-0.1);
   Display();
   break;
   case 'v':               
   Camera.StrafeRight(0.1);
   Display();
   break;
   case 'f':
   Camera.MoveUpward(-0.3);
   Display();
   break;
   case 'r':
   Camera.MoveUpward(0.3);
   Display();
   break;

   case 'm':
   Camera.RotateZ(-5.0);
   Display();
   break;
   case 'n':
   Camera.RotateZ(5.0);
   Display();
   break;

   }
   }
*/
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

// eof - SolarSystem.cxx
