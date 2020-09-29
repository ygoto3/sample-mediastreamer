#ifndef IOverlayRepository_h
#define IOverlayRepository_h

#include <future>
#include <vector>
#include "Overlay/Overlay.hpp"

namespace overlay {

class IOverlayRepository {
public:
    virtual std::future<overlay::Overlay> Get(overlay::OverlayId id) = 0;
    virtual std::future<int> Update(overlay::Overlay overlay) = 0;
};

}

#endif /* IOverlayRepository_h */
