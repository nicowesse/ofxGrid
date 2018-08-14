#pragma once
#include "ofMain.h"
#include "Canvas.h"

#ifndef CANVAS_EVENT
#define PADDING

class CanvasEvent : public ofEventArgs {
public:
    
    enum CanvasEventType {
        NONE = 0,
        RESIZE,
    };
    
    Canvas * canvas;
    CanvasEventType type;
    string   message;
    
    CanvasEvent() {
        canvas = NULL;
        type = CanvasEventType::NONE;
    }
    
    static ofEvent <CanvasEvent> events;
};

#endif
