#version 150

attribute vec3 in_Position;
attribute vec2 in_Texture;
varying vec2 ex_Texture;
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(in_Position, 1.0);
	ex_Texture = in_Texture;
}
