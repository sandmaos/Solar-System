#include <windows.h>
#include <GL/glu.h>
#include <QGLWidget>
#include <QSlider>
#include <cmath>
#include <iostream>
#include "HierarchyWidget.h"
#include "SOIL2/SOIL2.h"
using namespace std;

double SUN_R    = 3;

float star[1000][3];


const int img_num = 8;
GLuint textures[img_num];
typedef struct texture_data {
    unsigned char* data;
    int width, height;
} texture_data;

texture_data load_texture2(char *path)
{
    texture_data t;
    //unsigned char* image;
    int width, height;
    t.data = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
    t.width = width;
    t.height = height;
    //SOIL_free_image_data(image);
    return t;
}


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

typedef struct materialStruct2 {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat emission[4];
  GLfloat shininess;
} materialStruct2;

static materialStruct2 sunMaterials = {
  { 6.0,0.0,0.0,1.0},
  { 1.0f, 0.5f, 0.31f,1.0},
  { 0.5f, 0.5f, 0.5f, 1.0},
    { 1, 1, 1, 0.0f },
  0.0
};

static materialStruct2 starMaterials = {
  {  1.0f, 1.0f, 1.0f, 1.0f},
  { 1.0f, 1.0f, 1.0f, 1.0f},
  { 0.8f, 0.8f, 0.8f, 0.2f },
  {  0.f, 0.f, 0.f, 1.0f},
  27.8 
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  3.0
};

static materialStruct2 orbitMaterials = {
  { 0.0, 0.0, 0.0, 0.0},
  { 0.0, 0.0, 0.0, 0.0},
  { 0.0, 0.0, 0.0, 0.0},
    {  0.2f, 0.2f, 0.2f, 1.0f},
  68.0
};

static materialStruct2 beltMaterials = {
  { 0.0, 0.0, 0.0, 0.0},
  { 0.0, 0.0, 0.0, 0.0},
  { 0.0, 0.0, 0.0, 0.0},
    {  1.8f, 1.8f, 1.8f, 1.0f},
  1.0
};


//void init_stars()
//{
//    for (int i = 0; i < 1000; i++)
//        for (int j = 0; j < 3; j++)
//            star[i][j] = rand() % 20 - 10;
//}
//void stars()
//{
//    glBegin(GL_POINTS);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    for (int i = 0; i < 1000; ++i) {
//        glVertex3f(star[i][0], star[i][1], star[i][2]);
//    }
//    glEnd();
//}


void img(){
    texture_data TextureImage[img_num];
    memset(TextureImage, 0, sizeof(void *) * img_num);
        TextureImage[0] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/sun.jpg");
        TextureImage[1] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/mercury.jpg");
        TextureImage[2] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/earth.jpg");
        TextureImage[3] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/moon.jpg");
        TextureImage[4] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/jupiter.jpg");
        TextureImage[5] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/venus.jpg");
        TextureImage[6] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/mars.jpg");
        TextureImage[7] = load_texture2("C:/Users/dell/Desktop/solar/hierarchy/saturn.jpg");
        glGenTextures(img_num, &textures[0]);
            for (int i = 0; i < img_num; i++)
            {
                glBindTexture(GL_TEXTURE_2D, textures[i]);
                glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i].width, TextureImage[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i].data);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            for (int i = 0; i < img_num; i++)
                SOIL_free_image_data(TextureImage[i].data);
}

// constructor
HierarchyWidget::HierarchyWidget(QWidget *parent)
  : QGLWidget(parent),
    angle(0),
    spot(1),
    WIN_SIZE(9),
    scale(0)
    {
      ball = gluNewQuadric();
	} // constructor

// called when OpenGL context is set up
void HierarchyWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
    glClearColor(0., 0., 0., 0.0);

    img();
 	} // initializeGL()

HierarchyWidget::~HierarchyWidget()
{
  gluDeleteQuadric(ball);
}


void HierarchyWidget::line(float dis){
    int n=300;
    float PI=3.1415926f;
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++)
    {
        glVertex3f(dis*cos(2*PI*i/n), 0.0f, dis*sin(2*PI*i/n));
    }
    glEnd();
}


void HierarchyWidget::updateAngle(){
  angle += 1+scale/10;
  this->repaint();
}

void HierarchyWidget::updateScale(int i){
    scale=i;
    cout << "Value of scale is : " << i << endl;
}


void HierarchyWidget::updateSpot(int i){
  // find out about the object that sent
  spot = i;
  cout << "Value of spot is : " << spot << endl;
  this->repaint();
}


void HierarchyWidget::updateSize(int i){
  // find out about the object that sent
  WIN_SIZE = i;
  cout << "Value of size is : " << WIN_SIZE << endl;
  this->repaint();
}



// called every time the window is resized
void HierarchyWidget::resizeGL(int w, int h)
    { // resizeGL()
    // set the viewport to the entire widget
    glViewport(0, 0, w, h);
    GLfloat light_pos[] = {0., 0.0, 1., 1.};

    glEnable(GL_LIGHTING); // enable lighting in general
    glEnable(GL_LIGHT0);   // each light source must also be enabled

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    materialStruct2* p_front = &starMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,500.);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1*WIN_SIZE, WIN_SIZE, -1*WIN_SIZE, WIN_SIZE, -1*WIN_SIZE, WIN_SIZE);

    } // resizeGL()

void HierarchyWidget::sun(){
  gluSphere(ball,1.2,100,100);
}

void HierarchyWidget::meteorite(){
   gluSphere(ball,0.01,10,10);
}
void HierarchyWidget::meteorite2(){
   gluSphere(ball,0.035,10,10);
}

void HierarchyWidget::moon(){
  gluSphere(ball,0.15, 32, 32);
}	

void HierarchyWidget::mercury(){
 gluSphere(ball,0.2, 32, 32);
}

void HierarchyWidget::jupiter(){
  gluSphere(ball,0.7, 70, 70);
}

void HierarchyWidget::saturn(){
  gluSphere(ball,0.5, 70, 70);
}


void HierarchyWidget::earth(){
  gluSphere(ball,0.3, 32, 32);
}


// called every time the widget needs painting
void HierarchyWidget::paintGL()
	{ // paintGL()
    // clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      	glShadeModel(GL_SMOOTH);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
      	glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result

        materialStruct* p_front;
        materialStruct2* e_front;

//    init_stars();
//    stars();

         glEnable(GL_LIGHTING);
         GLfloat	 lightPos[] = { 0.0, 0.0, 1.0, 1};
         glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

         glTranslatef(0,0,0);

     glPushMatrix();
    e_front = &sunMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    e_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    e_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   e_front->specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   e_front->emission);
    glMaterialf(GL_FRONT, GL_SHININESS,   e_front->shininess);
     // sun

    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef((float)angle/2, 0.0f, 0.0f, -1.0f);
    this->sun();
    glPopAttrib();
    glPopMatrix();

    e_front = &orbitMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    e_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    e_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   e_front->specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   e_front->emission);
    glMaterialf(GL_FRONT, GL_SHININESS,   e_front->shininess);

    line(SUN_R*0.5);
    line(SUN_R*0.8);
    line(SUN_R*1.2);
    line(SUN_R*1.6);
    line(SUN_R*2.5);
    line(SUN_R*3.1);


    gluQuadricTexture(ball, GLU_TRUE);

    e_front = &starMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    e_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    e_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   e_front->specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,   e_front->emission);
    glMaterialf(GL_FRONT, GL_SHININESS,   e_front->shininess);


    //mercury
       glPushMatrix();
       glRotatef((float)angle*1.4,0,1,0);
       glTranslatef(SUN_R*0.5,0,0);
       glRotatef(90, 1.0f, 0.0f, 0.0f);
       glRotatef((float)angle*2, 0.0f, 0.0f, -1.0f);
       glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, textures[1]);
       this->moon();
       glPopAttrib();
       glPopMatrix();

       //venus
          glPushMatrix();
          glRotatef((float)angle/1.2,0,1,0);
          glTranslatef(SUN_R*0.8,0,0);
          glRotatef(90, 1.0f, 0.0f, 0.0f);
          glRotatef((float)angle*3, 0.0f, 0.0f, 1.0f);
          glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, textures[5]);
          this->earth();
          glPopAttrib();
          glPopMatrix();



    //earth
       glPushMatrix();
       glRotatef((float)angle/3,0,1,0);
       glTranslatef(SUN_R*1.2,0,0);
       glRotatef(90, 1.0f, 0.0f, 0.0f);
       glRotatef((float)angle*2, 0.0f, 0.0f, -1.0f);
       glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, textures[2]);
       this->earth();
       glPopAttrib();
    // moon
       glRotatef(0,0,1,1);
       glTranslatef(0.4,0.4,0.);
       glRotatef((float)angle*0.6, 0.0f, 0.0f, 1.0f);
       glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, textures[3]);
       this->moon();
       glPopAttrib();
       glPopMatrix();


       //mars
          glPushMatrix();
          glRotatef((float)angle/4.,0,1,0);
          glTranslatef(SUN_R*1.6,0,0);
          glRotatef(90, 1.0f, 0.0f, 0.0f);
          glRotatef((float)angle*3, 0.0f, 0.0f, -1.0f);
          glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, textures[6]);
          this->mercury();
          glPopAttrib();
          glPopMatrix();


    //Jupiter
       glPushMatrix();
       glRotatef((float)angle/5,0,1,0);
       glTranslatef(SUN_R*2.5,0,0);
       glRotatef(90, 1.0f, 0.0f, 0.0f);
       glRotatef((float)angle*4, 0.0f, 0.0f, -1.0f);
       glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, textures[4]);
       this->jupiter();
       glPopAttrib();
       glPopMatrix();


       //Saturn
          glPushMatrix();
          glRotatef((float)angle/6.4,0,1,0);
          glTranslatef(SUN_R*3.1,0,0);
          glRotatef(90, 1.0f, 0.0f, 0.0f);
          glRotatef((float)angle*4, 0.0f, 0.0f, -1.0f);
          glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, textures[7]);
          this->saturn();
          glPopAttrib();
           //saturn belt
          e_front = &beltMaterials;
          glMaterialfv(GL_FRONT, GL_AMBIENT,    e_front->ambient);
          glMaterialfv(GL_FRONT, GL_DIFFUSE,    e_front->diffuse);
          glMaterialfv(GL_FRONT, GL_SPECULAR,   e_front->specular);
          glMaterialfv(GL_FRONT, GL_EMISSION,   e_front->emission);
          glMaterialf(GL_FRONT, GL_SHININESS,   e_front->shininess);
          glRotatef(90, 1.0f, 0.0f, 0.0f);
          glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, textures[3]);
          for(float i = 0;i<0.06;i+=0.001)
              line(SUN_R*(0.24+i));
          for(float i = 0.075;i<0.1;i+=0.001)
              line(SUN_R*(0.24+i));
          glPopAttrib();
          glPopMatrix();

       //meteorite belt
       glPushMatrix();
       p_front = &whiteShinyMaterials;
       glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
       glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
       glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
       glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

       for(float count=1;count<7;count++){
           for (int i = 0; i < 20; i++){
               glPushMatrix();
               glRotatef((float)angle/3.5+i*(20+count),0.,1,0);
             // glColor3f(1.0f, 0.0f, 0.0f);
              glTranslatef(SUN_R*2-count/30,count/20,count/20);
              this->meteorite2();
              glPopMatrix();
               }
           for (int i = 0; i < 150; i++){
               glPushMatrix();
               glRotatef((float)angle/3.5+i*(3+count),0.,1,0);
               glTranslatef(SUN_R*2-count/30,count/20,count/20);
              this->meteorite();
              glPopMatrix();
               }
           }
 glPopMatrix();

	glLoadIdentity();
        gluLookAt(1,1,1, (float)spot/5,0.0,0., (float)spot/10,1.0,0.);

	// flush to screen
	glFlush();	

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            //WIN_SIZE=(int)(WIN_SIZE%10);
            glOrtho(-1*WIN_SIZE, WIN_SIZE, -1*WIN_SIZE, WIN_SIZE, -1*WIN_SIZE, WIN_SIZE);

	} // paintGL()
