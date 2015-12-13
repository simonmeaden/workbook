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


#include "pluginstore.h"
#include "interface.h"

#include "workbook_global.h"

namespace QWorkbook {

PluginStore::PluginStore() :
    d_ptr(new PluginStorePrivate(this)) {

}

PluginStore::PluginStore(QObject *parent) :
    QObject(parent),
    d_ptr(new PluginStorePrivate(this)) {

}

bool PluginStore::isEmpty() {
    return d_ptr->isEmpty();
}

IOperator* PluginStore::getOperator(QString name) {
    return d_ptr->getOperator(name);
}

QStringList PluginStore::operatorNames() {
    return d_ptr->operatorNames();
}

IFunction* PluginStore::getFunction(QString name) {
    return d_ptr->getFunction(name);
}

QStringList PluginStore::functionNames() {
    return d_ptr->functionNames();
}

IConstant* PluginStore::getConstant(QString name) {
    return d_ptr->getConstant(name);
}

QStringList PluginStore::constantNames() {
    return d_ptr->constantNames();
}

void PluginStore::addOperator(IOperator *interface) {
    d_ptr->addOperator(interface);
}

void PluginStore::addFunction(IFunction *interface) {
    d_ptr->addFunction(interface);
}

void PluginStore::addConstant(IConstant *interface) {
    d_ptr->addConstant(interface);
}

void PluginStore::loadPlugins() {
    d_ptr->loadPlugins();
}

}

