#pragma once
#include "SkeletonEvent.h"
#include "EdgeChain.h"
class PickEvent :
    public SkeletonEvent
{
private:
    using spv2d = std::shared_ptr<Vector2d>;
    using spec = std::shared_ptr<EdgeChain>;
public:
    EdgeChain* Chain;
    PickEvent(spv2d point, double distance, spec chain);
    bool IsObsolete() override;
};
