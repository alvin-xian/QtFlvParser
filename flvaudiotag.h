#ifndef FLVAUDIOTAG_H
#define FLVAUDIOTAG_H

#include "itag.h"
/**
 * @brief The FlvAudioTag class
 * 暂时不用
 */
class FlvAudioTag: public ITag
{
    Q_OBJECT
public:
    FlvAudioTag(const QByteArray &raw);
    virtual Type type(){return Flv_AudioTag;}
};

#endif // FLVAUDIOTAG_H
