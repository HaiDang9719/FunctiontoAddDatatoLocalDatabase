#include <QCoreApplication>
#include"encodejson.h"
#include <QSqlDatabase>
#include<QDebug>
int main(int argc, char *argv[])
{
    encodejson b;
    QByteArray test = "&vn~0";
    qDebug() << "Original: " << test;
    qDebug() << "Hexcode: " << test.toHex();
    QString RFID = "R"+test.toHex();
    QCoreApplication a(argc, argv);
    b.encodejsonpackage("a3e4453ef",100,100,200);
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
    //b.insertRFIDtabletoDatabase("R9938293",100,200,300);
    //b.insertRFIDtorfidsTable("R9938293",100,200,300);
    b.insertRFIDtoStationTable(RFID,4,3,5,6,"ok");
    return a.exec();
}
