#ifndef SHADERS_SPRITEBATCH_VERT
#define SHADERS_SPRITEBATCH_VERT

const char* spritebatch_vert = GLSL(

	layout (location = 0) in vec2 position;
	layout (location = 1) in vec2 tex_coord;

	uniform mat4 MVP_MATRIX;

	out VS_OUT {
		vec2 tex_coord;
	} vs_out;

	void main()
	{
		gl_Position = MVP_MATRIX * vec4(position, 0, 1);
		vs_out.tex_coord = tex_coord;
	}

);

#endif
