#ifndef POSITION_TEXTURE_VERT
#define POSITION_TEXTURE_VERT

const char* position_texture_vert = GLSL(

	layout (location = 0) in vec4 position;
	layout (location = 1) in vec2 tex_coord;

	uniform mat4 MVP_MATRIX;

	out VS_OUT {
		vec2 tex_coord;
	} vs_out;

	void main()
	{
		gl_Position = MVP_MATRIX * position;
		vs_out.tex_coord = tex_coord;
	}

);

#endif