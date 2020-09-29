#include <iostream>
#include "RegistrarApp/RegistrarApp.hpp"
#include "Overlay/OverlayRepository.hpp"

int main(int argc, const char **argv) {
    overlay::OverlayRepository *overlayRepository = new overlay::OverlayRepository;
    app::registrar::RegistrarApp app(&argc, &argv, overlayRepository);
    delete overlayRepository;
    return 0;
}
