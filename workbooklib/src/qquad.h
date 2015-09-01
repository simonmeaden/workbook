#ifndef QQUAD_H
#define QQUAD_H

#include <QtCore/qglobal.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


template <class T1, class T2, class T3, class T4>
struct QQuad
{
    typedef T1 first_type;
    typedef T2 second_type;
    typedef T3 third_type;
    typedef T4 fourth_type;

    QQuad() : first(), second(), third(), fourth() {}
    QQuad(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) : first(t1), second(t2), third(t3), fourth(t4) {}
    // compiler-generated copy/move ctor/assignment operators are fine!

    T1 first;
    T2 second;
    T3 third;
    T4 fourth;
};

// mark QQuad<T1,T2, T3, T4> as complex/movable/primitive depending on the
// typeinfos of the constituents:
template<class T1, class T2, class T3, class T4>
class QTypeInfo<QQuad<T1, T2, T3, T4> > : public QTypeInfoMerger<QQuad<T1, T2, T3, T4>, T1, T2, T3, T4> {}; // Q_DECLARE_TYPEINFO

template <class T1, class T2, class T3, class T4>
Q_INLINE_TEMPLATE bool operator==(const QQuad<T1, T2, T3, T4> &p1, const QQuad<T1, T2, T3, T4> &p2)
{ return p1.first == p2.first && p1.second == p2.second && p1.third = p2.third && p1.fourth = p2.fourth; }

template <class T1, class T2, class T3, class T4>
Q_INLINE_TEMPLATE bool operator!=(const QQuad<T1, T2, T3, T4> &p1, const QQuad<T1, T2, T3, T4> &p2)
{ return !(p1 == p2); }

template <class T1, class T2, class T3, class T4>
Q_INLINE_TEMPLATE bool operator<(const QQuad<T1, T2, T3, T4> &p1, const QQuad<T1, T2, T3, T4> &p2)
{
//    return p1.first < p2.first || (!(p2.first < p1.first) && p1.second < p2.second);
    return (p1.first < p2.first ||
            (!(p2.first < p1.first) && p1.second < p2.second) ||
            (!(p2.first < p1.first) && !(p2.second < p1.second) && p1.third < p2.third) ||
            (!(p2.first < p1.first) && !(p2.second < p1.second) && !(p1.third < p2.third) && p1.fourth < p2.fourth)
            );
}

template <class T1, class T2, class T3, class T4>
Q_INLINE_TEMPLATE bool operator>(const QQuad<T1, T2, T3, T4> &p1, const QQuad<T1, T2, T3, T4> &p2)
{
    return p2 < p1;
}

template <class T1, class T2, class T3, class T4>
Q_INLINE_TEMPLATE bool operator<=(const QQuad<T1, T2, T3, T4> &p1, const QQuad<T1, T2, T3, T4> &p2)
{
    return !(p2 < p1);
}

template <class T1, class T2, class T3, class T4>
Q_INLINE_TEMPLATE bool operator>=(const QQuad<T1, T2, T3, T4> &p1, const QQuad<T1, T2, T3, T4> &p2)
{
    return !(p1 < p2);
}

template <class T1, class T2, class T3, class T4>
Q_OUTOFLINE_TEMPLATE QQuad<T1, T2, T3, T4> qMakeQuad(const T1 &first, const T2 &second, const T3 &third, const T4 fourth)
{
    return QQuad<T1, T2, T3, T4>(first, second, third, fourth);
}

QT_END_NAMESPACE

QT_END_HEADER

#endif // QQUAD_H
