#ifndef REGEX_H
#define REGEX_H



/*
 * REGEX_CELL_REFERENCE_1 matches an entire string, from start of string to end of string.
 * It can have
 * 0 or 1 $
 * 1 or 2 letters A-Z a-z
 * 1 number 1 - 9
 * 0 - 2 numbers 0 - 9
 * Basically an optional static column character ($), a one or two character column descriptor (A - ZZ), an
 * optional static row character ($) and a one to three character row descriptor (1 to 999).
 *
 * There is almost certainly a better way to do this but I am not in any way a Regex expert.
 */
#define REGEX_CELL_REFERENCE_1      "^\\${0,1}([A-Za-z][A-Za-z]|[A-Za-z])\\${0,1}([1-9][0-9][0-9]|[1-9][0-9]|[0-9])$"
/*
 * Same as REGEX_CELL_REFERENCE_1 except not whole string match.
 */
#define REGEX_CELL_REFERENCE_2      "\\${0,1}([A-Za-z][A-Za-z]|[A-Za-z])\\${0,1}([1-9][0-9][0-9]|[1-9][0-9]|[0-9])"

/*
 * These are only used AFTER the cell reference has been verified by REGEX_CELL_REFERENCE
 * so they don't need to be so perfect.
 */
#define REGEX_NO_STATIC             "^[A-Za-z]{1,2}[1-9][0-9]{0,2}$"
#define REGEX_NO_STATIC_SPLIT       "[A-Za-z]{1,2}|[1-9][0-9]{0,2}"
#define REGEX_COLUMN_STATIC         "^\\$[A-Za-z]{1,2}[1-9][0-9]{0,2}$"
#define REGEX_COLUMN_STATIC_SPLIT   "\\$|[A-Za-z]{1,2}|[1-9][0-9]{0,2}"
#define REGEX_ROW_STATIC            "^[A-Za-z]{1,2}\\$[1-9][0-9]{0,2}$"
#define REGEX_ROW_STATIC_SPLIT      "[A-Za-z]{1,2}|\\$|[1-9][0-9]{0,2}"
#define REGEX_BOTH_STATIC           "^\\$[A-Za-z]{1,2}\\$[1-9][0-9]{0,2}$"
#define REGEX_BOTH_STATIC_SPLIT     "\\$|[A-Za-z]{1,2}|[1-9][0-9]{0,2}"

#define REGEX_ROW                   "\\d+"
#define REGEX_COLUMN                "[A-Za-z]{1,3}?"

#define REGEX_SPLIT_CELL_REFERENCE  "(\\$?|\\d+|[A-Za-z]{1,3}?)"


#define CellReferenceRegex          REGEX_CELL_REFERENCE_1
#define ScientificNumberRegex       "((\\b[0-9]+)?\\.)?\\b[0-9]+([eE][-+]?[0-9]+)?\\b"
#define HexNumberRegex              "\\b0[xX][0-9a-fA-F]+\\b"
#define MatchedParenthesisRegex     "((?>[^()]|(?R))*"
#define NumbersRegex                "[+-]?([0-9]*\\.?[0-9]+|[0-9]+\\.?[0-9]*)([eE][+-]?[0-9]+)?"

#endif // REGEX_H

