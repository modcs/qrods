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


#include "metadataentry.h"

/**
 * This is a constructor for MetadataEntry class.
 *
 * @brief MetadataEntry::MetadataEntry Constructor method.
 * @param attr a string that is the attribute.
 * @param val a string that is the value.
 * @param unt a string that is the unit.
 * @param parent the parent Qt widget.
 */
MetadataEntry::MetadataEntry(QString& attr,QString& val, QString &unt, QObject *parent) :
    QObject(parent),
    _attribute( attr ),
    _value( val ),
    _unit( unt )
{
}

/**
 * Returns the metadata attribute.
 *
 * @brief MetadataEntry::attribute Returns the attribute.
 * @return returns the attribute.
 */
const QString& MetadataEntry::attribute() const{
    return _attribute;
}

/**
 * Returns the metadata value.
 *
 * @brief MetadataEntry::value Returns the value.
 * @return returns the value.
 */
const QString& MetadataEntry::value() const{
    return _value;
}

/**
 * Returns the metadata unit.
 *
 * @brief MetadataEntry::unit Returns the unit
 * @return returns the unit.
 */
const QString& MetadataEntry::unit() const{
    return _unit;
}
