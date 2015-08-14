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

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += ../QRODS
LIBS  += -L../build-QRODS-Desktop_Qt_5_4_1_GCC_64bit-Debug -lQRODS

DISTFILES += \
README \
config.ini \
log.txt

message(Building the Tests)
QT += testlib
TARGET = runTests

SOURCES -= main.cpp

HEADERS += testfilecontentclient.h\
           collectionclientsync.h \
           testdataobjectclient.h \
           testcollectionclient.h\
           dataobjectclientasync.h

SOURCES += main.cpp \
    testfilecontentclient.cpp \
    collectionclientsync.cpp \
    testdataobjectclient.cpp \
    testcollectionclient.cpp \
    dataobjectclientasync.cpp

