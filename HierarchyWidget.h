#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <windows.h>
#include <GL/glu.h>

class HierarchyWidget: public QGLWidget
	{ // 

	Q_OBJECT

	public:

	HierarchyWidget(QWidget *parent);
	~HierarchyWidget();

    void line(float dis);

    public slots: void updateAngle();

    public slots: void updateSize(int i);
	
    public slots: void updateSpot(int i);

    public slots: void updateScale(int i);
	

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

    void sun();
    void meteorite();
    void meteorite2();
    void moon();
    void mercury();
    void jupiter();
    void earth();
    void saturn();


    GLUquadricObj* ball;

	int angle;
    double spot;
    int WIN_SIZE;
    int scale;

	}; // class GLPolygonWidget
	
#endif
