#include "framework/media/MediaStreamer/MediaStreamer.hpp"

namespace framework::media {

    MediaStreamer::MediaStreamer() {
    }
    
    MediaStreamer::MediaStreamer(MediaStreamerType type, std::string host, int port) {
        switch (type) {
            case MEDIA_STREAMER_SEND:
                init_sender(host, port);
                break;
            case MEDIA_STREAMER_RECEIVE:
                init_receiver(port);
                break;
        }
    }
    
    MediaStreamer::~MediaStreamer() {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }
    
    void MediaStreamer::Load() {
        GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
        if (ret == GST_STATE_CHANGE_FAILURE) {
            gst_element_set_state(pipeline, GST_STATE_NULL);
            g_printerr("Failed to change states to GST_STATE_PLAYING.");
        }
    }
    
    void MediaStreamer::Change(std::string text) {
        g_object_set(textoverlay, "text", text.c_str(), NULL);
    }
    
    void MediaStreamer::init_sender(std::string host, int port) {
        pipeline = gst_pipeline_new("mediastreamer-sender-pipeline");
        
        source = gst_element_factory_make("autovideosrc", "sender_source");
                
        GstElement *encode = gst_element_factory_make("x264enc", "sender_encode");
        
        GstCaps *filter = gst_caps_from_string("video/x-h264, stream-format=byte-stream");
        
        GstElement *payload = gst_element_factory_make("rtph264pay", "sender_pay");
        
        GstElement *sink = gst_element_factory_make("udpsink", "sender_sink");
        g_object_set(sink, "host", host.c_str(), "port", port, NULL);
        
        gst_bin_add_many(GST_BIN(pipeline), source, encode, payload, sink, NULL);
        
        if (!gst_element_link(source, encode)) {
            g_printerr("Failed to link the source and the encode.");
        }
        
        if (!gst_element_link_filtered(encode, payload, filter)) {
            g_printerr("Failed to link the encode and the payload with the filter: video/x-h264, stream-format=byte-stream.");
        }
        
        if (!gst_element_link(payload, sink)) {
            g_printerr("Failed to link the payload and the sink");
        }
        
    }
    
    void MediaStreamer::init_receiver(int port) {
        pipeline = gst_pipeline_new("mediastreamer-pipeline");
        
        source = gst_element_factory_make("udpsrc", "source");
        g_object_set(source, "port", port, NULL);
        
        GstCaps *filter = gst_caps_from_string("application/x-rtp, encoding-name=H264, payload=96");
        
        GstElement *depay = gst_element_factory_make("rtph264depay", "depay");
        GstElement *parse = gst_element_factory_make("h264parse", "parse");
        GstElement *decode = gst_element_factory_make("avdec_h264", "decode");
        
        textoverlay = gst_element_factory_make("textoverlay", "textoverlay");
        g_object_set(textoverlay, "text", "TEXT", "font-desc", "Sans 36", NULL);
        
        sink = gst_element_factory_make("autovideosink", "sink");
        
        gst_bin_add_many(GST_BIN(pipeline), source, depay, parse, decode, textoverlay, sink, NULL);
        
        if (!gst_element_link_filtered(source, depay, filter)) {
            g_printerr("Failed to link the source and the depay with the filter: application/x-rtp, encoding-name=H264, payload=96.");
        }
        
        if (!gst_element_link_many(depay, parse, decode, textoverlay, sink, NULL)) {
            g_printerr("Failed to link elements: the depay, parse, decode, textoverlay, and sink.");
        }
    }
    
}
