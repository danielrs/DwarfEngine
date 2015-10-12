#ifndef POSITION_TEXTURE_FRAG
#define POSITION_TEXTURE_FRAG

const char* position_texture_frag = GLSL(

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