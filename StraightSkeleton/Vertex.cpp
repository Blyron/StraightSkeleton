#include "Vertex.h"
#include "CircularList.h"

unsigned int Vertex::_idCounter = 0;

Vertex::Vertex()
{
    _id = ++_idCounter;
    Point = nullptr;
    Bisector = nullptr;
    NextEdge = nullptr;
    PreviousEdge = nullptr;
    Distance = std::numeric_limits<double>::quiet_NaN();
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}
/*
Vertex::Vertex(const Vertex& val)
{
    Point = std::make_shared<Vector2d>(Vector2d(*val.Point));
    Distance = val.Distance;
    Bisector = std::make_shared<LineParametric2d>(LineParametric2d(*val.Bisector));
    NextEdge = std::make_shared<Edge>(Edge(*val.NextEdge));
    PreviousEdge = std::make_shared<Edge>(Edge(*val.PreviousEdge));
    IsProcessed = val.IsProcessed;
    LeftFace = std::make_shared<FaceNode>(FaceNode(*val.LeftFace));
    RightFace = std::make_shared<FaceNode>(FaceNode(*val.RightFace));
}

Vertex::Vertex(Vector2d point, double distance, LineParametric2d bisector, Edge previousEdge, Edge nextEdge, spn nextNode, spn prevNode, CircularList* list)
    : CircularNode(nextNode, prevNode, list)
{
    Point = std::make_shared<Vector2d>(Vector2d(point));
    Distance = Round(distance, RoundDigitCount);
    Bisector = std::make_shared<LineParametric2d>(LineParametric2d(bisector));
    PreviousEdge = std::make_shared<Edge>(Edge(previousEdge));
    NextEdge = std::make_shared<Edge>(Edge(nextEdge));
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}

Vertex::Vertex(Vector2d* point, double distance, LineParametric2d* bisector, Edge* previousEdge, Edge* nextEdge)
{
    Point = point;
    Bisector = bisector;
    NextEdge = nextEdge;
    PreviousEdge = previousEdge;
    Distance = distance;
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}
*/
Vertex::Vertex(spv2d point, double distance, splp2d bisector, spe previousEdge, spe nextEdge)
{
    _id = ++_idCounter;
    Point = point;
    Bisector = bisector;
    NextEdge = nextEdge;
    PreviousEdge = previousEdge;
    Distance = distance;
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}

Vertex& Vertex::operator = (const Vertex& other)
{
    if (this != &other)
    {
        Point = other.Point;
        Distance = other.Distance;
        Bisector = other.Bisector;
        PreviousEdge = other.PreviousEdge;
        NextEdge = other.NextEdge;
        IsProcessed = other.IsProcessed;
        LeftFace = other.LeftFace;
        RightFace = other.RightFace;
    }
    return *this;
}

bool Vertex::operator==(const Vertex& other) const
{
    return this->_id == other._id;
}

std::string Vertex::ToString() const
{
    return std::format("Vertex [v={0}, IsProcessed={1}, Bisector={2}, PreviousEdge={3}, NextEdge={4}]", Point->ToString(), IsProcessed, Bisector->ToString(), PreviousEdge->ToString(), NextEdge->ToString());
}

unsigned int Vertex::GetInstanceId() const
{
    return _id;
}

double Vertex::Round(double value, double precision)
{
    double p10 = pow(10.0f, precision);
    return round(value * p10) / p10;
}
size_t Vertex::HashFunction::operator()(const Vertex& val) const
{
    return val.GetInstanceId();
}

size_t Vertex::HashFunction::operator()(const std::shared_ptr<Vertex> val) const
{
    return val->GetInstanceId();
}