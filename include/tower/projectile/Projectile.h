#pragma once

#include <map>
#include <vector>

namespace termd {

class CCoordinate;
class CVirusHandle;

class IProjectile {
public:
    virtual ~IProjectile() {};

    virtual const CCoordinate& getPosition() const = 0;
    virtual bool update(std::map<CCoordinate, std::vector<CVirusHandle>>& virusMap) = 0;
    virtual char getGraphic() const = 0;
};

template <typename T>
struct SProjectileTraits {
};

}
