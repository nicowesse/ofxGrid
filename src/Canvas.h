//
//  Canvas.h
//  type_wall
//
//  Created by Jobb @ Void on 09.08.2018.
//
//
#include "ofMain.h"
#include "CanvasEvent.h"

#ifndef PADDING
#define PADDING
struct Padding {
    float top;
    float right;
    float bottom;
    float left;
    
    Padding() : top(0.0f), right(0.0f), bottom(0.0f), left(0.0f) {};
    Padding(float _horiz, float _vert) {
        top = _vert;
        right = _horiz;
        bottom = _vert;
        left = _horiz;
    };
    Padding(float _top, float _right, float _bottom, float _left) {
        top = _top;
        right = _right;
        bottom = _bottom;
        left = _left;
    };
    
    void set2D(float _horiz, float _vert) {
        top = _vert;
        right = _horiz;
        bottom = _vert;
        left = _horiz;
    }
    void set4D(float _top, float _right, float _bottom, float _left) {
        top = _top;
        right = _right;
        bottom = _bottom;
        left = _left;
    }
    
    Padding& normalize(const ofRectangle target) {
        top = (top > 1.0f) ? ((target.width - (top * 2.0f)) / target.width) : 1.0f - top;
        right = (right > 1.0f) ? ((target.height - (right * 2.0f)) / target.height) : 1.0f - right;
        bottom = (bottom > 1.0f) ? ((target.width - (bottom * 2.0f)) / target.width) : 1.0f - bottom;
        left = (left > 1.0f) ? ((target.height - (left * 2.0f)) / target.height) : 1.0f - left;
        
        return *this;
    }
    
    Padding getNormalized(const ofRectangle target) {
        Padding pad;
        pad.top = (top > 1.0f) ? ((target.width - (top * 2.0f)) / target.width) : 1.0f - top;
        pad.right = (right > 1.0f) ? ((target.height - (right * 2.0f)) / target.height) : 1.0f - right;
        pad.bottom = (bottom > 1.0f) ? ((target.width - (bottom * 2.0f)) / target.width) : 1.0f - bottom;
        pad.left = (left > 1.0f) ? ((target.height - (left * 2.0f)) / target.height) : 1.0f - left;
        
        return pad;
    }
    
    Padding getPixelOffsets(const ofRectangle target) {
        Padding pad;
        pad.top = (target.height * top) / 2.0f;
        pad.right = (target.width * right) / 2.0f;
        pad.bottom = (target.height * bottom) / 2.0f;
        pad.left = (target.width * left) / 2.0f;
        
        return pad;
    }
    
    ofVec2f getVector() {
        return ofVec2f(top, left);
    }
    
    static Padding fromVector(const ofVec2f vector) {
        Padding pad(vector.x, vector.y);
        return pad;
    }
    
    static Padding zero() {
        static Padding object = Padding();
        return object;
    }
};
#endif

#ifndef CANVAS
#define CANVAS

class Canvas : public enable_shared_from_this<Canvas> {
    shared_ptr<Canvas> _parent;
    vector<shared_ptr<Canvas> > _children;
    
    ofRectangle _outerBounds;
    ofRectangle _innerBounds;
    
    Padding _outerPadding;
    Padding _innerPadding;
    
public:
    Canvas();
    ~Canvas() {
        ofLogNotice("Deleted Canvas element");
    }
    void setup(const ofVec2f padding, const ofRectangle fitInside = ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    void setup(const ofRectangle target, const ofRectangle fitInside = ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    void setup(float topInset, float rightInset, float bottomInset, float leftInset, const ofRectangle fitInside = ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    
    void setParent(shared_ptr<Canvas> parent)
    {
        _parent = parent;
    }
    
    inline shared_ptr<Canvas> const getParent() const { return _parent; }
    
    void addChild(const shared_ptr<Canvas> child)
    {
        _children.push_back(child);
        child->setParent(shared_from_this());
    }
    
    vector<shared_ptr<Canvas> > getChildren()
    {
        return _children;
    }
    
    void draw();
    void draw(ofStyle &style);
    void debug();
    
    void refit();
    
    void setOuterPadding(Padding padding);
    void setInnerPadding(Padding padding);
    
    ofRectangle getOuterBounds() const
    {
        return _outerBounds;
    };
    
    ofRectangle getInnerBounds() const
    {
        return _innerBounds;
    };
};
#endif
