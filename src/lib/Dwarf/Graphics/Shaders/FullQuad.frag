#ifndef SHADERS_FULLQUAD_FRAG
#define SHADERS_FULLQUAD_FRAG

const char* fullquad_frag = GLSL(

	in VS_OUT {
		vec2 tex_coord;
	} fs_in;

	uniform sampler2D sampler;
	out vec4 color;

	void main(void) {
		color = texture(sampler, fs_in.tex_coord);
	}

);
#endif
