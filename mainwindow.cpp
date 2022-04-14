#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicsscene.h"
#include "graphicsview.h"
#include <QHBoxLayout>

#include "Stan.h"
#include "winbgi_qt.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto *VBoxLayout=new QVBoxLayout();

    auto Fscene=new GraphicsScene(this);

    auto graphicsView = new GraphicsView(ui->frame);
    graphicsView->setScene(Fscene);
    VBoxLayout->addWidget(graphicsView);
    ui->frame->setLayout(VBoxLayout);


    QPixmap *pixmap=new QPixmap(1280,1024);
    QPainter painter(pixmap);
    auto brush=painter.brush();
    auto pen=painter.pen();
    pen.setColor(Qt::green);
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0,1280,1024);


    Station *stan=new Station("");
//    QString fn="d:/__E/EXE/WinDnc/sta/holoni.ste";
    QString fn="sta/holoni.ste";

    stan->Open(fn.toStdString().c_str());
    setAntLibPainter(&painter);
    stan->Go();
    Fscene->addPixmap(*pixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{

}

