#ifndef POSITION_COLOR_FRAG
#define POSITION_COLOR_FRAG

const char* position_color_frag = GLSL(

	in VS_OUT {
		vec4 color;
	} vs_in;

	out vec4 color;

	void main()
	{
		color = vs_in.color;
	}

);

#endif
