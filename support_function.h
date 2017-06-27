#ifndef SUPPORT_FUNCTION_H
#define SUPPORT_FUNCTION_H
#include<QString>
#include <QJsonArray>
class support_function
{
public:
    support_function();
    void createRFIDtable(QString tablename);
    void insertRFIDtabletoDatabase(QString RFID,double pressure,double voltage, double current);
    void insertRFIDtorfidsTable(QString RFID,double pressure,double voltage, double current);
    void insertRFIDtoStationTable(QString RFID, int pumpAddr, int pumpCH, int sdcsAddr, int sdcsCH, QString warehouseName);
    void deleteControlTable();
    void updateSetting();
};

#endif // SUPPORT_FUNCTION_H
