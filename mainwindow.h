#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* m_graphicsScene;
    void processFunction(QString raw);
    void drawFunction();
};
#endif // MAINWINDOW_H
