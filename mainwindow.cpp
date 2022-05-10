#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evaluator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_graphicsScene = new QGraphicsScene(this);
    ui->outGraph->setScene(m_graphicsScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processFunction(QString raw){
    raw.capacity();
}

void MainWindow::on_inGraph_returnPressed()
{
    m_graphicsScene->~QGraphicsScene();
    m_graphicsScene = new QGraphicsScene(this);
    ui->outGraph->setScene(m_graphicsScene);
    QPainter* p;
    p=new QPainter;
    QPen pen(Qt::red, 0.5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    p->setPen(pen);
    p->drawPoint(0, 0);
    QPoint Ox1(-1000, 0), Ox2(1000, 0), Oy1(0, -1000), Oy2(0, 1000);
    QLine Ox(Ox1, Ox2), Oy(Oy1, Oy2);
    m_graphicsScene->addLine(Ox,pen);
    m_graphicsScene->addLine(Oy,pen);

    Eval.SetString(ui->inGraph->text());

    for(float i=0; i<1000 && Eval.Evaluate(i)<=1000 && Eval.Evaluate(i)>=-1000; i=i+0.1){
        QPoint A(i, -Eval.Evaluate(i)), B(i+1, -Eval.Evaluate(i+1)); //de ce y? de ce?
        QLine AB(A, B);
        m_graphicsScene->addLine(AB, pen);
    }
    for(float i=0; i>-1000 && Eval.Evaluate(i)<=1000 && Eval.Evaluate(i)>=-1000; i=i-0.1){
        QPoint A(i, -Eval.Evaluate(i)), B(i+1, -Eval.Evaluate(i+1));
        QLine AB(A, B);
        m_graphicsScene->addLine(AB, pen);
    }

    ui->outGraph->setScene(m_graphicsScene);

    ui->outGraph->centerOn(-100,-100);
    ui->outGraph->show();

}


void MainWindow::on_inCalc_returnPressed()
{
    Eval.SetString(ui->inCalc->text());
    calcText.append("\n");
    calcText.append(QString::number(Eval.Evaluate()));
    ui->outCalc->setText(calcText);
}


void MainWindow::on_clearButton_clicked()
{
    calcText.clear();
    ui->outCalc->setText(calcText);
}

