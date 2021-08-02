#include <tower/Wall.h>

#include <Coordinate.h>
#include <Gui.h>

namespace termd {

CWall::CWall()
    : mCost(3)
    , mGraphic('#')
{
}

int CWall::getCost() const
{
    return mCost;
}

int CWall::getSellValue() const
{
    return mCost / 2;
}

char CWall::getGraphic() const
{
    return mGraphic;
}

bool CWall::update(
    std::function<void(std::unique_ptr<IProjectile>&& projectile)> /* spawnProjectile */,
    const std::vector<std::unique_ptr<CVirus>>& /* viruses */,
    const std::map<CCoordinate, std::vector<std::reference_wrapper<std::unique_ptr<CVirus>>>>& /* virusMap */
)
{
    return true;
}

void CWall::updateEndOfWave() { }

}
