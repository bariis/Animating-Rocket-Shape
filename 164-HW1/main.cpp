

/*********
 CTIS164 - Template Source Program
 ----------
 STUDENT : Hüseyin Baris Ertas
 SECTION :  164-2
 HOMEWORK: FIRSTT HOMEWORK
 ----------
 PROBLEMS:
 ----------
 ADDITIONAL FEATURES:
 When space is clicked rockets get faster and slower.
 All rockets are connected to one point.
 *********/

/*#ifdef __APPLE__
 #include <GLUT/glut.h>
 #else
 #include <GL/glut.h>
 #endif
 #ifdef _MSC_VER
 #define _CRT_SECURE_NO_WARNINGS
 #endif
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>
 #include <stdarg.h>
 #include <time.h>*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>



#define MAX 10


#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT  720

#define TIMER_PERIOD  10 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define MAX 10  // MAXIMUM OBJECT ON THE SCREEN

#define D2R 0.0174532


int i, j;
bool fast = false;
bool showRocket = false;
bool draw = false;
//bool animation = false;
int rocketNumber = 0, animationNumber;

typedef struct{
  bool animation = false;
  int xB, yB;
}draw_t;

draw_t arr[MAX];


/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

int mx, my; // COORDINATES
// to draw circle, center at (x,y)
// radius r
//
void circle( int x, int y, int r )
{
#define PI 3.1415
  float angle ;
  glBegin( GL_POLYGON ) ;
  for ( int i = 0 ; i < 100 ; i++ )
  {
    angle = 2*PI*i/100;
    glVertex2f( x+r*cos(angle), y+r*sin(angle)) ;
  }
  glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
  float angle;
  
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 100; i++)
  {
    angle = 2 * PI*i / 100;
    glVertex2f(x + r*cos(angle), y + r*sin(angle));
  }
  glEnd();
}

void print(int x, int y, const char *string, void *font )
{
  int len, i ;
  
  glRasterPos2f( x, y );
  len = (int) strlen( string );
  for ( i =0; i<len; i++ )
  {
    glutBitmapCharacter( font, string[i]);
  }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string , ...)
{
  va_list ap;
  va_start ( ap, string );
  char str[1024] ;
  vsprintf( str, string, ap ) ;
  va_end(ap) ;
  
  int len, i ;
  glRasterPos2f( x, y );
  len = (int) strlen( str );
  for ( i =0; i<len; i++ )
  {
    glutBitmapCharacter( font, str[i]);
  }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
  va_list ap;
  va_start(ap, string);
  char str[1024];
  vsprintf(str, string, ap);
  va_end(ap);
  glPushMatrix();
  glTranslatef(x, y, 0);
  glScalef(size, size, 1);
  
  int len, i;
  len = (int)strlen(str);
  for (i = 0; i<len; i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
  }
  glPopMatrix();
}




void rocketShape(draw_t rocket[]){
  
  int i;
  
  for(i=0; i<rocketNumber; i++){
    
    
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex2f((*(rocket+i)).xB +-8,(*(rocket+i)).yB + 11);
    glVertex2f((*(rocket+i)).xB+-8,(*(rocket+i)).yB  + -11);
    glVertex2f((*(rocket+i)).xB +10,(*(rocket+i)).yB + 0);
    glEnd();
    
    glColor3f(0.5,0,0.2);
    glRectf((*(rocket+i)).xB+0, (*(rocket+i)).yB + 17, (*(rocket+i)).xB  +130,(*(rocket+i)).yB  + -17);
    
    glBegin(GL_QUADS);
    glColor3f(1,0,0);   glVertex2f((*(rocket+i)).xB +20,(*(rocket+i)).yB+ 17);
    glColor3f(0,1,0); glVertex2f((*(rocket+i)).xB+15,(*(rocket+i)).yB  + 42);
    glColor3f(0,0,1);glVertex2f((*(rocket+i)).xB+30,(*(rocket+i)).yB  + 37);
    glColor3f(0,0,0); glVertex2f((*(rocket+i)).xB+45,(*(rocket+i)).yB+ 17);
    
    glColor3f(1,0,0); glVertex2f((*(rocket+i)).xB +20,(*(rocket+i)).yB + -17);
    glColor3f(0,1,0); glVertex2f((*(rocket+i)).xB +15,(*(rocket+i)).yB  + -42);
    glColor3f(0,0,1); glVertex2f((*(rocket+i)).xB +30,(*(rocket+i)).yB + -37);
    glColor3f(0,0,0); glVertex2f((*(rocket+i)).xB +45,(*(rocket+i)).yB + -17);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(1,1,1);
    glVertex2f((*(rocket+i)).xB +60,(*(rocket+i)).yB + 17);
    glVertex2f((*(rocket+i)).xB +60,(*(rocket+i)).yB  + -17);
    glEnd();
    
    glColor3f(0,1,0);
    
    circle((*(rocket+i)).xB+130,(*(rocket+i)).yB ,17);
    glColor3f(0.5,0,0.2);
    circle((*(rocket+i)).xB,(*(rocket+i)).yB,17);
    glColor3f(1,0,0);
    circle_wire((*(rocket+i)).xB+ 90, (*(rocket+i)).yB, 14);
    
    
    glColor3f( 1, 0, 0 );
    glLineWidth(1);
    glBegin( GL_LINE_STRIP);
    glVertex2f( (*(arr+i)).xB + -17 ,(*(arr+i)).yB + 0);
    glVertex2f( (*(arr+i)).xB + 0,(*(arr+i)).yB+0);
    glVertex2f( (*(arr+i)).xB + 0, (*(arr+i)).yB+ 0);
    glVertex2f( (*(arr+i)).xB + 0, (*(arr+i)).yB+ 0);
    glVertex2f( (*(arr+i)).xB + 0, (*(arr+i)).yB+ 0);
    glVertex2f( (*(arr+i)).xB + 0, (*(arr+i)).yB+ 0);
    glVertex2f( (*(arr+i)).xB + 0, (*(arr+i)).yB+ 0);
    glColor3f(1,1,1) ;
    
    glVertex2f(0, 0) ;
    
    
    glEnd();
    
    
    
    
    
    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    glVertex2f((*(rocket+i)).xB +130,(*(rocket+i)).yB + 18);
    glVertex2f((*(rocket+i)).xB+130,(*(rocket+i)).yB + -18);
    glVertex2f((*(rocket+i)).xB+180,(*(rocket+i)).yB  + 0);
    
    glEnd();
    vprint(arr[i].xB + 87, arr[i].yB -5 ,GLUT_BITMAP_HELVETICA_12,"%d",i+1);
  }
}

void displayBackground(){
  
  glColor3ub(100, 130, 180);
  glColor3f(1,0,0);
  vprint(-40,302,GLUT_BITMAP_8_BY_13,"Baris Ertas");
  vprint(-25,285,GLUT_BITMAP_8_BY_13,"21702126");
  glBegin(GL_LINE_LOOP);
  glColor3f(1,0,0);
  glVertex2f(-47,315);
  glVertex2f(-47,275);
  glVertex2f(60,275);
  glVertex2f(60,315);
  
  glEnd();
}



void display() {
  
  int i =1;
  
  glClearColor( 0, 0 , 0.1, 0);
  glClear( GL_COLOR_BUFFER_BIT );
  
  glColor3ub(100,100,100);
  circle(230,220,100);
  
  
  glColor3ub(0,0,25);
  circle(280,220,70);
  
  displayBackground();
  
  
  
  if(showRocket){
    rocketShape(arr);
    //for(j=0; j<MAX; j++)
    //  vprint(arr[j].xB + 87, arr[j].yB -5 ,GLUT_BITMAP_HELVETICA_12,"%d",j+1);
  }
  
  
  glColor3f(1,0,0);
  
  vprint(486,-303,GLUT_BITMAP_9_BY_15," (%d, %d) ",mx,my);
  
  glFlush();
  
  
  glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y )
{
  // ROCKET GETS FASTER WHEN PRESSED SPACE OR GET BACK TO ITS NORMAL SPEED
  if ( key == ' ' )
    fast = !fast;
  
  // to refresh the window it calls display() function
  glutPostRedisplay() ;
}

void onKeyUp(unsigned char key, int x, int y )
{
  // exit when ESC is pressed.
  if ( key == 27 )
    exit(0);
  
  // to refresh the window it calls display() function
  glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown( int key, int x, int y )
{
  // Write your codes here.
  switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
  }
  
  // to refresh the window it calls display() function
  glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp( int key, int x, int y )
{
  // Write your codes here.
  switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
  }
  
  // to refresh the window it calls display() function
  glutPostRedisplay() ;
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick( int button, int state, int x, int y )
{
  
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    for(i=0; i<MAX; i++){
      if(mx >= arr[i].xB + - 22 && mx <= arr[i].xB + 185 && my <= arr[i].yB + 52 && my >= arr[i].yB + - 52){
        return;
      }
    }
    
    if (rocketNumber < MAX){
      arr[rocketNumber].xB = mx;
      arr[rocketNumber].yB = my;
      j = rocketNumber;
      showRocket = true;
      //for(i=0; i<MAX; i++){
      if(mx < arr[i].xB + -19 && mx > arr[i].xB + 185 && my < arr[i].yB + -55 && my > arr[i].yB + 45){
        //showRocket = true;
      }
      else{
        rocketNumber++;
      }
    }
    
    //}
  }
  
  if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    
    for(i=0; i<MAX; i++){
      if(mx >= arr[i].xB + 0 && mx <= arr[i].xB + 130 && my <= arr[i].yB + 17 && my >= arr[i].yB + - 17){
        arr[i].animation = !arr[i].animation;
        printf("TRUE\n");
      }
    }
    
  }
  
  glutPostRedisplay() ;
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize( int w, int h )
{
  winWidth = w;
  winHeight = h;
  glViewport( 0, 0, w, h ) ;
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( -w/2, w/2, -h/2, h/2, -1, 1);
  glMatrixMode( GL_MODELVIEW);
  glLoadIdentity();
  display(); // refresh window.
}

void onMoveDown( int x, int y ) {
  // Write your codes here.
  // to refresh the window it calls display() function
  glutPostRedisplay() ;
}

void onMove( int x, int y ) {
  
  mx = x - winWidth / 2;
  my = winHeight / 2 - y;
  
  glutPostRedisplay();
}




#if TIMER_ON == 1
void onTimer( int v) {
  
  glutTimerFunc( TIMER_PERIOD, onTimer, 0) ;
  animationNumber= 0;
  
  while(animationNumber<MAX){
    if(arr[animationNumber].animation){
      arr[animationNumber].xB++;
      if(fast)
        arr[animationNumber].xB+=3;
      if(arr[animationNumber].xB >= 640)
        arr[animationNumber].xB -= 1410;
    }
    animationNumber++;
  }
  
  glutPostRedisplay() ;
  
}
#endif

void Init() {
  
  // Smoothing shapes
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
}

int main( int argc, char *argv[] ) {
  
  int number;
  
  glutInit(&argc, argv );
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  //glutInitWindowPosition(100, 100);
  glutCreateWindow("HW-1 ANIMATING ROCKET SHAPE");
  
  glutDisplayFunc(display);
  glutReshapeFunc(onResize);
  
  //
  // keyboard registration
  //
  glutKeyboardFunc(onKeyDown);
  glutSpecialFunc(onSpecialKeyDown);
  
  glutKeyboardUpFunc(onKeyUp);
  glutSpecialUpFunc(onSpecialKeyUp);
  
  //
  
  
  // mouse registration
  //
  glutMouseFunc(onClick);
  glutMotionFunc(onMoveDown);
  glutPassiveMotionFunc(onMove);
  
#if  TIMER_ON == 1
  // timer event
  glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
#endif
  
  Init();
  
  srand(time(0));
  
  glutMainLoop();
}

