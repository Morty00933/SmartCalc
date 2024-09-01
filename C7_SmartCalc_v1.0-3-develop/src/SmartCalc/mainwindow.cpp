#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../h_calc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clean_clicked()
{
    ui->label->clear();
}

void MainWindow::on_pushButton_dot_clicked()
{
    ui->label->setText(ui->label->text() + '.');
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->label->setText(ui->label->text() + '1');
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText(ui->label->text() + '2');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label->setText(ui->label->text() + '3');
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label->setText(ui->label->text() + '4');
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label->setText(ui->label->text() + '5');
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->label->setText(ui->label->text() + '6');
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->label->setText(ui->label->text() + '7');
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->label->setText(ui->label->text() + '8');
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->label->setText(ui->label->text() + '9');
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->label->setText(ui->label->text() + '0');
}

void MainWindow::on_pushButton_open_bracket_clicked()
{
    ui->label->setText(ui->label->text() + '(');
}

void MainWindow::on_pushButton_close_bracket_clicked()
{
    ui->label->setText(ui->label->text() + ')');
}

void MainWindow::on_pushButton_plus_clicked()
{
    ui->label->setText(ui->label->text() + '+');
}

void MainWindow::on_pushButton_minus_clicked()
{
    ui->label->setText(ui->label->text() + '-');
}

void MainWindow::on_pushButton_multiple_clicked()
{
    ui->label->setText(ui->label->text() + '*');
}

void MainWindow::on_pushButton_divide_clicked()
{
    ui->label->setText(ui->label->text() + '/');
}

void MainWindow::on_pushButton_degree_clicked()
{
    ui->label->setText(ui->label->text() + '^');
}

void MainWindow::on_pushButton_mod_clicked()
{
    ui->label->setText(ui->label->text() + "mod");
}

void MainWindow::on_pushButton_cosinus_clicked()
{
    ui->label->setText(ui->label->text() + "cos(");
}

void MainWindow::on_pushButton_sinus_clicked()
{
    ui->label->setText(ui->label->text() + "sin(");
}

void MainWindow::on_pushButton_tan_clicked()
{
    ui->label->setText(ui->label->text() + "tan(");
}

void MainWindow::on_pushButton_acos_clicked()
{
    ui->label->setText(ui->label->text() + "acos(");
}

void MainWindow::on_pushButton_asin_clicked()
{
    ui->label->setText(ui->label->text() + "asin(");
}

void MainWindow::on_pushButton_atan_clicked()
{
    ui->label->setText(ui->label->text() + "atan(");
}

void MainWindow::on_pushButton_sqrt_clicked()
{
    ui->label->setText(ui->label->text() + "sqrt(");
}

void MainWindow::on_pushButton_ln_clicked()
{
    ui->label->setText(ui->label->text() + "ln(");
}

void MainWindow::on_pushButton_log_clicked()
{
    ui->label->setText(ui->label->text() + "log(");
}


void MainWindow::on_pushButton_equal_clicked()  /* = */
{
    QString str1 = ui->label->text();
    QByteArray ba = str1.toLocal8Bit();
    char *func = ba.data();
    double xnum = 0;
    int flag = 0;
    if (ui->x_value->text() != "") {
        if ((ui->x_value->text() >= "0" && ui->x_value->text() <= "9")) {
            xnum = (ui->x_value->text().toDouble());
        } else {
            flag = 1;
        }
    }
    if (!check_error(func) && !flag)
    {
        double res = calc(reverse_input(push_to_ready(reverse_input(parser(func, xnum)))));

        ui->label->setText(QString::number(res, 'g', 8));
    } else {
        ui->label->clear();
        ui->label->setText(ui->label->text() + "Invalid value");
    }
}

void MainWindow::on_pushButton_x_clicked()  /* x */
{
    ui->label->setText(ui->label->text() + "x");
}

void MainWindow::on_pushButton_graph_clicked()  /* graph */
{
   ui->openGLWidget->xAxis->setRange(-100, 100);
   ui->openGLWidget->yAxis->setRange(-100, 100);


   double y2 = 0;
   double delta = 0.1;


       QString str1 = ui->label->text();
       if (str1 == "\0") {
           str1 = "0";
       }
       QByteArray ba = str1.toLocal8Bit();
       char *func = ba.data();
       if (!check_error(func)) {
         for (double i = -100; i <= 100; (i += delta)) {
              x.push_back(i);
             y2 = calc(reverse_input(push_to_ready(reverse_input(parser(func, i)))));
             y.push_back(y2);}
        } else {
             ui->label->clear();
             ui->label->setText(ui->label->text() + "Invalid value");
         }
       ui->openGLWidget->addGraph();
       ui->openGLWidget->graph(0)->addData(x, y);
       ui->openGLWidget->replot();
       x.clear();
       y.clear();
       ui->openGLWidget->graph(0)->data()->clear();

}
