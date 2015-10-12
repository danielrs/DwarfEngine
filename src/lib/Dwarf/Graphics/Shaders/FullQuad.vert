#ifndef SHADERS_FULLQUAD_VERT
#define SHADERS_FULLQUAD_VERT

const char* fullquad_vert = GLSL(

	out VS_OUT {
		vec2 tex_coord;
	} vs_out;

	const vec4 vertices[] = vec4[](
		vec4(-1, -1, 0, 1),
		vec4(1, -1, 0, 1),
		vec4(-1, 1, 0, 1),
		vec4(-1, 1, 0, 1),
		vec4(1, -1, 0, 1),
		vec4(1, 1, 0, 1)
	);

	const vec4 tex_mod[] = vec4[](
		vec4(1, 1, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(1, 0, 0, 0),
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 0, 0)
	);

	void main(void) {
		gl_Position = vertices[gl_VertexID];
		vs_out.tex_coord = (vertices[gl_VertexID] + tex_mod[gl_VertexID]).xy;
	}

);
#endif
