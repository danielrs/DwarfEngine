#ifndef SHADERS_GAUSSBLURFX_FRAG
#define SHADERS_GAUSSBLURFX_FRAG

const char* gaussblurfx_frag = GLSL(

	const float weights[] = float[](
		0.0024499299678342,
		0.0043538453346397,
		0.0073599963704157,
		0.0118349786570722,
		0.0181026699707781,
		0.0263392293891488,
		0.0364543006660986,
		0.0479932050577658,
		0.0601029809166942,
		0.0715974486241365,
		0.0811305381519717,
		0.0874493212267511,
		0.0896631113333857,
		0.0874493212267511,
		0.0811305381519717,
		0.0715974486241365,
		0.0601029809166942,
		0.0479932050577658,
		0.0364543006660986,
		0.0263392293891488,
		0.0181026699707781,
		0.0118349786570722,
		0.0073599963704157,
		0.0043538453346397,
		0.0024499299678342
	);

	uniform sampler2D sampler;
	uniform bool horizontal;

	out vec4 color;

	void main(void) {
		vec4 c = vec4(0.0);
		int half_length = weights.length() >> 1;
		ivec2 P = ivec2(gl_FragCoord.xy);

		if (horizontal)  P -= ivec2(half_length, 0);
		else P -= ivec2(0, half_length);

		for (int i = 0; i < weights.length(); ++i) {
			if (horizontal) c += texelFetch(sampler, P + ivec2(i, 0), 0) * weights[i];
			else c += texelFetch(sampler, P + ivec2(0, i), 0) * weights[i];
		}

		color = c;
	}

);

#endif
