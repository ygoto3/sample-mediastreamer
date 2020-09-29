#include "Overlay/Overlay.hpp"

namespace overlay {

Overlay::Overlay(OverlayId id, OverlayText text) {
    this->id = id.getValue();
    this->text = text.getValue();
}

OverlayId Overlay::getId() {
    return OverlayId(id);
}

OverlayText Overlay::getText() {
    return OverlayText(text);
}

OverlayId::OverlayId(const long id) {
    if (id > 0 && id < 10) {
        value = id;
    } else {
        value = 1;
    }
}

}
