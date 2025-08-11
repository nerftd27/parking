#pragma once

#include <vector>

namespace BrakeParking {

typedef unsigned int VehicleNumberType;
typedef unsigned int BarrierIdType;
typedef unsigned int AreaIdType;

class IArea {
public:
    virtual unsigned int GetId() const = 0;
    virtual bool EmplaceVehicle(VehicleNumberType vehicleNumber) = 0;
    virtual bool DeleteVehicle(VehicleNumberType vehicleNumber) = 0;
    virtual unsigned int CheckOccupied() = 0;
};

class IBarrier {
public:
    virtual unsigned int GetId() const = 0;
    virtual void SetSideIn(IArea*) = 0;
    virtual void SetSideOut(IArea*) = 0;
    virtual void VehicleMoveIn(VehicleNumberType vehicleNumber) = 0;
    virtual void VehicleMoveOut(VehicleNumberType vehicleNumber) = 0;
};

class IParking {
public:
    enum class MoveDirection { In, Out };

    virtual void Construct(std::vector<BarrierIdType> barriers) = 0; // передаем список айдишников барьеров, которые мы хотим создать в этом паркинге
    virtual unsigned int CheckOccupied() = 0;

    virtual void VehicleMove(VehicleNumberType vehicleNumber, BarrierIdType barrierId, MoveDirection ) = 0;
};

} // namespace BrakeParking
