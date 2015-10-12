#ifndef SHADERS_BLOOMFX_FRAG
#define SHADERS_BLOOMFX_FRAG

const char* bloomfx_frag = GLSL(

	in VS_OUT {
		vec2 tex_coord;
	} fs_in;

	uniform sampler2D sampler;
	uniform float bloom_thresh_min;
	uniform float bloom_thresh_max;

	out vec4 color;

	void main(void) {
		vec3 pixel = texture(sampler, fs_in.tex_coord).xyz;
		// Calculate luminance
		float Y = dot(pixel, vec3(0.299, 0.587, 0.144));
		// Threshold color based on its luminance
		pixel = pixel * 4.0 * smoothstep(bloom_thresh_min, bloom_thresh_max, Y);
		color = vec4(pixel, 1.0);
	}

);
#endif
