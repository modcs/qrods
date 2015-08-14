//The MIT License (MIT)

//Copyright (c) <2015> <CIn-UFPE>

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#ifndef FILECONTENTSCLIENT_H
#define FILECONTENTSCLIENT_H

#include "abstracthttpclient.h"
#include <QNetworkReply>
#include <QString>

class FileContentsClient: public AbstractHTTPClient
{
    Q_OBJECT
public:
    explicit FileContentsClient(QString &baseURL, QString user, QString pass, QObject *parent = 0);

    void uploadFile(QString &remotePath, QString &localPath);
    void getFile(QString &remotePath, QString &localPath);

public slots:
    void replyFinished(QNetworkReply *reply);
private:
    void getFinished(QNetworkReply *reply);
    void postFinished(QNetworkReply *reply);
signals:
    void modelChanged();
};

#endif // FILECONTENTSCLIENT_H
