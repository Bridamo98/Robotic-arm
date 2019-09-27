/* -------------------------------------------------------------------------
 * @brief Simulation of a simple solar system
 * @author Leonardo Flórez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 *g++ -std=c++17 main.cxx -lm -lGL -lGLU -lglut -o yolo
 */

  

#include <GL/glut.h>
#include <iostream>

#include "Camera.cxx"
#include "arm.cxx"

// -------------------------------------------------------------------------
Camera myCamera;//esto va
Arm* myStar = nullptr;//cambiar el nombre
bool articulacionSeleccionada = false;
bool ejeSeleccionado = false;
int artSel;
int artAct = 0;
float* posActualDePunta;
float* rotPad;
unsigned char axis;
unsigned char axisAct = ' ';


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
// -------------------------------------------------------------------------
Arm* initWorld( int argc, char* argv[] )//cambiar tipo de retorno y función
{
  // Initialize camera//cambiar--Listo
  myCamera.setFOV( 45 );
  myCamera.setPlanes( 1e-2, 100000 );
  myCamera.move( Vector( 50, 0, 0 ) );
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
  return( arm );
}

// -------------------------------------------------------------------------
void destroyWorld( Arm* star )
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

  posActualDePunta = new float[3];
  rotPad = new float[3];

  posActualDePunta[0] = 0.0;
  posActualDePunta[1] = 0.0;
  posActualDePunta[2] = 0.0;

  rotPad[0] = 0.0;
  rotPad[1] = 0.0;
  rotPad[2] = 0.0;
  // Draw the scene
  myStar->drawBase();

  myStar->drawInOpenGLContext( GL_LINE_LOOP, false ,0.0,' ',
  /*IMPORTANTE*/posActualDePunta, /*PARA DIFERENCIARLA DE LAS DEMÁS*/artAct, /*CREO QUE NO SE NECESITA*/ axisAct);

  std::cout<<"Pos actual de punta "<<posActualDePunta[0]<<" "<<posActualDePunta[1]<<" "<< posActualDePunta[2]<<std::endl;

  delete posActualDePunta;

  delete rotPad;

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
    //agarrar bola
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
