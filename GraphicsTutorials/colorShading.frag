#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
out vec4 color;

uniform float time;

void main(){
	fragmentColor = vec4(tan(fragmentPosition.y/fragmentPosition.x*time),
	tan(fragmentPosition.y/fragmentPosition.x*time),
	tan(fragmentPosition.y/fragmentPosition.x*time), fragmentColor.a + time);
}