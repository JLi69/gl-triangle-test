#version 330

layout(location = 0) in vec4 pos;
out vec2 fragpos;

void main()
{
	gl_Position = pos;
	fragpos = pos.xy;
}
