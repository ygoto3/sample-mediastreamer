#ifndef MediaStreamer_hpp
#define MediaStreamer_hpp

#include <gst/gst.h>
#include <string>
#include <stdio.h>

namespace framework::media {
    enum MediaStreamerType {
        MEDIA_STREAMER_SEND,
        MEDIA_STREAMER_RECEIVE
    };

    class MediaStreamer {
    public:
        MediaStreamer(MediaStreamerType type, std::string ip, int port);
        virtual ~MediaStreamer();
        void Load();
        void Change(std::string text);
    private:
        MediaStreamer();
        GstElement *pipeline, *source, *textoverlay, *demuxer, *decoder, *converter, *resample, *sink;
        void init_sender(std::string host, int port);
        void init_receiver(int port);
    };

}

#endif /* MediaStreamer_hpp */
