#include "home_component.hpp"

HomeComponent::HomeComponent(){
    default_texture = make_shared<Texture>(texture_path("home.png"), true);
	alt_texture = make_shared<Texture>(texture_path("home_warning.png"), true);
}