#ifndef FLVAVCTAG_H
#define FLVAVCTAG_H

#include "itag.h"
/**
 * @brief The FlvAvcTag class
 * 存放SPS&PPS
 */
class FlvAvcTag:public ITag
{
    Q_OBJECT
public:
    FlvAvcTag(const QByteArray &raw);
    virtual Type type(){return Flv_AVCProfileIndicationTag;}
};

#endif // FLVAVCTAG_H
