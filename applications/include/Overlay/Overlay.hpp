#ifndef Overlay_h
#define Overlay_h

#include <string>

namespace overlay {

class OverlayId {
public:
    OverlayId(const long id);
    long getValue() { return value; }
private:
    long value;
};

class OverlayText {
public:
    OverlayText(std::string text)
        : value(text)
    {}
    const std::string getValue() { return value; }
private:

    const std::string value;
};

class Overlay {
public:
    Overlay(OverlayId id, OverlayText text);
    OverlayId getId();
    OverlayText getText();
private:
    long id;
    std::string text;
};

}

#endif /* Overlay_h */
