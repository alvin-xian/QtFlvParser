#ifndef FLVSCRIPTTAG_H
#define FLVSCRIPTTAG_H

#include "itag.h"
class FlvScriptTag:public ITag
{
    Q_OBJECT
public:
    FlvScriptTag(const QByteArray &raw);
    virtual Type type(){return Flv_ScriptTag;}
};

#endif // FLVSCRIPTTAG_H
