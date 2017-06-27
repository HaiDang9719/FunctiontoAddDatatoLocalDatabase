#include <QCoreApplication>
#include"encodejson.h"
#include "support_function.h"
#include <QSqlDatabase>
#include<QDebug>
int main(int argc, char *argv[])
{
    encodejson b;
    support_function s;
    QByteArray test = "&vn~0";
    qDebug() << "Original: " << test;
    qDebug() << "Hexcode: " << test.toHex();
    QString RFID = "R"+test.toHex();
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("raspberry");
    db.setUserName("root");
    db.setPassword("root");
    db.setPort(3306);
    if(!db.open())
        qDebug() << "can not connect";
    else qDebug() << "connected";
    //b.createRFIDtable(RFID);
    //s.insertRFIDtabletoDatabase("R166c218e",0.0000000034,200,300);
    //s.deleteControlTable();
    //s.insertRFIDtorfidsTable("R166c218e",100,200,300);
    //b.insertRFIDtoStationTable(RFID,4,3,5,6,"ok");
    //b.identifyConnectionTimeOut();
    //b.updateIsSentColumn();
    b.encodejsonpackageDataNode();

    //b.encodejsonpackageStationNode();
    return a.exec();
}
