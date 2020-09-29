#include <gtk/gtk.h>
#include "ReceiverApp/ReceiverApp.hpp"
#include "Overlay/OverlayRepository.hpp"

int main(int argc, const char **argv) {
    overlay::OverlayRepository *overlayRepository = new overlay::OverlayRepository;
    app::receiver::ReceiverApp app(&argc, &argv, overlayRepository);
    delete overlayRepository;
    return 0;
}
