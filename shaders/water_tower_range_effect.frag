#version 330 core
in vec2 texCoord;
// https://stackoverflow.com/questions/35604130/convert-gl-fragcoord-coordinate-to-screen-positions
layout(origin_upper_left) in vec4 gl_FragCoord;

out vec4 color;

uniform vec4 spriteColor;
uniform sampler2D image;
uniform vec3 towerRangeData[512];
uniform int towerRangeDataSize;
uniform float time;

vec2 distort(vec2 uv, float factor) {
  vec2 coord;
  coord.x = uv.x + factor * cos(uv.x * 3.14 * 10.0 + time / 3.3)/190.0;
  coord.y = uv.y + factor * sin(uv.y * 3.14 * 10.0 + time / 3.1)/200.0;
  return coord;
}

void main()
{
  // these tower varibales below are used to compute "factor", more details below
  float minDistance = 999999.0f;
  float largestRange = 0.01f;

  bool isInRange = false;
  for(int i = 0; i < towerRangeDataSize; i++){
    float dist = distance(gl_FragCoord.xy, towerRangeData[i].xy);
    minDistance = min(minDistance, dist);
    if (dist <= towerRangeData[i].z) {
      largestRange = max(largestRange, towerRangeData[i].z);
      isInRange = true;
    }
  }

  if(isInRange){
    // why we need "factor"?
    // if a pixel is closer to a tower, then more distort and blue
    // otherwise, less distort and blue
    float factor = (largestRange - minDistance)/largestRange;
    vec2 coord = distort(texCoord, factor);
    color = spriteColor * texture(image, coord) + vec4(0,0,0.5,0) * factor; 
  } else {
    vec2 coord = texCoord;
    color = spriteColor * texture(image, coord);
  }
}  
