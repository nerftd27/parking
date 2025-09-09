#pragma once

#include "interfaces.h"
#include "thirdpartyAdapters.h"
#include "accountingDB.h"

//#include <chrono>
#include <memory>
//#include <unordered_map>

namespace BrakeParking {

class Accounting : public IAccounting{
public:
    Accounting()
        : m_payment(new PaymentSystemAdapter())
        , m_db(new AccountingDB()){
    }

    ~Accounting() {
        m_db->Print();
    }

public:
    bool MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber) override;
    bool MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber) override;

private:
    std::unique_ptr<IAccountingDB> m_db;
    std::unique_ptr<IPaymentSystem> m_payment;  
};

} // namespace BrakeParking