/*!
    The lcd & gcm functions are Qt-ised versions of the C code by Louis-Philippe Lessard.
    see http://lplessard.blogspot.ca/2011/11/integer-math.html

    Copyright (c) 2011, Louis-Philippe Lessard
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
    THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
    OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    int main() {

    QTextStream cout;

    QList<quint32> list1, list2;

    list1 << 8 << 9 << 12 << 13 << 39 << 7 << 16 << 24 << 26 << 15;
    list2 << 2 << 4 << 8 << 16 << 32 << 64 << 128 << 256 << 512 << 1024 << 2048;
    quint32 result;

    cout << gcdList(list1) << " : " << gcdList(list2) << " : "  <<  lcmList(list1) <<
    " : "  << lcmList(list2) << flush;

    return result;

    }

*/
#include "ssmath.h"


/*!
    \brief Find the greatest common divisor of 2 numbers

    Returns the greatest common divisor of 2 unsigned integer numbers, a and b.
    See http://en.wikipedia.org/wiki/Greatest_common_divisor
*/
quint32 gcd(quint32 a, quint32 b ) {
    quint32 c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

/*!
    \brief Find the least common multiple of 2 numbers

    Returns the least common multiple of 2 unsigned integer numbers, \d a and \d b.
    See http://en.wikipedia.org/wiki/Least_common_multiple
*/
quint32 lcm(quint32 a, quint32 b) {
    return (b / gcd(a, b) ) * a;
}

/*!
    Find the greatest common divisor of a list of unsigned integer numbers

    Returns the greatest common divisor of an QList of unsigned integer numbers
    See http://en.wikipedia.org/wiki/Greatest_common_divisor
*/
quint32 gcd(QList<quint32> list) {
    quint32 lastGcd, i;
    if(list.size() < 2) return 0;

    lastGcd = gcd(list.at(0), list.at(1));

    for(i=2; i < list.size(); i++) {
        lastGcd = gcd(lastGcd, list.at(i));
    }

    return lastGcd;
}

/*!
    Find the least common multiple of a list of unsigned integer numbers

    Returns the least common multiple of a QList of unsigned integer numbers.
    See http://en.wikipedia.org/wiki/Least_common_multiple
*/
quint32 lcm(QList<quint32> list) {
    quint32 lastLcm, i;

    if(list.size() < 2) return 0;

    lastLcm = lcm(list.at(0), list.at(1));

    for(i=2; i < list.size(); i++) {
        lastLcm = lcm(lastLcm, list.at(i));
    }

    return lastLcm;
}
