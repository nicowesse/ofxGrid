// Modified from https://github.com/ofZach/a-b-z

#include "ofxGrid.h"

//---------------------------------------------------------------

void Grid::setup(ofRectangle container, int cols, int rows) {
    _container = container;
    _nCols = cols;
    _nRows = rows;
    
    float rowH = container.height / _nRows;
    float colW = container.width / _nCols;
    for (int row = 0; row < _nRows; row++) {
        Row currentRow;
        for (int col = 0; col < _nCols; col++) {
            float x = colW * col;
            float y = rowH * row;
            
            ofRectangle rect(x, y, colW, rowH);
            rect.translate(_container.getPosition());
            auto cell = make_shared<Canvas>();
            cell->setup(ofVec2f(0.0f, 0.0f), rect);
            _cells.push_back(cell);
            currentRow.addCol(cell);
        }
        _rows.push_back(currentRow);
    }
}

//---------------------------------------------------------------
void Grid::draw() {
    for (auto cell : _cells) {
        cell->draw();
    }
}

