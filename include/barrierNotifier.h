#pragma once

#include "interfaces.h"

#include <algorithm>
#include <list>

namespace BrakeParking {

class BarrierNotifier : public INotifier {
public:
    virtual ~BarrierNotifier() = default;
public:
    void AddListener(std::shared_ptr<IListener> listener) override {
        m_list.push_back(listener);
    }

    void RemoveListener(std::shared_ptr<IListener> listener) override {
        auto it = std::find(m_list.begin(), m_list.end(), listener);
        if (it != m_list.end())
            m_list.erase(it);
    }

    void Notify(BarrierIdType id,  IParking::MoveDirection md, VehicleNumberType vehicleNumber,std::size_t placeNumber) override {
        for(const auto& listener : m_list) {
            listener->OnNotify(id, md, vehicleNumber, placeNumber);
        }
    }
private:
    std::list<std::shared_ptr<IListener>> m_list;
};

} // namespace BrakeParking