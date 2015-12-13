
#include <QString>

#include "types.h"

enum Type {
	Double,	
	String,
};

struct Token {
    QWorkbook::ParserError error;
	Type type;
	double dValue;
	QString sValue;
	
	void setValue(double value) {
		type = Double;
		dValue = value;
	}
	void setValue(QString value) {
		type = String;
		sValue = value;
	}
	QString string() { return sValue; }
	double number() { return dValue; }
}
