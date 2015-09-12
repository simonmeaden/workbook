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
#ifndef PLUGINSTOREPRIVATE
#define PLUGINSTOREPRIVATE

#include <QMap>

#include "interface.h"

class PluginStore;

class PluginStorePrivate {

public:
    PluginStorePrivate(PluginStore *parent) ;

    ~PluginStorePrivate() {}

    IOperator* getOperator(QString name);
    IFunction* getFunction(QString name);
    IConstant* getConstant(QString name);
    bool isEmpty();

    void addOperator(IOperator* interface);
    void addFunction(IFunction* interface);
    void addConstant(IConstant* interface);
    void loadPlugins();

protected:
    QMap<QString, IOperator*> mOperators;
    QMap<QString, IFunction*> mFunctions;
    QMap<QString, IConstant*> mConstants;

    static bool pluginsAreLoaded;

    PluginStore *q_ptr;

private:
    Q_DECLARE_PUBLIC(PluginStore)


};

#endif // PLUGINSTOREPRIVATE

