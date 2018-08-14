#pragma once

#include "ofMain.h"
#include "Canvas.h"
#include "CanvasEvent.h"

struct Row {
    vector<shared_ptr<Canvas> > cols;
    
    void addCol(shared_ptr<Canvas> col) {
        cols.push_back(col);
    }
    
    shared_ptr<Canvas> getCol(int index) {
        return cols[index];
    }
};

#ifndef GRID
#define GRID

class Grid {
    int _nCols;
    int _nRows;
    vector<shared_ptr<Canvas> > _cells;
    vector<Row> _rows;
    ofRectangle _container;
    
public:
    Grid() : _nCols(1), _nRows(1) {};
    inline void setCols(int cols) { _nCols = cols; }
    inline void setRows(int rows) { _nRows = rows; }
    
    void setup(ofRectangle container, int cols = 1, int rows = 1);
    void draw();
    
    vector<shared_ptr<Canvas> > getCells() { return _cells; }
    
    shared_ptr<Canvas> getCell(int index) {
        if (index > _cells.size()) {
            ofLogWarning("Index has to be lower than the cell-count") << " (" << _cells.size() << ")";
            return;
        }
        return _cells[index];
    }
    
    ofRectangle getCellRect(int index) {
        if (index > _cells.size()) {
            ofLogWarning("Index has to be lower than the cell-count") << " (" << _cells.size() << ")";
            return;
        }
        return _cells[index]->getInnerBounds();
    }
};

#endif
