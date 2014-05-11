#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera.h"
#include "videoqlabel.h"
#include "calibration.h"
#include "frame_holder.h"
#include "video_dispatch.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <QCloseEvent>
#include <QGridLayout>


// Constructor:
//*********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    createMenu();

    // main layout:
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);
    // ui->setupUi(this);


    // left box:
    //**************************************************




    QWidget *leftBox = new QWidget(centralWidget);
    QVBoxLayout *leftBoxLayout = new QVBoxLayout(leftBox);
    leftBox->setLayout(leftBoxLayout);
    leftBox->setStyleSheet("background-color:#e9e9e9;");


    createLeftBoxLayout(leftBoxLayout);

    QGroupBox *algorithmStartBox = createAlgorithmBox();
    leftBoxLayout->addWidget(algorithmStartBox);

    QGroupBox *calibrationBox = createCalibrationBox();
    leftBoxLayout->addWidget(calibrationBox);

    QGroupBox *mouseBox = createMouseBox();
    leftBoxLayout->addWidget(mouseBox);

    //right box:
    //**************************************************
    QWidget *rightBox = new QWidget;

    // video box QLabel
    VideoQLabel *videoBox = new VideoQLabel(rightBox);
    videoBox->setActiveClick(true);
    videoBox->setText("Video stream window");

    QGridLayout *rightBoxLayout = new QGridLayout;
    rightBoxLayout->addWidget(videoBox);
    rightBox->setLayout(rightBoxLayout);
    rightBox->setStyleSheet("background-color:#e9e9e9;");

    // add boxes to main layout:
    mainLayout->addWidget(leftBox,1);
    mainLayout->addWidget(rightBox,3);

    // set central widget of QMainWindow
    setCentralWidget(centralWidget);

    // calibration measures
    calibration = new Calibration();
    FrameHolder *holder = new FrameHolder();
    calibration->setFrameHolder(holder);

    dispatcher = new VideoDispatcher();
    dispatcher->attach(videoBox);
    dispatcher->attach(holder);
    initiateTimer();
    connect(videoBox,SIGNAL(mousePressed(QPoint,QSize)),calibration,SLOT(receiveClickedPixel(QPoint,QSize)));
    calibration->setState(GATHERING);
}

// Destructor:
//*********************************************************************************************************************
MainWindow::~MainWindow()
{
}

void MainWindow::createMenu(){

    saveAction = new QAction("Save", this);
    loadAction = new QAction("Load", this);
    quitAction = new QAction("Quit", this);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(load()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menuFile = new QMenu("File",menuBar);
    menuBar->addMenu(menuFile);
    menuFile->addAction(saveAction);
    menuFile->addAction(loadAction);
    menuFile->addAction(quitAction);

    setMenuBar(menuBar);
}

// methods:
//*********************************************************************************************************************

QGroupBox* MainWindow::createAlgorithmBox(){

    QGroupBox *algorithmStartBox = new QGroupBox("Algorithm:");
    startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));

    QWidget *comboWidget = new QWidget;
    QLabel *comboLabel = new QLabel("Choose camera:");
    QHBoxLayout *comboLayout = new QHBoxLayout;
    camerasCombo= new QComboBox;
    /***************************************************************
     *
     * Napisać kod znajdujący kamery
     *
     *
     * *************************************************************/
    camerasCombo->addItem("A");
    camerasCombo->addItem("B");
    camerasCombo->addItem("C");
    comboLayout->addWidget(comboLabel);
    comboLayout->addWidget(camerasCombo);
    comboWidget->setLayout(comboLayout);

    stopButton = new QPushButton("Stop");
    connect(stopButton,SIGNAL(clicked()), this, SLOT(stop()));

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(startButton);
    boxLayout->addWidget(comboWidget);
    boxLayout->addWidget(stopButton);

    algorithmStartBox->setLayout(boxLayout);

    return algorithmStartBox;
}

QGroupBox* MainWindow::createCalibrationBox(){

    QGroupBox *algorithmCalibrationBox = new QGroupBox("Calibration:");


    return algorithmCalibrationBox;
}

QGroupBox* MainWindow::createMouseBox(){

    QGroupBox *algorithmMouseBox = new QGroupBox("Mouse:");

    return algorithmMouseBox;
}

void MainWindow::initiateTimer(){
    paintTimer = new QTimer(this);
    connect(paintTimer,SIGNAL(timeout()),dispatcher,SLOT(dispatchFrame()));
    paintTimer->start(1000/DEFAULT_FPS);
}

void MainWindow::closeEvent(QCloseEvent *event){
    quit();
}


void MainWindow::createLeftBoxLayout(QVBoxLayout *layout){

  /*  QTabWidget *tabs = new QtabWidget();

    QWidget *primary = new QWidget();
    QWidget *Calibration = new Qwidget();*/
}


void MainWindow::cleanUp(){
    paintTimer->stop();
    delete dispatcher;
}


// Slots:
//*********************************************************************************************************************
void MainWindow::save(){

}

void MainWindow::load(){

}

void MainWindow::quit(){
    /*QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Mouth", "Do you really want to quit?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
        cleanUp();
        qApp->quit();
    }*/
    cleanUp();
    qApp->quit();
}

// butons:
void MainWindow::start(){

}

void MainWindow::stop(){

}
