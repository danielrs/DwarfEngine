#ifndef SHADERS_BLOOMCOMBINEFX_FRAG
#define SHADERS_BLOOMCOMBINEFX_FRAG

const char* bloomcombinefx_frag = GLSL(

	uniform sampler2D sampler;
	uniform sampler2D bloom_sampler;

	uniform float exposure;
	uniform float bloom_factor;
	uniform float scene_factor;

	out vec4 color;

	void main(void) {
		vec4 c = vec4(0.0);

		c += texelFetch(sampler, ivec2(gl_FragCoord.xy), 0) * scene_factor;
		c += texelFetch(bloom_sampler, ivec2(gl_FragCoord.xy), 0) * bloom_factor;


		/* c.rgb = vec3(1.0) - exp(-c.rgb * exposure); */
		color = c;

	}
);

#endif
