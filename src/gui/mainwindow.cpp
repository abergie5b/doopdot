#include <QtWidgets>
#include <functional>

#include "mainwindow.h"
#include "../../ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Select a single image"));
    original = QImage(filename);
    reset_default_parameters();
    display(original);
    ui->comboBox->setCurrentIndex(0);
    grayscale = original.convertToFormat(QImage::Format_Grayscale8);
}

void MainWindow::display(const QImage& image) {
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());
    ui->image->setScene(scene);
    ui->image->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    current = image;
}

