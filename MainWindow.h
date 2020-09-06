#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>

#include <WeatherData.h>

#include <thread>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onBtnUpdateClicked();

private:

    shared_ptr<QWidget> mainWidget;
    shared_ptr<QVBoxLayout> mainLayout;
    shared_ptr<QLineEdit> lnCity;
    shared_ptr<QLabel> lbCurrentCity;

    // Here will show current temperature
    shared_ptr<QHBoxLayout> infoInterfaceLayout;
    shared_ptr<QLabel> lbCurrentTemperature;

    // Here will show more information
    shared_ptr<QVBoxLayout> moreInfoLayout;
    shared_ptr<QLabel> lbRealTemperature;
    shared_ptr<QLabel> lbWindSpeed;
    shared_ptr<QLabel> lbMain;
    shared_ptr<QLabel> lbDescription;

    shared_ptr<WeatherData> weatherData;

    shared_ptr<QPushButton> btnUpdate;

    QFont temperatureFont;
    QFont moreInfoFont;

};
#endif // MAINWINDOW_H
