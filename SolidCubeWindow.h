#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QTimer>
#include "HierarchyWidget.h"
 #include <QLabel>
class SolidCubeWindow: public QWidget
	{ 
	public:	
	// constructor / destructor
	SolidCubeWindow(QWidget *parent);
	~SolidCubeWindow();

	// window layout
	QBoxLayout *windowLayout;
    QHBoxLayout* Layout;
    QHBoxLayout* Layout1;

	// beneath that, the main widget
	HierarchyWidget *cubeWidget;
    QLabel *label;
    QLabel *label1;
    QLabel *label2;
	// and a slider for the number of vertices
	QSlider *nSlider;
    QSlider *nSlider1;
    QSlider *nSlider2;
	// timer for animation
	QTimer* ptimer;

	// resets all the interface elements
	void ResetInterface();
	}; 
	
#endif
