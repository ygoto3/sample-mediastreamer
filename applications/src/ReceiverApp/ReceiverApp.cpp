#include "ReceiverApp/ReceiverApp.hpp"

namespace app::receiver {

    ReceiverApp::ReceiverApp(int *argc, const char ***argv, overlay::IOverlayRepository *overlayRepository) {
        this->overlayRepository = overlayRepository;
        gtk_init(argc, const_cast<char ***>(argv));
        gst_init(argc, const_cast<char ***>(argv));
        app_init(argc, argv);
    }
    
    ReceiverApp::~ReceiverApp() {
    }

    void ReceiverApp::on_activate(GtkApplication *application, ReceiverApp *app) {
        app->window = gtk_application_window_new(application);
        gtk_window_set_title(GTK_WINDOW(app->window), "Receiver");
        gtk_window_set_default_size(GTK_WINDOW(app->window), 300, 200);
        app->create_ui();
        gtk_widget_show_all(app->window);
    }

    void ReceiverApp::on_key_press(GtkWidget *widget, GdkEventKey *event, ReceiverApp *app) {
        int id;
        switch (event->keyval) {
            case GDK_KEY_1:
                id = 1;
                break;
            case GDK_KEY_2:
                id = 2;
                break;
            case GDK_KEY_3:
                id = 3;
                break;
            case GDK_KEY_4:
                id = 4;
                break;
            case GDK_KEY_5:
                id = 5;
                break;
            case GDK_KEY_6:
                id = 6;
                break;
            case GDK_KEY_7:
                id = 7;
                break;
            case GDK_KEY_8:
                id = 8;
                break;
            case GDK_KEY_9:
                id = 9;
                break;
            default:
                id = 1;
                break;
        }
        
        overlay::Overlay overlay = app->overlayRepository->Get(overlay::OverlayId(id)).get();
        app->mediaStreamer->Change(overlay.getText().getValue());
    }

    void ReceiverApp::on_receive_button_click(GtkWidget *button, ReceiverApp *app) {
        const char *port = gtk_entry_get_text(GTK_ENTRY(app->port_entry));
        app->mediaStreamer = new framework::media::MediaStreamer(framework::media::MEDIA_STREAMER_RECEIVE, "", atoi(port));
        app->mediaStreamer->Load();
    }

    int ReceiverApp::app_init(int *argc, const char ***argv) {
        application = gtk_application_new("com.ygoto3.sample-mediastreamer.receiver", G_APPLICATION_FLAGS_NONE);
        g_signal_connect(application, "activate", G_CALLBACK(on_activate), this);
        int status = g_application_run(G_APPLICATION(application), *argc, const_cast<char **>(*argv));
        g_object_unref(application);
        return status;
    }
    
    void ReceiverApp::create_ui() {
        gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        port_entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(port_entry), "5000");
        receive_button = gtk_button_new_with_label("receive");
        g_signal_connect(receive_button, "clicked", G_CALLBACK(on_receive_button_click), this);
        g_signal_connect(window, "key_press_event", G_CALLBACK(on_key_press), this);
        gtk_box_pack_start(GTK_BOX(vbox), port_entry, FALSE, FALSE, 1);
        gtk_box_pack_start(GTK_BOX(vbox), receive_button, FALSE, FALSE, 1);
        gtk_container_add(GTK_CONTAINER(window), vbox);
    }

}
