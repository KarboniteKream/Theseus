#version 150

uniform sampler2D texture;
varying vec2 ex_Texture;

void main()
{
	gl_FragColor = texture2D(texture, ex_Texture);
}
