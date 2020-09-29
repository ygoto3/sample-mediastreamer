#include "RegistrarApp/RegistrarApp.hpp"
#include "Overlay/Overlay.hpp"
#include <iostream>

namespace app::registrar {
    
    RegistrarApp::RegistrarApp(int *argc, const char ***argv, overlay::IOverlayRepository *artistRepository) {
        this->artistRepository = artistRepository;
        gtk_init(argc, const_cast<char ***>(argv));
        app_init(argc, argv);
    }
    
    RegistrarApp::~RegistrarApp() {
    }
    
    void RegistrarApp::on_activate(GtkApplication *application, RegistrarApp *app) {
        app->window = gtk_application_window_new(application);
        gtk_window_set_default_size(GTK_WINDOW(app->window), 300, 200);
        gtk_window_set_title(GTK_WINDOW(app->window), "Registrar");
        app->create_ui();
        gtk_widget_show_all(app->window);
    }
    
    void RegistrarApp::on_submit_button_click(GtkWidget *widget, RegistrarApp *app) {
        using namespace overlay;
        int num = ((char *)gtk_entry_get_text(GTK_ENTRY(app->id_entry)))[0] - '0';
        const gchar *text = gtk_entry_get_text(GTK_ENTRY(app->text_entry));
        Overlay overlay{OverlayId(num), OverlayText(text)};
        app->artistRepository->Update(overlay);
    }
    
    int RegistrarApp::app_init(int *argc, const char ***argv) {
        application = gtk_application_new("com.ygoto3.sample-mediastreamer.registrar", G_APPLICATION_FLAGS_NONE);
        g_signal_connect(application, "activate", G_CALLBACK(on_activate), this);
        int status = g_application_run(G_APPLICATION(application), *argc, const_cast<char **>(*argv));
        g_object_unref(application);
        return status;
    }
    
    int RegistrarApp::create_ui() {
        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
        id_entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(id_entry), "1");
        text_entry = gtk_entry_new();
        GtkWidget *submit_button = gtk_button_new_with_label("register");
        g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_button_click), this);
        gtk_box_pack_start(GTK_BOX(hbox), id_entry, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), text_entry, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), submit_button, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(window), vbox);
    }

}
