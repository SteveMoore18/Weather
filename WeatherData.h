#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QDebug>
#include <QtNetwork>
#include <QPixmap>

using namespace std;

class WeatherData
{

    struct DATA {
        double currentTemperature; //C
        double realTemperature; // C
        double windSpeed; // m/s
        QString main;
        QString description;
        QPixmap icon;

        DATA() {
            currentTemperature = 0;
            realTemperature = 0;
            windSpeed = 0;
        }
    };

public:
    WeatherData();
    ~WeatherData();

    void makeRequest(const QString city);



    shared_ptr<DATA> getData() const;

    QString getResponseCode() const;

    QString getErrorMessage() const;

private:


    shared_ptr<DATA> data;


    const QString API_KEY = "705e9e2d3fe296187f82687ed0cd7351";
    const QString LINK = "https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2";
    QString CITY = "Moscow";
    QString OUT_LINK = "";

    QNetworkRequest request;
    QNetworkAccessManager accessManeger;
    QNetworkReply *reply;

    QString responseCode;
    QString errorMessage;

private:
    void writeToDATAStruct(const QByteArray & arrData);

    double kelvinToCelsius(const double value);

    bool checkResponse(const QByteArray & arrData);

};

#endif // WEATHERDATA_H
