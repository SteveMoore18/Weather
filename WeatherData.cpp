#include "WeatherData.h"

WeatherData::WeatherData()
{
    data = shared_ptr<DATA>(new DATA());
    //makeRequest(CITY);
}

WeatherData::~WeatherData()
{
    delete reply;
}

void WeatherData::makeRequest(const QString city)
{
    OUT_LINK = LINK.arg(city).arg(API_KEY);

    request = QNetworkRequest(OUT_LINK);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    reply = accessManeger.get(request);

    while (!reply->isFinished()) {
        qApp->processEvents();
    }

    QByteArray responseData = reply->readAll();

//    QFile f("/Users/savik/index.json");
//    if (!f.open(QIODevice::ReadOnly)) {
//        qDebug() << "Read file error";
//        return;
//    }
//    QByteArray arr = f.readAll();
//    f.close();

    writeToDATAStruct(responseData);

    reply->deleteLater();
}

shared_ptr<WeatherData::DATA> WeatherData::getData() const
{
    return data;
}


void WeatherData::writeToDATAStruct(const QByteArray & arrData)
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(arrData, &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error!\n" << jsonError.errorString();
        return;
    }

    if (!document.isObject()) {
        qDebug() << "Error! JSON document is not object!";
        return;
    }

    QJsonObject jsonObj = document.object();

    // Getting main and description weather
    {
        QJsonArray weatherArr = jsonObj["weather"].toArray();
        QJsonObject weatherObj = weatherArr[0].toObject();

        data->description = weatherObj["description"].toString();
        data->main = weatherObj["main"].toString();
    }

    // Getting temperature, real temperature
    {
        QJsonObject mainObj = jsonObj["main"].toObject();
        data->currentTemperature = kelvinToCelsius(mainObj["temp"].toDouble());
        data->realTemperature = kelvinToCelsius(mainObj["feels_like"].toDouble());
    }

    // Getting wind speed
    {
        QJsonObject windObj = jsonObj["wind"].toObject();
        data->windSpeed = windObj["speed"].toDouble();
    }

    qDebug() << data->main;
    qDebug() << data->description;
    qDebug() << "Current temp: " << data->currentTemperature;
    qDebug() << "Real temp: " << data->realTemperature;
    qDebug() << "Wind speed: " << data->windSpeed << " m/s";

}

double WeatherData::kelvinToCelsius(const double value)
{
    return value - 273.15;
}
