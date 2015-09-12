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
#include "qstd.h"

#include "pluginstore.h"
#include "interface.h"

PluginStore::PluginStore() :
    d_ptr(new PluginStorePrivate(this)) {

}

PluginStore::PluginStore(QObject *parent) :
    QObject(parent),
    d_ptr(new PluginStorePrivate(this)) {

}

PluginStore::~PluginStore() {

}

bool PluginStore::isEmpty() {
    return d_ptr->isEmpty();
}

IOperator *PluginStore::getOperator(QString name) {
    return d_ptr->getOperator(name);
}

IFunction* PluginStore::getFunction(QString name) {
    return d_ptr->getFunction(name);
}

IConstant* PluginStore::getConstant(QString name) {
    return d_ptr->getConstant(name);
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
