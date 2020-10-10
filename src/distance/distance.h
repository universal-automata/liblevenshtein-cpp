#ifndef __LIBLEVENSHTEIN__DISTANCE__DISTANCE_H__
#define __LIBLEVENSHTEIN__DISTANCE__DISTANCE_H__


template <class Term>
class Distance {
public:
    int between(Term v, Term w);
};


#endif // __LIBLEVENSHTEIN__DISTANCE__DISTANCE_H__
