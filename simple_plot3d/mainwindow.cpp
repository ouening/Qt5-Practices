#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <mgl2/qmathgl.h>
#include "mgl2/qt.h"
#include <QDebug>
#include <QLineEdit>

//const char *expr="sin((x^2+y^2))/sqrt(x^2+y^2+1)";

const char *expr;   // here `expr` is a global variable

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(850,610);
    this->setWindowTitle("Simple 3D plot!");

    QMGL = new QMathGL(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int example(mglGraph *gr)
{
    gr->Rotate(20,40);
    gr->SetRanges(-3,3,-3,3,-1,1);
    //    gr->FSurf("sin((x^2+y^2))/sqrt(x^2+y^2+1)");
    qDebug() << expr << endl;
    gr->FSurf(expr);
    //    gr->Drop(mglPoint(0,0,3),mglPoint(0,0,-1),0.7,"b");
    gr->Box();
    gr->Axis();
    gr->Rotate(50,60);
    gr->Title("Sample Plot!","", -1);   // -1 is the font size of title
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    QByteArray byte = str.toLocal8Bit();
    expr = byte.data();     // update the variable `expr`, convert QString to const chat

    QMGL->setDraw(example);
    //    QMGL->adjust();
    //    QMGL->setGrid(true);
    QMGL->setZoom(true);
    QMGL->setRotate(true);
    QMGL->update();
}
