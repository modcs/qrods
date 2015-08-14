#The MIT License (MIT)

#Copyright (c) <2015> <CIn-UFPE>

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

QT       += core gui widgets network xml

TARGET = QRODS
TEMPLATE = lib

CONFIG  += c++11

DEFINES += QRODS_LIBRARY

SOURCES += qrods.cpp \
    abstracthttpclient.cpp \
    callcontroller.cpp \
    collectionclient.cpp \
    dataobjectclient.cpp \
    dataobjectdata.cpp \
    filecontentsclient.cpp \
    filelistingentry.cpp \
    jsonparser.cpp \
    metadataentry.cpp \
    qmetadatamodel.cpp \
    qmetadatamodel_p.cpp \
    qrods_p.cpp \
    resultsparser.cpp \
    serverinfoclient.cpp \
    xmlparser.cpp

HEADERS += qrods.h\
        qrods_global.h \
    xmlparser.h \
    serverinfoclient.h \
    resultsparser.h \
    qrods_p.h \
    qmetadatamodel_p.h \
    qmetadatamodel.h \
    metadataentry.h \
    jsonparser.h \
    filelistingentry.h \
    filecontentsclient.h \
    dataobjectdata.h \
    dataobjectclient.h \
    collectionclient.h \
    callcontroller.h \
    abstracthttpclient.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
