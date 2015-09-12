/*
    Copyright © Simon Meaden 2015.

    This file is part of the QWorkbook spreadsheet library.

    QWorkbook is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QWorkbook is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QWorkbook.  If not, see <http://www.gnu.org/licenses/>.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#ifndef PLUGINSTORE_H
#define PLUGINSTORE_H

#include <QObject>
#include <QMap>
#include <QDir>
#include <QtPlugin>
#include <QPluginLoader>
#include <QApplication>
#include <QScopedPointer>

#include "interface.h"
#include "pluginstore_p.h"

class PluginStore : QObject {
    Q_OBJECT
public:
    PluginStore();
    PluginStore(QObject *parent=0);
    ~PluginStore();

    IOperator* getOperator(QString name);
    IFunction* getFunction(QString name);
    IConstant* getConstant(QString name);
    bool isEmpty();

public slots:
    void addOperator(IOperator* interface);
    void addFunction(IFunction* interface);
    void addConstant(IConstant* interface);
    void loadPlugins();

protected:
    PluginStore(PluginStorePrivate &d, QObject *parent) :
        QObject(parent),
        d_ptr(&d) {}
    const QScopedPointer<PluginStorePrivate> d_ptr;

    QMap<QString, IOperator*> mOperators;
    QMap<QString, IFunction*> mFunctions;
    QMap<QString, IConstant*> mConstants;

private:
    Q_DECLARE_PRIVATE(PluginStore)

};



#endif // PLUGINSTORE_H
