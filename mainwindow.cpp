#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_graphicsScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_graphicsScene);
    QPainter* p;
    p=new QPainter;
    QPen pen(Qt::white, 0.5, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    p->setPen(pen);
    p->drawPoint(0, 0);
    QPoint Ox1(-1000, 0), Ox2(1000, 0), Oy1(0, -1000), Oy2(0, 1000);
    QLine Ox(Ox1, Ox2), Oy(Oy1, Oy2);
    m_graphicsScene->addLine(Ox,pen);
    m_graphicsScene->addLine(Oy, pen);
    ui->graphicsView->setScene(m_graphicsScene);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_returnPressed()
{

}

