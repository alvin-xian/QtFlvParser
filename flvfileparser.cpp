#include "flvfileparser.h"
#include <QDebug>
FlvFileParser::FlvFileParser(QObject *parent) : QObject(parent)
{

}

void FlvFileParser::open(const QString &filePath)
{
    if(!QFile::exists(filePath)){
        return;
    }
    m_flvFile = new QFile(filePath);
    m_flvFilePath = filePath;
    if(!m_flvFile->open(QFile::ReadOnly)){
        delete m_flvFile;
        m_flvFile = 0;
        return;
    }
    parserHeader();

    parserAllTag();
}

FlvHeader *FlvFileParser::header() const
{
    return m_flvHeader;
}

QList<ITag *> FlvFileParser::packagets() const
{
    return m_packagets;
}

/**
 * @brief FlvFileParser::parserHeader
 * 获取flv头
 */
void FlvFileParser::parserHeader()
{
#if 1
    QByteArray data = m_flvFile->read(9);
#else
    char datastr[9];
    m_flvFile->read(datastr, 9);
    QByteArray data(datastr, 9);
#endif
    Q_ASSERT(data.count() == 9);
    Q_ASSERT(data.startsWith("flv")||data.startsWith("FLV"));
    m_flvHeader = new FlvHeader(data);
}

void FlvFileParser::parserAllTag()
{
    QByteArray data = m_flvFile->readAll();
    while(1){
        ITag *tag = getOneTag(data);
        if(!tag||m_packagets.size()>3000){
            break;
        }

        m_packagets<<tag;
    }
}

/**
 * @brief bytesToInt
 * @param bytes
 * @return 倒叙
 */
int bytesToInt(QByteArray bytes) {
    int addr = bytes[3] & 0x000000FF;
    addr |= ((bytes[2] << 8) & 0x0000FF00);
    addr |= ((bytes[1] << 16) & 0x00FF0000);
    addr |= ((bytes[0] << 24) & 0xFF000000);
    return addr;
}


ITag *FlvFileParser::getOneTag(QByteArray &data)
{
    if(data.size()< (4+sizeof(ITag::TagHeader))){
        //没有presize+header，那么数据失效
        return Q_NULLPTR;
    }
    //前一个数据的大小，占四个字节
    QByteArray presize = data.mid(0,4);
//    qDebug()<<"tag presize"<<bytesToInt(presize);
    data.remove(0,4);

    //探嗅tag头，获取tag的长度。
    ITag::TagHeader header = ITag::peekTagHeader(data);
//    qDebug()<<"FlvFileParser::getOneTag---->header   type:0x"<<QString::number((qint32)header.type,16)
//          <<"length:"<<(ITag::uint24ToInt(header.size)+11)
//           <<"timestamp:"<<ITag::uint24ToInt(header.timestamp)
//          <<(int)header.timestamp_ex;
    //根据长度获取到一个tag的数据
    Q_ASSERT(sizeof(ITag::TagHeader) == 11);
    QByteArray tagData = data.left(11 + ITag::uint24ToInt(header.size));
    data.remove(0, tagData.size());
    //创建相关tag类，数据不对则创建失败
    ITag *tag = ITag::CreateTag(tagData);
    return tag;
}
