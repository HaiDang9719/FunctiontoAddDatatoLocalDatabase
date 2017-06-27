#ifndef ENCODEJSON_H
#define ENCODEJSON_H
#include<QString>
#include <QJsonArray>
class encodejson
{
public:
    encodejson();
    QString identifyConnectionTimeOut();
    void updateIsSentColumn();
    void encodejsonpackageDataNode();
    void encodejsonpackageStationNode();
    void sendJsonStationPackage(QByteArray station);
    void sendJsonDataPackage(QByteArray data);


};

#endif // ENCODEJSON_H
