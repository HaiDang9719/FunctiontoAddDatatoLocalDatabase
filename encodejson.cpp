#include "encodejson.h"
#include <QJsonObject>
#include<QJsonDocument>
#include<QDebug>
#include <QJsonArray>
#include <QString>
#include <QSqlQuery>
#include <QDateTime>
#include <QtNetwork>
#include <QNetworkReply>
#include <QTimer>
encodejson::encodejson()
{

}

// identify connection timeout when connect with server
QString encodejson::identifyConnectionTimeOut()
{
    QSqlQuery query;
    QString total,RFID;
    query.prepare("SELECT RFID FROM stations where LocalID = ?");
    query.addBindValue(1);
    query.exec();
    if (query.next())
    {
        RFID = query.value(0).toString();
    }
    else qDebug()<<"error";
    query.prepare("SELECT COUNT(isSent) FROM "+RFID+" WHERE isSent = ?");
    query.addBindValue(0);
    query.exec();
    if(query.next())
        {
            total = query.value(0).toString();
            qDebug().noquote()<<total;
            return total;
        }
        else
        {
            qDebug()<<"count not successful";
        }
}


// update status in isSent column to identify the packages are sent
void encodejson::updateIsSentColumn()
{
    QSqlQuery query;
    QString total,RFID;
    query.prepare("SELECT COUNT(LocalID) FROM stations");
    query.exec();
    if(query.next())
        {
            total = query.value(0).toString();
            //qDebug().noquote()<<total;
        }
        else
        {
            qDebug()<<"count not successful";
        }
    for (int i = 0 ; i<total.toInt(); i++)
    {
        query.prepare("SELECT RFID FROM stations where LocalID = ?");
        query.addBindValue(i+1);
        query.exec();
        if (query.next())
        {
            RFID = query.value(0).toString();
        }
        else qDebug()<<"error";
        query.prepare("UPDATE "+RFID+" SET isSent = 1 WHERE isSent = ? ORDER BY Time ASC LIMIT 1");
        query.addBindValue(0);
        if (query.exec())
        {
            qDebug()<<"updateSuccess";
        }
    }
}


//encode json package
void encodejson::encodejsonpackageDataNode()
{
    QByteArray data;
    QSqlQuery query;
    QJsonArray dataNode;
    QString total,RFID,setRoughValveOn, setHVOn,pressure,current,voltage,time,GlobalID;
    query.prepare("SELECT COUNT(LocalID) FROM stations");
    query.exec();
    if(query.next())
        {
            total = query.value(0).toString();
            //qDebug().noquote()<<total;
        }
        else
        {
            qDebug()<<"count not successful";
        }
    for (int i = 0 ; i<total.toInt(); i++)
    {
        query.prepare("SELECT RFID, setRoughValveOn, setHVOn, GlobalID FROM stations where LocalID = ?");
        query.addBindValue(i+1);
        query.exec();
        if (query.next())
        {
            RFID = query.value(0).toString();
            setRoughValveOn = query.value(1).toString();
            setHVOn = query.value(2).toString();
            GlobalID = query.value(3).toString();
            qDebug().noquote()<<RFID<<"----"<<setRoughValveOn<<"-----"<<setHVOn<<"\n";
            query.prepare("SELECT * FROM "+RFID+" WHERE isSent = ? ORDER BY Time ASC LIMIT 1");
            query.addBindValue(1);
            query.exec();
            if(query.next())
            {
                time = query.value(0).toString();
                pressure = query.value(1).toString();
                voltage = query.value(2).toString();
                current = query.value(3).toString();
                qDebug().noquote()<<time<<"----"<<pressure<<"-----"<<voltage<<"-----"<<current<<"\n";
                QJsonObject value{
                    {"hv",setHVOn,},
                    {"valve",setRoughValveOn,},
                    {"pressure", pressure,},
                    {"current",current,},
                    {"voltage",voltage,},
                    {"rfid",RFID,},
                    {"time",time,}
                };
                QJsonObject pump
                {
                    {GlobalID,value},
                };
                dataNode << pump;
            }
        }
        else qDebug()<<"select not success";
    }
    data = QJsonDocument(dataNode).toJson(QJsonDocument::Compact);

    qDebug().noquote()<< data;
    sendJsonDataPackage(data);

}


//
void encodejson::encodejsonpackageStationNode()
{
    QByteArray station;
    QSqlQuery query;
    QJsonArray stationNode;
    QString total,globalid,stationName,isEmpty,setRoughValveOn,setHVOn,setStationOn,pumpType,pumpAddr,pumpCH,sdcsAddr,sdcsCH,thresholdDownP,thresholdUpP,thresholdUpI,thresholdDownI,RFID,warehouseName,time;
    query.prepare("SELECT COUNT(LocalID) FROM stations");
    query.exec();
    if(query.next())
        {
            total = query.value(0).toString();
            qDebug().noquote()<<total;
        }
        else
        {
            qDebug()<<"count not successful";
        }
    for (int i = 0 ; i<total.toInt(); i++)
    {
    query.prepare("SELECT * FROM stations where LocalID = ?");
    query.addBindValue(i+1);
    query.exec();
    if(query.next())
    {

        globalid = query.value(1).toString();
        stationName = query.value(2).toString();
        isEmpty = query.value(3).toString();
        setRoughValveOn = query.value(4).toString();
        setHVOn = query.value(5).toString();
        setStationOn = query.value(6).toString();
        pumpType = query.value(7).toString();
        pumpAddr = query.value(8).toString();
        pumpCH = query.value(9).toString();
        sdcsAddr = query.value(10).toString();
        sdcsCH = query.value(11).toString();
        thresholdDownP = query.value(12).toString();
        thresholdUpP = query.value(13).toString();
        thresholdUpI = query.value(14).toString();
        thresholdDownI = query.value(15).toString();
        RFID = query.value(16).toString();
        warehouseName = query.value(17).toString();
        time = query.value(18).toString();
        QJsonObject value{
            {"stationName",stationName,},
            {"isEmpty",isEmpty,},
            {"setRoughValveOn",setRoughValveOn,},
            {"setHVOn",setHVOn,},
            {"setStationOn",setStationOn,},
            {"pumpType",pumpType,},
            {"pumpAddr",pumpAddr,},
            {"pumpCh",pumpCH,},
            {"sdcsAddr",sdcsAddr,},
            {"sdcsCh",sdcsCH,},
            {"thresholdDownP",thresholdDownP,},
            {"thresholdUpP",thresholdUpP,},
            {"thresholdUpI",thresholdUpI,},
            {"thresholdDownI",thresholdDownI,},
            {"rfid",RFID,},
            {"warehouseName",warehouseName,},
            {"time",time,}
        };

        QJsonObject station
        {
            {globalid,value},
        };
        stationNode << station;
    }
    else qDebug()<<"select not success";
    }
    station = QJsonDocument(stationNode).toJson(QJsonDocument::Compact);

    qDebug().noquote()<< station;
    sendJsonStationPackage(station);
}


//
void encodejson::sendJsonDataPackage(QByteArray data)
{

    QUrl url("http://119.17.254.105:82/iot/updateData.php");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QNetworkReply *reply = manager->post(request, data);
    while (!reply -> isFinished()) {
        qApp->processEvents();
    }
    updateIsSentColumn();
    QString numofUnSendPackage = identifyConnectionTimeOut();
    if (numofUnSendPackage != '0')
    {
       encodejsonpackageDataNode();
    }
    QByteArray response_data = reply->readAll();
    qDebug()<<response_data;

}


//
void encodejson::sendJsonStationPackage(QByteArray station)
{
    QUrl url("http://119.17.254.105:82/iot/updateStation.php");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QNetworkReply *reply = manager->post(request, station);
   // while (!reply -> isFinished()) {
     //   qDebug()<<"send success";
    //}

}
