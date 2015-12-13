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
#include "pluginstore_p.h"
#include "pluginstore.h"

#include "workbook_global.h"

namespace QWorkbook {

PluginStorePrivate::PluginStorePrivate(PluginStore *parent) :
    q_ptr(parent) {

    loadPlugins();

}

IOperator* PluginStorePrivate::getOperator(QString name) {
    if (mOperators.contains(name))
        return mOperators.value(name);
    return NULL;
}

IFunction* PluginStorePrivate::getFunction(QString name) {
    if (mFunctions.contains(name))
        return mFunctions.value(name);
    return NULL;
}

IConstant* PluginStorePrivate::getConstant(QString name) {
    if (mConstants.contains(name))
        return mConstants.value(name);
    return NULL;
}

bool PluginStorePrivate::isEmpty() {
    return (mOperators.isEmpty() && mFunctions.isEmpty() && mConstants.isEmpty());
}

void PluginStorePrivate::addOperator(IOperator* interface) {
    mOperators.insert(interface->name(), interface);
    mOperatorNames.append(interface->name());
}

void PluginStorePrivate::addFunction(IFunction* interface) {
    mFunctions.insert(interface->name(), interface);
    mFunctionNames.append(interface->name());
}

void PluginStorePrivate::addConstant(IConstant* interface) {
    mConstants.insert(interface->name(), interface);
    mConstantNames.append(interface->name());
}

QStringList PluginStorePrivate::functionNames() {
    return mFunctionNames;
}

QStringList PluginStorePrivate::operatorNames() {
    return mOperatorNames;
}

QStringList PluginStorePrivate::constantNames() {
    return mConstantNames;
}

void PluginStorePrivate::loadPlugins() {

    QDir pluginsDir = QDir(qApp->applicationDirPath() + "/plugins");

    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {

            IOperator *opInterface = qobject_cast<IOperator*>(plugin);
            if (opInterface) {
                addOperator(opInterface);
//                qDebug() << "Plugin file " << opInterface->name() << " is valid.";
                // now the plugin can be initialized and used
            }

            IConstant *conInterface = qobject_cast<IConstant*>(plugin);
            if (conInterface) {
                // now the plugin can be initialized and used
                addConstant(conInterface);
//                qDebug() << "Plugin file " << conInterface->name() << " is valid.";
            }

            IFunction *func = qobject_cast<IFunction*>(plugin);
            if (func) {
                // now the plugin can be initialized and used
                addFunction(func);
//                qDebug() << "Plugin file " << func->name() << " is valid.";
            }

        }
    }

}

} // end namespace QWorkbook

