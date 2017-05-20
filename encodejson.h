#ifndef ENCODEJSON_H
#define ENCODEJSON_H
#include<QString>

class encodejson
{
public:
    encodejson();
    void encodejsonpackage(QString rfid,double pressure, double current, double voltage);
    void createRFIDtable(QString tablename);
    void insertRFIDtabletoDatabase(QString RFID,double pressure,double voltage, double current);
    void insertRFIDtorfidsTable(QString RFID,double pressure,double voltage, double current);
    void insertRFIDtoStationTable(QString RFID, int pumpAddr, int pumpCH, int sdcsAddr, int sdcsCH, QString warehouseName);
};

#endif // ENCODEJSON_H
