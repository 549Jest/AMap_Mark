#pragma execution_character_set("utf-8")//防止中文乱码
#include "jswebbridge.h"
JSWebBridge::JSWebBridge(QObject *parent) : QObject(parent)
{

}

QString JSWebBridge::GetAMapAuthorName()
{
    return "AuthorName:Jest";
}


void JSWebBridge::GetPointLatLngFromAMap(const QString lat,const QString lng)
{
   qDebug()<<"来自web标记点输出" <<"维度"<<lat<<","<<"经度"<<lng;
}
