#ifndef FLVHEADER_H
#define FLVHEADER_H

#include "itag.h"

class FlvHeader
{
public:
    FlvHeader(const QByteArray &raw);
    QString startStr() const;
    int version() const;
    bool hasVideo() const;
    bool hasAudio() const;
private:
    QByteArray m_rawData;
};

#endif // FLVHEADER_H
