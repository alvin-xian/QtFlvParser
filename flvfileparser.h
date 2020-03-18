#ifndef FLVFILEPARSER_H
#define FLVFILEPARSER_H

#include <QObject>
#include "itag.h"
#include <QFile>
#include "flvaudiotag.h"
#include "flvavctag.h"
#include "flvheader.h"
#include "flvvideotag.h"
#include "flvscripttag.h"

class FlvFileParser : public QObject
{
    Q_OBJECT
public:
    explicit FlvFileParser(QObject *parent = 0);
    void open(const QString &filePath);
    FlvHeader *header() const;
    QList<ITag *> packagets() const;
private:
    QList<ITag *> m_packagets;//所有解析出来的包
    FlvHeader *m_flvHeader = Q_NULLPTR;
    QFile *m_flvFile = Q_NULLPTR;
    QString m_flvFilePath;
private:
    void parserHeader();
    void parserAllTag();

    ITag *getOneTag(QByteArray &data);
signals:
    void sigDone();
public slots:
};

#endif // FLVFILEPARSER_H
