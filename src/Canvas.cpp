//
//  Canvas.cpp
//  type_wall
//
//  Created by Jobb @ Void on 09.08.2018.
//
//

#include "Canvas.h"

Canvas::Canvas() {
    _outerBounds.set(0, 0, ofGetWidth(), ofGetHeight());
    _innerBounds = _outerBounds;
}

void Canvas::setup(const ofVec2f padding, const ofRectangle fitInside) {
    ofLogNotice("Canvas type – 2D");
    if (_parent != nullptr) {
        _outerBounds = _parent->getOuterBounds();
    } else {
        _outerBounds = fitInside;
    }
    
    ofLogNotice("Outer bounds:") << _outerBounds;
    
    _innerBounds = _outerBounds;
    
    setOuterPadding(Padding::fromVector(padding));
    setInnerPadding(Padding::zero());
}

void Canvas::setup(const ofRectangle target, const ofRectangle fitInside) {
    ofLogNotice("Canvas type – Target Rect");
    if (_parent != nullptr) {
        _outerBounds = _parent->getOuterBounds();
    } else {
        _outerBounds = fitInside;
    }
    
    _outerBounds.setPosition(target.getPosition() + fitInside.getPosition());
    _outerBounds.setSize(target.width, target.height);
    
    _innerBounds = _outerBounds;
    
    Padding outer(_outerBounds.getTop(), _outerBounds.getRight(), _outerBounds.getBottom(), _outerBounds.getLeft());
    setOuterPadding(outer);
    setInnerPadding(Padding::zero());
}

void Canvas::setup(float topInset, float rightInset, float bottomInset, float leftInset, const ofRectangle fitInside) {
    ofLogNotice("Canvas type – 4D");
    if (_parent != nullptr) {
        _outerBounds = _parent->getOuterBounds();
    } else {
        _outerBounds = fitInside;
    }
    
    _outerBounds.setX(leftInset);
    _outerBounds.setY(topInset);
    _outerBounds.setWidth((_outerBounds.width - _outerBounds.getLeft()) - rightInset);
    _outerBounds.setHeight((_outerBounds.height - _outerBounds.getBottom()) - bottomInset);
    
    _innerBounds = _outerBounds;
    
    Padding outer(topInset, rightInset, bottomInset, leftInset);
    setOuterPadding(outer);
    setInnerPadding(Padding::zero());
}

void Canvas::refit() {
    setOuterPadding(_outerPadding);
    setInnerPadding(_innerPadding);
}

void Canvas::draw() {
    ofPushStyle();
    ofSetColor(255);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawRectangle(_innerBounds);
    ofPopStyle();
}

void Canvas::draw(ofStyle &style) {
    ofPushStyle();
    if (style.bFill) {
        ofSetColor(style.bgColor);
        ofFill();
        ofDrawRectangle(_innerBounds);
    }
    ofSetColor(style.color);
    ofNoFill();
    ofSetLineWidth(style.lineWidth);
    ofDrawRectangle(_innerBounds);
    ofPopStyle();
}

void Canvas::debug() {
    ofPushStyle();
    ofSetColor(ofColor::indianRed);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawRectangle(_outerBounds);
    ofPopStyle();
}

void Canvas::setOuterPadding(Padding padding) {
    ofRectangle parentBounds;
    if (_parent != nullptr) {
        parentBounds = _parent->getInnerBounds();
    } else {
        parentBounds = _outerBounds;
    }
    
    _outerPadding = padding;
    ofVec2f pad = padding.getNormalized(parentBounds).getVector();
    
    float w = parentBounds.getWidth() * pad.x;
    float h = parentBounds.getHeight() * pad.y;
    
    //_outerBounds.scaleFromCenter(pad.x, pad.y);
    _outerBounds.setFromCenter(parentBounds.getCenter(), w, h);
    
    setInnerPadding(_innerPadding);
}

void Canvas::setInnerPadding(Padding padding) {
    _innerPadding = padding;
    ofVec2f pad = padding.getNormalized(_outerBounds).getVector();
    
    float w = _outerBounds.getWidth() * pad.x;
    float h = _outerBounds.getHeight() * pad.y;
    
    _innerBounds.setFromCenter(_outerBounds.getCenter(), w, h);
    
    static CanvasEvent resizeEvent;
    resizeEvent.message = "RESIZE";
    resizeEvent.type = CanvasEvent::RESIZE;
    resizeEvent.canvas = this;
    
    //ofNotifyEvent(CanvasEvent::events, resizeEvent);
    for (auto child : _children) {
        child->refit();
    }
}


