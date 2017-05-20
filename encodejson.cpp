#include "encodejson.h"
#include <QJsonObject>
#include<QJsonDocument>
#include<QDebug>
#include <QJsonArray>
#include <QString>
#include <QSqlQuery>
#include <QDateTime>

encodejson::encodejson()
{

}
//encode json package
void encodejson::encodejsonpackage(QString rfid,double pressure, double current, double voltage)
{
    QJsonObject value{
        {"pressure", pressure,},
        {"current",current,},
        {"voltage",voltage,},
        {"rfid",rfid,}
    };
    QJsonObject pump
    {
        {"sdcsAddr",1,},
        {"value",value,}

    };

    QJsonDocument doc(pump);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    QString jsonString(data);
    qDebug().noquote()<< data;

}
// create RFID table in Local Database
void encodejson::createRFIDtable(QString tablename)
{
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE IF NOT EXISTS "+tablename+"( Time DATETIME NOT NULL, Pressure DOUBLE NULL,Voltage DOUBLE NULL, Current DOUBLE NULL, PRIMARY KEY (Time), UNIQUE INDEX Time_UNIQUE (Time ASC)) ENGINE = InnoDB"));
    if(query.exec())
        {
            qDebug()<<"table created";
        }
        else
        {
            qDebug()<<"table is not created";
        }
}
//insert data to RFID table in Local Database
void encodejson::insertRFIDtabletoDatabase(QString RFID, double Pressure, double Voltage, double Current)
{
    QSqlQuery query;
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("INSERT INTO "+RFID+" (Time, Pressure,Voltage,Current) "
                    "VALUES (?, ?, ?, ?)");
    query.bindValue(0,dateTimeString);
    query.bindValue(1,Pressure);
    query.bindValue(2,Voltage);
    query.bindValue(3,Current);
    if(query.exec())
        {
            qDebug()<<"insert successful";
        }
        else
        {
            qDebug()<<"insert not successful";
        }
}

// insert RFID to rfids table : check RFID exist, if RFID not exist, insert RFID to rfids table - create RFID table
// in Local Database - insert data to RFID table, else insert data to RFID table
void encodejson::insertRFIDtorfidsTable(QString RFID, double pressure, double voltage, double current)
{
    QSqlQuery query,query1;
    QString total;
    query.prepare("SELECT COUNT(*) FROM rfids WHERE RFID = ?");
    query.addBindValue(RFID);
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
    if(total=="0")
    {

        query1.prepare("INSERT INTO rfids (RFID) "
                       "VALUES (?)");
        query1.addBindValue(RFID);
        if(query1.exec()) qDebug()<<"insert rfid to rfids success";
        else qDebug()<<"insert rfid to rfids not success";
        createRFIDtable(RFID);
        insertRFIDtabletoDatabase(RFID,pressure,voltage,current);
    }else
    {
        insertRFIDtabletoDatabase(RFID,pressure,voltage,current);
    }
}

// insert RFID to stations table: check pumpAddr, pumpCH, sdcsAddr, sdcsCH and warehouseName
// to override RFID in stations table
void encodejson::insertRFIDtoStationTable(QString RFID, int pumpAddr, int pumpCH, int sdcsAddr, int sdcsCH, QString warehouseName)
{
    QSqlQuery query;
    query.prepare("UPDATE stations SET RFID = ? WHERE pumpAddr = ? AND pumpCH = ? AND sdcsAddr = ? AND sdcsCH = ? AND warehouseName = ?");
    query.bindValue(0,RFID);
    query.bindValue(1,pumpAddr);
    query.bindValue(2,pumpCH);
    query.bindValue(3,sdcsAddr);
    query.bindValue(4,sdcsCH);
    query.bindValue(5,warehouseName);
    if(query.exec())
        {
            qDebug()<<"update RFID in stations Table successful";
        }
        else
        {
            qDebug()<<"update RFID in stations Table not successful";
        }
}
