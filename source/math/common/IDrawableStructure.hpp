#pragma once

#include <vector>

#include "math/common/Edge.hpp"
#include "math/common/NodeValue.hpp"

namespace math::common {

class IDrawableStructure {
public:
    virtual ~IDrawableStructure() = default;

    // TODO: На Class Diagram квалификатор const у getEdges() и getNodes() явно не указан,
    // но добавлен для совместимости с `const IDrawableStructure*` в GraphRender.
    virtual std::vector<Edge> getEdges() const = 0;
    virtual std::vector<NodeValue> getNodes() const = 0;
};

} // namespace math::common
