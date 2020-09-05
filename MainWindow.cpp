#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mainWidget = shared_ptr<QWidget>(new QWidget());
    mainLayout = shared_ptr<QVBoxLayout>(new QVBoxLayout());

    infoInterfaceLayout = shared_ptr<QHBoxLayout>(new QHBoxLayout());
    lbCurrentTemperature = shared_ptr<QLabel>(new QLabel("0°"));

    moreInfoLayout = shared_ptr<QVBoxLayout>(new QVBoxLayout());
    lbRealTemperature = shared_ptr<QLabel>(new QLabel("0"));
    lbWindSpeed = shared_ptr<QLabel>(new QLabel("100"));

    btnUpdate = shared_ptr<QPushButton>(new QPushButton("Update"));
    connect(btnUpdate.get(), &QPushButton::clicked, this, &MainWindow::onBtnUpdateClicked);;




    infoInterfaceLayout->addWidget(lbCurrentTemperature.get());
    moreInfoLayout->addWidget(lbRealTemperature.get());
    moreInfoLayout->addWidget(lbWindSpeed.get());

    mainLayout->addLayout(infoInterfaceLayout.get());
    infoInterfaceLayout->addLayout(moreInfoLayout.get());
    mainLayout->addWidget(btnUpdate.get());
    mainWidget->setLayout(mainLayout.get());
    setCentralWidget(mainWidget.get());
}

MainWindow::~MainWindow()
{

}

void MainWindow::onBtnUpdateClicked()
{
    qDebug() << "Hello world";
}

