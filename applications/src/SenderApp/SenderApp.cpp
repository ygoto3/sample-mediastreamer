#include <gtk/gtk.h>
#include <gst/gst.h>
#include "SenderApp/SenderApp.hpp"

namespace app::sender {
    
    SenderApp::SenderApp(int *argc, const char ***argv) {
        gtk_init(argc, const_cast<char ***>(argv));
        gst_init(argc, const_cast<char ***>(argv));
        app_init(argc, argv);
    }
    
    SenderApp::~SenderApp() {
        g_object_unref(application);
    }
    
    void SenderApp::on_activate(GtkApplication *application, SenderApp *app) {
        app->window = gtk_application_window_new(application);
        gtk_window_set_title(GTK_WINDOW(app->window), "Sender");
        gtk_window_set_default_size(GTK_WINDOW(app->window), 300, 200);
        app->create_ui();
        gtk_widget_show_all(app->window);
    }
    
    void SenderApp::on_start_button_click(GtkWidget *widget, SenderApp *app) {
        const char *host = gtk_entry_get_text(GTK_ENTRY(app->host_entry));
        const char *port = gtk_entry_get_text(GTK_ENTRY(app->port_entry));
        app->mediaPlayer = new framework::media::MediaStreamer(framework::media::MEDIA_STREAMER_SEND, host, atoi(port));
        app->mediaPlayer->Load();
    }
    
    void SenderApp::app_init(int *argc, const char ***argv) {
        create_app(argc, argv);
    }
    
    int SenderApp::create_app(int *argc, const char ***argv) {
        application = gtk_application_new("com.ygoto3.sample-mediastreamer.sender", G_APPLICATION_FLAGS_NONE);
        g_signal_connect(application, "activate", G_CALLBACK(on_activate), this);
        int status = g_application_run(G_APPLICATION(application), *argc, const_cast<char **>(*argv));
        g_object_unref(application);
        return status;
    }
    
    void SenderApp::create_ui() {
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
        host_entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(host_entry), "127.0.0.1");
        port_entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(port_entry), "5000");
        gtk_box_pack_start(GTK_BOX(hbox), host_entry, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), port_entry, FALSE, TRUE, 0);
        
        GtkWidget *start_button = gtk_button_new_with_label("send");
        g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_button_click), this);
        
        gtk_box_pack_start(GTK_BOX(box), hbox, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(box), start_button, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(window), box);
    }
    
}

