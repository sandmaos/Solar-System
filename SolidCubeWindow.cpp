#include "SolidCubeWindow.h"
#include <iostream>

using namespace std;

// constructor / destructor
SolidCubeWindow::SolidCubeWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

    // create the window layout
    windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	cubeWidget = new HierarchyWidget(this);
	windowLayout->addWidget(cubeWidget);

    // create slider


        nSlider = new QSlider(Qt::Horizontal);
            connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateSize(int)));
            nSlider->setMinimum(3);
            nSlider->setMaximum(22);
            nSlider->setValue(9);

            nSlider1 = new QSlider(Qt::Horizontal);
                connect(nSlider1, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateSpot(int)));
                nSlider1->setMinimum(-30);
                nSlider1->setMaximum(35);
                nSlider1->setValue(3);

                nSlider2 = new QSlider(Qt::Horizontal);
                    connect(nSlider2, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateScale(int)));
                    nSlider2->setMinimum(-110);
                    nSlider2->setMaximum(110);
                    nSlider2->setValue(0);

                    Layout = new QHBoxLayout();
                    QLabel *label=new QLabel();
                    label->setText("Scale");
                    Layout->addWidget(label);
                    Layout->addWidget(nSlider);
                    windowLayout->addLayout(Layout);

                    Layout1 = new QHBoxLayout();
                    QLabel *label1=new QLabel();
                    label1->setText("Spot");
                    QLabel *label2=new QLabel();
                    label2->setText("Speed");
                    Layout->addWidget(label1);
                    Layout->addWidget(nSlider1);
                     Layout->addWidget(label2);
                    Layout->addWidget(nSlider2);
                        windowLayout->addLayout(Layout1);



	ptimer = new QTimer(this);
        connect(ptimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle())); 
        ptimer->start(1);

	} // constructor

SolidCubeWindow::~SolidCubeWindow()
	{ // destructor
	  delete ptimer; 
	delete nSlider;
    delete nSlider1;
    delete nSlider2;
	delete cubeWidget;
	delete windowLayout;

	} // destructor

// resets all the interface elements
void SolidCubeWindow::ResetInterface()
	{ // ResetInterface()
	cubeWidget->update();
	update();
	} // ResetInterface()
