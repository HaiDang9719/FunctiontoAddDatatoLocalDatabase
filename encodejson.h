#ifndef ENCODEJSON_H
#define ENCODEJSON_H
#include<QString>
#include <QJsonObject>
#include<QJsonDocument>

class encodejson
{
public:
    encodejson();
    QString encodejsonpackage(double pressure, double current, double voltage);
};

#endif // ENCODEJSON_H
