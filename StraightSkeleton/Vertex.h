#pragma once
#include <string>
#include <format>
#include <limits>
#include "Edge.h"
#include "Vector2d.h"
#include "LineParametric2d.h"
#include "FaceNode.h"
#include "CircularNode.h"

class Vertex : public CircularNode
{    
private:
    using spn = std::shared_ptr<CircularNode>;
    using spfn = std::shared_ptr<FaceNode>;
    using spv2d = std::shared_ptr<Vector2d>;
    using splp2d = std::shared_ptr<LineParametric2d>;
    using spe = std::shared_ptr<Edge>;
    const int RoundDigitCount = 5;
    double Round(double value, double precision);
public:
    friend class CircularNode;
    Vector2d* Point = nullptr;
    double Distance;
    LineParametric2d* Bisector = nullptr;
    Edge* NextEdge = nullptr;
    Edge* PreviousEdge = nullptr;
    bool IsProcessed;

    Vertex();
    //Vertex(const Vertex& val);
    //Vertex(Vector2d point, double distance, LineParametric2d bisector, Edge previousEdge, Edge nextEdge, spn nextNode = nullptr, spn prevNode = nullptr, CircularList* list = nullptr);
    Vertex(Vector2d* point, double distance, LineParametric2d* bisector, Edge* previousEdge, Edge* nextEdge);
    ~Vertex() override;
    Vertex& operator = (const Vertex& other);
    std::string ToString() const override;

    spfn LeftFace = nullptr;
    spfn RightFace = nullptr;
};
