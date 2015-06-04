#include "Block.h"

CompassDirection axis_to_compass(AxisDirection axisDirection) {
    return static_cast<CompassDirection>((int)axisDirection);
}
AxisDirection compass_to_axis(CompassDirection compassDirection) {
    return static_cast<AxisDirection>((int)compassDirection);
}

Block::Block(std::string name) :
    name_(name)
{
}

Block::~Block()
{
    delete renderer_;
}