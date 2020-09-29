#ifndef RegistrarApp_h
#define RegistrarApp_h

#include <gtk/gtk.h>
#include "Overlay/IOverlayRepository.hpp"

namespace app::registrar {

    class RegistrarApp {
    public:
        RegistrarApp(int *argc, const char ***argv, overlay::IOverlayRepository *artistRepository);
        virtual ~RegistrarApp();
    private:
        static void on_activate(GtkApplication *application, RegistrarApp *app);
        static void on_submit_button_click(GtkWidget *widget, RegistrarApp *app);
        
        GtkApplication *application;
        GtkWidget *window;
        GtkWidget *id_entry;
        GtkWidget *text_entry;
        overlay::IOverlayRepository *artistRepository;
        
        int app_init(int *argc, const char ***argv);
        int create_ui();
    };

}

#endif /* RegistrarApp_h */
