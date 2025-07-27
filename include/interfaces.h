#pragma once

namespace BrakeParking {

class IArea;

class IPortal {
public:
    virtual unsigned int GetId() const = 0;
    virtual void SetSideA(IArea*) = 0;
    virtual void SetSideB(IArea*) = 0;
    virtual void VehicleGoForward(unsigned int vehicleNumber) = 0; // A -> B
    virtual void VehicleGoBack(unsigned int vehicleNumber) = 0; // B -> A
};

class IArea {
public:
    virtual void connectPortal(IPortal*) = 0;
    virtual bool EmplaceVehicle(unsigned int vehicleNumber) = 0;
    virtual bool DeleteVehicle(unsigned int vehicleNumber) = 0;
    virtual void CheckFill() = 0; // просто выводит сколько занято ячеек, сколько свободно
};

} // namespace BrakeParking
