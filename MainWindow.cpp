#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mainWidget = shared_ptr<QWidget>(new QWidget());
    mainLayout = shared_ptr<QVBoxLayout>(new QVBoxLayout());

    infoInterfaceLayout = shared_ptr<QHBoxLayout>(new QHBoxLayout());

    moreInfoLayout = shared_ptr<QVBoxLayout>(new QVBoxLayout());
    lbCurrentTemperature = shared_ptr<QLabel>(new QLabel("0°"));
    lbRealTemperature = shared_ptr<QLabel>(new QLabel("0"));
    lbWindSpeed = shared_ptr<QLabel>(new QLabel("100"));
    lbMain = shared_ptr<QLabel>(new QLabel("None"));
    lbDescription = shared_ptr<QLabel>(new QLabel("None"));

    lbCurrentTemperature->setAlignment(Qt::AlignCenter);

    btnUpdate = shared_ptr<QPushButton>(new QPushButton("Update"));
    connect(btnUpdate.get(), &QPushButton::clicked, this, &MainWindow::onBtnUpdateClicked);;

    weatherData = shared_ptr<WeatherData>(new WeatherData());

    temperatureFont = QFont(":/fonts/Fonts/Proxima Nova Alt Regular.otf", 36);
    lbCurrentTemperature->setFont(temperatureFont);
    lbCurrentTemperature->setMinimumWidth(150);

    moreInfoFont = temperatureFont;
    moreInfoFont.setPixelSize(18);
    lbRealTemperature->setFont(moreInfoFont);
    lbWindSpeed->setFont(moreInfoFont);
    lbMain->setFont(moreInfoFont);
    lbDescription->setFont(moreInfoFont);

    infoInterfaceLayout->addWidget(lbCurrentTemperature.get());
    moreInfoLayout->addWidget(lbRealTemperature.get());
    moreInfoLayout->addWidget(lbWindSpeed.get());
    moreInfoLayout->addWidget(lbMain.get());
    moreInfoLayout->addWidget(lbDescription.get());

    mainLayout->addLayout(infoInterfaceLayout.get());
    infoInterfaceLayout->addLayout(moreInfoLayout.get());
    mainLayout->addWidget(btnUpdate.get());
    mainWidget->setLayout(mainLayout.get());
    setCentralWidget(mainWidget.get());

    onBtnUpdateClicked();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onBtnUpdateClicked()
{
    weatherData->makeRequest("Moscow");

    const int currTemp = weatherData->getData()->currentTemperature;
    const int realTemp = weatherData->getData()->realTemperature;
    const unsigned int windSpeed = weatherData->getData()->windSpeed;
    const QString main = weatherData->getData()->main;
    const QString description = weatherData->getData()->description;

    lbCurrentTemperature->setText(QString("%1 °C").arg(currTemp));
    lbRealTemperature->setText(QString("Feels like:  \t%1 °C").arg(realTemp));
    lbWindSpeed->setText(QString("Wind speed:  \t%1 m/s").arg(windSpeed));
    lbMain->setText(QString("%1").arg(main));
    lbDescription->setText(QString("%1").arg(description));

}

