#ifndef App_h
#define App_h

#include <gtk/gtk.h>
#include <gst/gst.h>
#include "Overlay/IOverlayRepository.hpp"
#include "framework/media/MediaStreamer/MediaStreamer.hpp"

namespace app::receiver {

    class ReceiverApp {
    public:
        ReceiverApp(int *argc, const char ***argv, overlay::IOverlayRepository *overlayRepository);
        ~ReceiverApp();
    private:
        static void on_key_press(GtkWidget *widget, GdkEventKey *event, ReceiverApp *app);
        static void on_receive_button_click(GtkWidget *button, ReceiverApp *app);
        static void on_activate(GtkApplication *application, ReceiverApp *app);
        
        int app_init(int *argc, const char ***argv);
        void create_ui();

        overlay::IOverlayRepository *overlayRepository;
        framework::media::MediaStreamer *mediaStreamer;
        GtkApplication *application;
        GtkWidget *window;
        GtkWidget *vbox;
        GtkWidget *port_entry;
        GtkWidget *receive_button;
    };

}

#endif /* App_h */
