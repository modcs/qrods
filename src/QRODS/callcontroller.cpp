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


#include "callcontroller.h"
#include "QEventLoop"
#include <QTimer>

/**
 * This is a constructor for CallController class.
 *
 * @brief CallController::CallController constructor method.
 * @param parent the parent.
 */
CallController::CallController(QObject *parent) : QObject(parent)
{
    this->isModelReleased = true;
    this->qrods = 0;
}

/**
 * Sets QRODS model.
 *
 * @brief CallController::setQRODS Sets QRODS.
 * @param qrods the qrods value.
 */
void CallController::setQRODS(QRODS* qrods)
{
    this->qrods = qrods;

    connect(qrods, SIGNAL(notifyModelUpdated()),
            this, SLOT(modelReady()));
}

/**
 * This method turns the model ready.
 *
 * @brief CallController::modelReady Turns the model ready.
 */
void CallController::modelReady()
{
    this->isModelReleased = true;
}

/**
 * This method waits for a resource.
 *
 * @brief CallController::waitForResource Waits for a resource.
 */
void CallController::waitForResource()
{
    if(!this->isModelReleased)
    {
        QEventLoop loop;
        QObject::connect(this->qrods, SIGNAL(notifyModelUpdated()), &loop, SLOT(quit()));

        QTimer timeoutTimer;
        timeoutTimer.setSingleShot(true);
        connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));

        timeoutTimer.start(2000);

        loop.exec();
    }

    this->isModelReleased = false;
}

CallController callController;
