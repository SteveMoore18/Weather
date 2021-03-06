#include "WeatherData.h"

WeatherData::WeatherData()
{
    data = shared_ptr<DATA>(new DATA());
    //makeRequest(CITY);
}

WeatherData::~WeatherData()
{
    //delete reply;
}

void WeatherData::makeRequest(const QString city)
{
    OUT_LINK = LINK.arg(city).arg(API_KEY);

    request = QNetworkRequest(OUT_LINK);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = accessManeger.get(request);

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

    if (!checkResponse(responseData)) {
        return;
    }

    writeToDATAStruct(responseData);

    reply->deleteLater();
    delete reply;
}

shared_ptr<WeatherData::DATA> WeatherData::getData() const
{
    return data;
}

QString WeatherData::getResponseCode() const
{
    return responseCode;
}

QString WeatherData::getErrorMessage() const
{
    return errorMessage;
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

    // Getting main and description weather and icon
    {
        QJsonArray weatherArr = jsonObj["weather"].toArray();
        QJsonObject weatherObj = weatherArr[0].toObject();

        data->description = weatherObj["description"].toString();
        data->main = weatherObj["main"].toString();

        QString iconCode = weatherObj["icon"].toString();
        data->icon = QPixmap(QString(":/icons/icons/%1@2x.png").arg(iconCode));
        data->icon = data->icon.scaled(200, 200);
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


//    qDebug() << data->main;
//    qDebug() << data->description;
//    qDebug() << "Current temp: " << data->currentTemperature;
//    qDebug() << "Real temp: " << data->realTemperature;
//    qDebug() << "Wind speed: " << data->windSpeed << " m/s";

}

double WeatherData::kelvinToCelsius(const double value)
{
    return value - 273.15;
}

bool WeatherData::checkResponse(const QByteArray &arrData)
{
    QJsonDocument doc = QJsonDocument::fromJson(arrData);
    QJsonObject jsonObj = doc.object();
    QJsonValue tempResponseCode = jsonObj["cod"];

    if (tempResponseCode.type() == QJsonValue::Type::Double) {

        double t = tempResponseCode.toDouble();
        responseCode = QString("%1").arg(t);

    } else if (tempResponseCode.type() == QJsonValue::Type::String) {

        responseCode = tempResponseCode.toString();

    }


    if (responseCode != "200") {
        errorMessage = jsonObj["message"].toString();
        return false;
    }

    return true;

}
