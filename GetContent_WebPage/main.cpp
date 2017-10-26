#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //TODO: Create UI allow user set city and country
    QString city = "hanoi";
    QString country = "vietnam";
    QString path = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22" + city + "%2C%20" + country + "%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
    QUrl url(path);
    int highTemp, lowTemp;
    QString imageSrc;
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkRequest req(url);
    QNetworkReply *reply = nam.get(req);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray buffer = reply->readAll();
    QString str(buffer);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject rootObj = jsonDoc.object();
    QJsonObject query = rootObj["query"].toObject();
    QJsonObject results = query["results"].toObject();
    QJsonObject channel = results["channel"].toObject();
    QJsonObject item = channel["item"].toObject();
    QJsonArray forecast = item["forecast"].toArray();
    QJsonObject obj = forecast.at(0).toObject();
    highTemp = obj["high"].toString().toInt();
    lowTemp = obj["low"].toString().toInt();
    imageSrc = item["description"].toString();
    auto ctx = engine.rootContext();
    ctx->setContextProperty("high",highTemp);
    ctx->setContextProperty("low", lowTemp);
    ctx->setContextProperty("srcWea", imageSrc);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //TODO: Wrap this code in a Class inherit from QQuickItem, then make it as a QML Component for reuse purpose
    //Create a timer to update weather information daily

    return app.exec();
}

