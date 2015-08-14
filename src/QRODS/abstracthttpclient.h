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


#ifndef ABSTRACTHTTPCLIENT_H
#define ABSTRACTHTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QByteArray>
#include <QNetworkRequest>

enum HTTPOperation{
    PUT,POST
};

class AbstractHTTPClient : public QObject
{
    Q_OBJECT
public:
    explicit AbstractHTTPClient(QString &baseURL, QString user, QString pass, QObject *parent = 0);
    QString baseURL();

    void setBaseURL(QString &str);
    void setUserName(QString &str);
    void setPassword(QString &str);
    void setContentType(QString &str);

protected:
    QByteArray doGet(QString &url);    
    QByteArray doPut(QString &url, QByteArray &content);
    QByteArray doPost(QString &url, QByteArray &content);
    QByteArray doDelete(QString &url);

    QNetworkReply* doAsyncGet(QString &url);
    QNetworkReply* doAsyncGet(QString &url, const char* accept);

    void prepareRequest(QNetworkRequest &request);

    QNetworkAccessManager *manager;


private:

    QByteArray doHttpOperation(QString &url, QByteArray &content, HTTPOperation op);

    QString _baseURL;
    QString _username;
    QString _password;
    QString _contentType;
signals:

public slots:

};

#endif // ABSTRACTHTTPCLIENT_H
