/* -------------------------------------------------------------------------
 * @brief Simulation of a simple solar system
 * @author Leonardo Flórez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <iostream>

#include "Camera.h"
#include "SpatialObject.h"

// -------------------------------------------------------------------------
Camera myCamera;//esto va
SpatialObject* myStar = nullptr;//cambiar el nombre
bool articulacionSeleccionada = false;
bool ejeSeleccionado = false;
int artSel;
unsigned char axis;

// -------------------------------------------------------------------------
SpatialObject* initWorld( int argc, char* argv[] );//esto va
void destroyWorld( SpatialObject* star );//esto va

// -------------------------------------------------------------------------
void displayCbk( );//esto va
void idleCbk( );//esto va
void resizeCbk( int w, int h );//esto va
void keyboardCbk( unsigned char key, int x, int y );//esto va
void mouseClickCbk( int button, int state, int x, int y );//esto va
void mouseMoveCbk( int x, int y );// esto va

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

// -------------------------------------------------------------------------
SpatialObject* initWorld( int argc, char* argv[] )//cambiar tipo de retorno y función
{
  // Initialize camera//cambiar--Listo
  myCamera.setFOV( 45 );
  myCamera.setPlanes( 1e-2, 100000 );
  myCamera.move( Vector( 0, 0, 30 ) );
  //myCamera.rotY(90);
  //myCamera.rotZ(90);
  


  // OpenGL initialization
  glClearColor( 0, 0, 0, 0 );

  // Check input arguments
  if( argc < 2 )
    throw std::runtime_error(
      std::string( "Usage: " ) + argv[ 0 ] + " world_description"
      );

  // Read world and keep the star of this solar system
  return( new SpatialObject( argv[ 1 ] ) );
}

// -------------------------------------------------------------------------
void destroyWorld( SpatialObject* star )
{
  if( star != nullptr )
    delete star;
}

// -------------------------------------------------------------------------
void displayCbk( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  // Prepare model matrix
  myCamera.loadCameraMatrix( );

  // Draw the scene
  myStar->drawInOpenGLContext( GL_LINE_LOOP );

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
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '2':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=2;
      std::cout<<"entra "<<key<<std::endl;
    } 
  }
    break;
  case '3':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=3;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '4':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=4;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '5':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=5;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '6':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=6;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '7':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=7;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '8':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=8;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '9':
  {
    if(!articulacionSeleccionada){
      articulacionSeleccionada = true;
      artSel=9;
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
    case 'p': case 'P':
  {
    //agarrar bola
  }
    break;
  case '-':
  {
    if(ejeSeleccionado){
      myStar->moveArt(artSel, axis, -1);
      std::cout<<"entra "<<key<<std::endl;
    }
  }
    break;
  case '+':
  {
    if(ejeSeleccionado){
      myStar->moveArt(artSel, axis, 1);
      std::cout<<"entra "<<key<<std::endl;
    } 
  }
    break;
  case 'q':case 'Q':
  {
    articulacionSeleccionada = false;
    ejeSeleccionado = false;
    std::cout<<"entra "<<key<<std::endl;
  }
    break;
  case 'x':case 'X':case 'y':case 'Y':case 'z':case 'Z':
  {
    if(articulacionSeleccionada && !ejeSeleccionado){
      axis = key;
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
