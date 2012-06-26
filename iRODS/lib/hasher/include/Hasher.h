/* -*- mode: c++; fill-column: 72; c-basic-offset: 4; indent-tabs-mode: nil -*- */

#ifndef _Hasher_H_
#define _Hasher_H_

#include "HashStrategy.h"

#include <string>
#include <vector>

class Hasher
{
public:
    Hasher(void);
    virtual ~Hasher(void);

    unsigned int addStrategy(HashStrategy* strategy) { _strategies.push_back(strategy); return 0; }
    unsigned int listStrategies(std::vector<std::string>& strategies) const;
  
    unsigned int init(void);
    unsigned int update(char const* data, unsigned int size);
    unsigned int digest(const std::string& name, std::string& messageDigest);
    unsigned int catDigest(std::string& messageDigest);
  
private:
    std::vector<HashStrategy*> _strategies;
};

#endif // _Hasher_H_
