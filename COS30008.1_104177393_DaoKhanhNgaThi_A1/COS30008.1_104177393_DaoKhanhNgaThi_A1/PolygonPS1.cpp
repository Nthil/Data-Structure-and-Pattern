#include "Polygon.h"

float Polygon::getSignedArea() const 
{
    float result = 0.0f;

    if (fNumberOfVertices > 2) {
        for (size_t i = 0; i < fNumberOfVertices; i++) {
            size_t j = (i + 1) % fNumberOfVertices;
            float x1 = fVertices[i].getX();
            float y1 = fVertices[i].getY();
            float x2 = fVertices[j].getX();
            float y2 = fVertices[j].getY();
            result += 0.5f * (x1 * y2 - y1 * x2);
        }
    }

    return result;
}

