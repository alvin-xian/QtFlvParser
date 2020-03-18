#ifndef FLVPACKAGETINTERFACE_H
#define FLVPACKAGETINTERFACE_H

#include <QObject>
#include <QMetaEnum>
#include <QDebug>
/**
 * @brief The ITag class
 * flv Tag interface
 */
class ITag:public QObject
{
    Q_OBJECT
public:
    explicit ITag(const QByteArray &raw);
    Q_ENUMS(Type)
    enum Type{
        Flv_ScriptTag,
        Flv_AVCProfileIndicationTag,
        Flv_AudioTag,
        Flv_VideoTag,
    };
    QString getTypeStr(Type t){
        switch (t) {
        case Flv_ScriptTag:
            return "Script";
            break;
        case Flv_AVCProfileIndicationTag:
            return "AVCProfileIndication";
            break;
        case Flv_AudioTag:
            return "Audio";
            break;
        case Flv_VideoTag:
            return "Video";
            break;
        default:
            return "";
        }
    }
    typedef unsigned char uint24[3];
    //11个字节的tagheader

#pragma pack(1)
    struct TagHeader{
        char type;
        uint24 size;
        uint24 timestamp;
        char timestamp_ex;
        uint24 steamid;
        TagHeader &operator =(const TagHeader &other){
            this->type = other.type;
            memcpy(this->size, other.size, sizeof(uint24));
            memcpy(this->timestamp, other.timestamp, sizeof(uint24));
            memcpy(this->steamid, other.steamid, sizeof(uint24));
            this->timestamp_ex = other.timestamp_ex;
            return *this;
        }
    };
    static quint32 uint24ToInt(uint24 d){
        return d[0]*(1<<16)+d[1]*(1<<8)+d[2];
    }

    virtual Type type() = 0;
    virtual quint32 size();
    virtual quint32 metaDataSize(){return size() - 11;}
    quint32 timeStamp() const;
    quint32 steamid();

    static ITag *CreateTag(const QByteArray &raw);
    static TagHeader peekTagHeader(const QByteArray &raw);
protected:
    QByteArray m_rawData;
    TagHeader m_header;
};

#endif // FLVPACKAGETINTERFACE_H
