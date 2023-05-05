#version 330

uniform vec2 resolution;
uniform vec2 mouse;


const int MAX_ITERATION = 1024; 

int julia(vec2 c, vec2 z) {
	
	int i = 0;

	for(; (dot(z, z) < 4.0) && (i < MAX_ITERATION); ++i) {
		vec2 t = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y);
		z = t + c;
	}

	return i;

}

void main()  {

	vec2 z = vec2(-2.0, -2.0) + (4.0 * gl_FragCoord.xy / resolution);
	z.x *= resolution.x / resolution.y;
	
	vec2 c = vec2(-2.0, -2.0) + (4.0 * mouse / resolution);

	int j = julia(c, z);

	float scale = -log(float(j + 1) / MAX_ITERATION) / log(MAX_ITERATION);
	gl_FragColor = vec4(.2 * scale, .8 * scale, .5 * scale, 1.0);
}