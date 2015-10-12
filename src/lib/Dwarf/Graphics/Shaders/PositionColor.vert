#ifndef POSITION_COLOR_VERT
#define POSITION_COLOR_VERT

const char* position_color_vert = GLSL(

	layout (location = 0) in vec4 position;
	layout (location = 1) in vec4 color;

	out VS_OUT {
		vec4 color;
	} vs_out;

	uniform mat4 MVP_MATRIX;

	void main()
	{
		gl_Position = MVP_MATRIX * position;
		vs_out.color = color;
	}

);

#endif
