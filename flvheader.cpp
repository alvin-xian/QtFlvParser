#include "flvheader.h"

FlvHeader::FlvHeader(const QByteArray &raw)
{
    m_rawData = raw;
}

QString FlvHeader::startStr() const
{
    return  m_rawData.left(3);
}

int FlvHeader::version() const
{
    return (int)m_rawData.at(3);
}

bool FlvHeader::hasVideo() const
{
    return m_rawData.at(4)&(1);
}

bool FlvHeader::hasAudio() const
{
    return m_rawData.at(4)&(1<<2);
}
