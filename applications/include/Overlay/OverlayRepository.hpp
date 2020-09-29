#ifndef OverlayRepository_h
#define OverlayRepository_h

#include <future>
#include "IOverlayRepository.hpp"
#include "Overlay/Overlay.hpp"

namespace overlay {

class OverlayRepository : public IOverlayRepository {
public:
    virtual std::future<overlay::Overlay> Get(overlay::OverlayId id);
    virtual std::future<int> Update(overlay::Overlay overlay);
};

}

#endif /* OverlayRepository_h */
