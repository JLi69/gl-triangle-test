#version 330

out vec4 color;
in vec2 fragpos;

void main()
{
	//Rainbow effect
	color = vec4(fragpos.x + 0.5, fragpos.y + 0.5, fragpos.y * fragpos.x + 0.5, 1.0);
}
