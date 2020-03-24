#ifndef _AREA_H
#define _AREA_H

#include <vector>
#include "basicplugin.h"

using namespace std;

class Area : public QObject, public BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")
#endif
     Q_INTERFACES(BasicPlugin)

 public:

    void onPluginLoad();
    void onObjectAdd();
    void printInfo();

 private:


 };

 #endif
