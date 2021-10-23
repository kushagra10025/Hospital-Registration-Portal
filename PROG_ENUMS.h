#ifndef PROG_ENUMS_H
#define PROG_ENUMS_H

#include <iostream>
#include <map>
#include <QString>

enum CONSULTATION_MODE{
    OFFLINE = 0,
    ONLINE = 1,
    LAB_WORK = 2,
    CM_C
};

enum PAYMENT_METHOD{
    CASH = 0,
    CARD = 1,
    UPI = 2,
    PM_C
};

enum PAYMENT_STATUS{
    FULL = 0,
    NONE = 1,
    PARTIAL = 2,
    PS_C
};

struct ConsultationMode{
    std::map<CONSULTATION_MODE, QString> enumMap;
    ConsultationMode(){
        enumMap[CONSULTATION_MODE::OFFLINE] = "OFFLINE";
        enumMap[CONSULTATION_MODE::ONLINE] = "ONLINE";
        enumMap[CONSULTATION_MODE::LAB_WORK]= "LAB_WORK";
    }

    QString getValueForKey(CONSULTATION_MODE key){
        return enumMap[key];
    }
};

struct PaymentMethod{
    std::map<PAYMENT_METHOD, QString> enumMap;
    PaymentMethod(){
        enumMap[PAYMENT_METHOD::CASH] = "CASH";
        enumMap[PAYMENT_METHOD::CARD] = "CARD";
        enumMap[PAYMENT_METHOD::UPI]= "UPI";
    }

    QString getValueForKey(PAYMENT_METHOD key){
        return enumMap[key];
    }
};

struct PaymentStatus{
    std::map<PAYMENT_STATUS, QString> enumMap;
    PaymentStatus(){
        enumMap[PAYMENT_STATUS::FULL] = "FULL";
        enumMap[PAYMENT_STATUS::NONE] = "NONE";
        enumMap[PAYMENT_STATUS::PARTIAL]= "PARTIAL";
    }

    QString getValueForKey(PAYMENT_STATUS key){
        return enumMap[key];
    }
};

#endif // PROG_ENUMS_H
