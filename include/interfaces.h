#pragma once

namespace BrakeParking {

class IArea {
public:
    virtual unsigned int GetId() const = 0;
    virtual bool EmplaceVehicle(unsigned int vehicleNumber) = 0;
    virtual bool DeleteVehicle(unsigned int vehicleNumber) = 0;
    virtual unsigned int CheckOccupied() = 0;
};

class IPortal {
public:
    virtual unsigned int GetId() const = 0;
    virtual void SetSideA(IArea*) = 0;
    virtual void SetSideB(IArea*) = 0;
    virtual void VehicleMoveIn(unsigned int vehicleNumber) = 0; // A -> B
    virtual void VehicleMoveOut(unsigned int vehicleNumber) = 0; // B -> A
};

class IParking {
    virtual void Construct() = 0; // потом тут будем опрделять какой конфиг паркинга хотим сделать, количество портов, площадок и тд (стратегия?)
    
    virtual void VehicleMoveIn(unsigned int vehicleNumber, unsigned int portalId = 0) = 0;
    virtual void VehicleMoveOut(unsigned int vehicleNumber, unsigned int portalId = 0) = 0;
};

} // namespace BrakeParking
