#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    void display(const QImage&);
    void resizeEvent(QResizeEvent*);

    void on_loadButton_clicked();
    void on_saveButton_clicked();

};

#endif // MAINWINDOW_H

