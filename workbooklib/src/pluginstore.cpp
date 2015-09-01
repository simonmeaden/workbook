/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#include "qstd.h"

#include "pluginstore.h"

bool PluginStore::pluginsAreLoaded = false;

PluginStore::PluginStore(QObject *parent) : QObject(parent) {
    loadPlugins();
}

PluginStore::~PluginStore() {

}

bool PluginStore::isEmpty() {
    return (mOperators.isEmpty() && mFunctions.isEmpty() && mConstants.isEmpty());
}

IOperator *PluginStore::getOperator(QString name) {
    if (mOperators.contains(name))
        return mOperators.value(name);
    return NULL;
}

IFunction* PluginStore::getFunction(QString name) {
    if (mFunctions.contains(name))
        return mFunctions.value(name);
    return NULL;
}

IConstant* PluginStore::getConstant(QString name) {
    if (mConstants.contains(name))
        return mConstants.value(name);
    return NULL;
}

void PluginStore::addOperator(IOperator *interface) {
    mOperators.insert(interface->name(), interface);
}

void PluginStore::addFunction(IFunction *interface) {
    mFunctions.insert(interface->name(), interface);
}
void PluginStore::addConstant(IConstant *interface) {
    mConstants.insert(interface->name(), interface);
}

void PluginStore::loadPlugins() {

    // only need to be loaded once.
    if (PluginStore::pluginsAreLoaded) return;

    QDir pluginsDir = QDir(qApp->applicationDirPath());

    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {

            IOperator *opInterface = qobject_cast<IOperator*>(plugin);
            if (opInterface) {
                addOperator(opInterface);
//                cout << "Plugin file " << opInterface->name() << " is valid." << endl;
                // now the plugin can be initialized and used
            }

            IConstant *conInterface = qobject_cast<IConstant*>(plugin);
            if (conInterface) {
                // now the plugin can be initialized and used
                addConstant(conInterface);
//                cout << "Plugin file " << conInterface->name() << " is valid." << endl;
            }

            IFunction *func = qobject_cast<IFunction*>(plugin);
            if (func) {
                // now the plugin can be initialized and used
                addFunction(func);
//                cout << "Plugin file " << func->name() << " is valid." << endl;
            }

        }
    }

    PluginStore::pluginsAreLoaded = true;
}
