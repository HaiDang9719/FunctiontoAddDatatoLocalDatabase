#include "encodejson.h"
#include <QJsonObject>
encodejson::encodejson()
{

}
QString encodejson::encodejsonpackage(double pressure, double current, double voltage)
{
    QJsonObject obj;
    obj.insert("Pressure", QString("200"));
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    QString jsonString(data);
    return data;
}
