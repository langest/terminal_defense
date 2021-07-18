#pragma once

#include <map>
#include <memory>
#include <vector>

namespace termd {

class CCoordinate;
class CVirus;

class IProjectile {
	public:
		virtual ~IProjectile() {};

		virtual const CCoordinate& getPosition() const = 0;
		virtual bool update(const std::map<CCoordinate, std::vector<std::unique_ptr<CVirus>>>& virusMap) = 0;
		virtual char getGraphic() const = 0;
};

}
