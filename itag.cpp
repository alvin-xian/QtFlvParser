#include "itag.h"
#include "flvaudiotag.h"
#include "flvavctag.h"
#include "flvheader.h"
#include "flvvideotag.h"
#include "flvscripttag.h"
#include <QDebug>
ITag::ITag(const QByteArray &raw):QObject()
{
    m_rawData = raw;
    m_header = peekTagHeader(raw);
    Q_ASSERT(uint24ToInt(m_header.size) == ( m_rawData.size()-11));
}

quint32 ITag::size(){
    Q_ASSERT(uint24ToInt(m_header.size) == ( m_rawData.size()-11));
    return uint24ToInt(m_header.size)+11;
}

quint32 ITag::timeStamp() const
{
    return m_header.timestamp_ex*(1<<24) + m_header.timestamp[0]*(1<<16) + m_header.timestamp[1]*(1<<8) + m_header.timestamp[2];
}

quint32 ITag::steamid()
{
    return uint24ToInt(m_header.steamid);
}

ITag *ITag::CreateTag(const QByteArray &raw)
{
    TagHeader header = peekTagHeader(raw);
    QByteArray tagData = raw.mid(sizeof(TagHeader));
    switch (header.type) {
    case 0x8:
        qDebug()<<"CreateTag:"<<"get audio tag!";
        return new FlvAudioTag(raw);
        break;
    case 0x9:
        if(tagData.at(0) == 0x17 && tagData.at(1) == 0){
            qDebug()<<"CreateTag:"<<"get avcc tag";
            return new FlvAvcTag(raw);//sps&pps
        }else{
            qDebug()<<"CreateTag:"<<"get video tag!";
            if(tagData.at(0) == 0x17){
                qDebug()<<"CreateTag:"<<"is IDR frame!";
            }else{
                qDebug()<<"CreateTag:"<<"is P frame! [0x"<<QString::number((int)tagData.at(0),16)<<"]";
            }
            return new FlvVideoTag(raw);
        }
        break;
    case 0x12:
        qDebug()<<"CreateTag:"<<"get script tag!";
        return new FlvScriptTag(raw);
        break;
    default:
        break;
    }
    qDebug()<<"CreateTag:error!"<<(int)header.type;
    return Q_NULLPTR;
}

ITag::TagHeader ITag::peekTagHeader(const QByteArray &raw)
{
    TagHeader header;
    Q_ASSERT(sizeof(header) == 11);
    memset(&header, 0, sizeof(header));
    if(raw.size() < sizeof(header)){
        qWarning()<<"peekTagHeader error! raw.size() not enough"<<raw.size();
        return header;
    }
    QByteArray headerarray = raw.left(11);
    memcpy(&header, headerarray.constData(), sizeof(header));
    return header;
}
