#ifndef FLVVIDEOTAG_H
#define FLVVIDEOTAG_H

#include "itag.h"
class FlvVideoTag:public ITag
{
    Q_OBJECT
public:
    FlvVideoTag(const QByteArray &raw);
    virtual Type type(){return Flv_VideoTag;}
    enum VideoFrame{
        KeyFrame = 1,//（for AVC，a seekable frame）
        InterFrame = 2,//（for AVC，a nonseekable frame）
        DisposableInterFrame = 3,//（H.263 only）
        GeneratedKeyframe = 4,//（reserved for server use）
        video_info_command_frame = 5,
    };
    VideoFrame frameType() const;
    QString getFrameType(VideoFrame t){
        switch (t) {
        case KeyFrame://关键帧，可重入帧，I帧
            return "KeyFrame";
            break;
        case InterFrame://h264的普通帧,P帧
            return "InterFrame";
            break;
        case DisposableInterFrame:
            return "DisposableInterFrame";
            break;
        case GeneratedKeyframe:
            return "GeneratedKeyframe";
            break;
        case video_info_command_frame:
            return "video_info_command_frame";
            break;
        }
        return "NULL";
    }

    enum VideoCode{
         JPEG = 1,// （currently unused）
         Sorenson_H263 = 2,
         Screen_video = 3,
         On2_VP6 = 4,
         On2_VP6_with_alpha_channel = 5,
         Screen_video_version_2 = 6,
         AVC = 7,
    };

    QString getVideoCodeStr(VideoCode t){
        switch (t) {
        case JPEG:
            return "JPEG";
            break;
        case Sorenson_H263:
            return "Sorenson_H263";
            break;
        case Screen_video:
            return "Screen_video";
            break;
        case On2_VP6:
            return "On2_VP6";
            break;
        case On2_VP6_with_alpha_channel:
            return "On2_VP6_with_alpha_channel";
        case Screen_video_version_2:
            return "Screen_video_version_2";
        case AVC:
            return "AVC";
            break;
        }
        return "NULL";
    }
    VideoCode codeType() const;

};

#endif // FLVVIDEOTAG_H
