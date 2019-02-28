#ifndef BUILD_AREA_INDICATOR_FACTORY_H
#define BUILD_AREA_INDICATOR_FACTORY_H

#include "../utility.hpp"
#include "../program.hpp"
#include "../entity.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/color_component.hpp"

class BuildAreaIndicatorFactory {
  public:
    static Entity build(vec2 position, vec2 scale);
};

#endif