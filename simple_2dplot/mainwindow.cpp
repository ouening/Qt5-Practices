#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tinyexpr.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str=ui->lineEdit->text();
    QByteArray byte  =str.toLocal8Bit();
    const char *expression = byte.data();   // QString to const char

    QString var_a = ui->lineEdit_2->text();
    QByteArray _a  =var_a.toLocal8Bit();
    const char *variable_a = _a.data(); // QString to const char

    QString var_b = ui->lineEdit_3->text();
    QByteArray _b  =var_b.toLocal8Bit();
    const char *variable_b = _b.data(); // QString to const char

    int err;
    double a = te_interp(variable_a, &err);
    double b = te_interp(variable_b, &err);
    qDebug() << "a=" << a << "b=" << b << endl;

    int LEN = 1000;
    QVector<double> x_vec(LEN), y_vec(LEN); // initialize with entries 0..100

    double h = (double) (b-a)/(double)LEN;
    /* the variables x is bound at eval-time. */
    double x;
    te_variable vars[] = {{"x", &x, TE_VARIABLE, }};
    /* This will compile the expression and check for errors. */
    te_expr *n = te_compile(expression, vars, 1, &err);

    // evaluating the function results
    for (int i=0; i<LEN; ++i)
    {
        x_vec[i] = a + i*h; // x goes from -1 to 1
        if (n)
        {
            x = x_vec[i];
            y_vec[i] = (double)te_eval(n);
        }
    }

    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x_vec, y_vec);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->rescaleAxes(true);
    ui->widget->replot();

}
