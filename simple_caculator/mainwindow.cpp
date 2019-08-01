#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinyexpr.h" // import this header file
#include <stdio.h>
#include <QDebug>
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
    qDebug() << "Evaluating:\n\t%s\n" << expression << endl;

    QString var = ui->lineEdit_2->text();
    QByteArray var_byte  =var.toLocal8Bit();
    const char *variable = var_byte.data(); // QString to const char

    /* the variables x is bound at eval-time. */
    double x;
    te_variable vars[] = {{"x", &x, TE_VARIABLE, }};

    /* This will compile the expression and check for errors. */
    int err;

    te_expr *n = te_compile(expression, vars, 1, &err);
    if (n) {
        /* Here we evaluate the value of variable x using tinyexpr again */
        x = te_interp(variable, &err);

        qDebug() << "The value of variable is :" << x << endl;

        const double r = te_eval(n); // evaluate the expression

        ui->lineEdit_3->setText(QString::number(r));

        te_free(n);
    } else {
        /* Show the user where the error is at. */
        qDebug() << "\t%*s^\nError near here" << err-1 << endl ;
    }

}
