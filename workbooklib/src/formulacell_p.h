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
#ifndef FORMULACELLPRIVATE_H
#define FORMULACELLPRIVATE_H

#include "types.h"
#include "mergedcell.h"
#include "mergedcell_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class FormulaCell;

class FormulaCellPrivate : public MergedCellPrivate {

public:

    virtual ~FormulaCellPrivate() {}

};


}

#endif // FORMULACELLPRIVATE_H
