#ifndef SenderApp_h
#define SenderApp_h

#include <gtk/gtk.h>
#include "framework/media/MediaStreamer/MediaStreamer.hpp"

namespace app::sender {

    class SenderApp {
    public:
        SenderApp(int *argc, const char ***argv);
        virtual ~SenderApp();
    private:
        static void on_activate(GtkApplication *application, SenderApp *app);
        static void on_start_button_click(GtkWidget *widget, SenderApp *app);
        
        GtkApplication *application;
        GtkWidget *window;
        GtkWidget *host_entry;
        GtkWidget *port_entry;
        framework::media::MediaStreamer *mediaPlayer;
        
        void app_init(int *argc, const char ***argv);
        int create_app(int *argc, const char ***argv);
        void create_ui();
    };

}

#endif /* SenderApp_h */
