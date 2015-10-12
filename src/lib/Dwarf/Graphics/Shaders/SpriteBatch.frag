#ifndef SHADERS_SPRITEBATCH_FRAG
#define SHADERS_SPRITEBATCH_FRAG

const char* spritebatch_frag = GLSL(

	uniform mat4 MVP_MATRIX;

	in VS_OUT {
		vec2 tex_coord;
	} vs_in;

	uniform sampler2D sampler;

	out vec4 color;

	void main()
	{
		color = texture(sampler, vs_in.tex_coord);
	}

);

#endif
