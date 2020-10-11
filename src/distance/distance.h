#ifndef __LIBLEVENSHTEIN__DISTANCE__DISTANCE_H__
#define __LIBLEVENSHTEIN__DISTANCE__DISTANCE_H__

#include <string>


class Distance {
public:
    virtual int between(std::string v, std::string w) = 0;
    virtual int operator()(std::string v, std::string w) = 0;
};


#endif // __LIBLEVENSHTEIN__DISTANCE__DISTANCE_H__
