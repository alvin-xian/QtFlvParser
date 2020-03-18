#include "flvvideotag.h"

FlvVideoTag::FlvVideoTag(const QByteArray &raw):ITag(raw)
{

}

/**
    /----视频参数8bit----------/
    /--4bit---/---4bit-------/
    /--帧类型--/--视频编码类型--/-视频数据 n bit-/
    /p帧->0010-/
    /I帧->0001-/
**/
/**
 * @brief FlvVideoTag::codeType
 * 紧接着header之后的第一个字节的前四位
 * @return
 */
FlvVideoTag::VideoFrame FlvVideoTag::frameType() const
{
    return VideoFrame((m_rawData.at(11)>>4)&0x0f);
}

/**
 * @brief FlvVideoTag::codeType
 * 紧接着header之后的第一个字节的后四位
 * @return
 */
FlvVideoTag::VideoCode FlvVideoTag::codeType() const
{
    return VideoCode(m_rawData.at(11)&0x0f);
}



