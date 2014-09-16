#version 330 core

out vec4 color;
in vec3 position;

// Values that stay constant for the whole mesh.
uniform samplerCube tex;
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

#define iMouse vec4(0)

#define INTENSITY 6.5
#define GLOW 2.0

vec3 blob(vec2 uv, vec3 color, vec2 speed, vec2 size, float time) {
	vec2 point = vec2(
		sin(speed.x * time) * size.x,
		cos(speed.y * time) * size.y
	);

	float d = 1.0 / distance(uv, point);
	d = pow(d / INTENSITY, GLOW);
	
	return vec3(color.r * d, color.g * d, color.b * d);
}

void main(void) {
	vec2 uv = -1.0 + 2.0 * (gl_FragCoord.xy / iResolution.xy);

	float time = iGlobalTime * 0.75;

	float freqBlue = texture2D(iChannel0, vec2(0.01,0.25)).x * 4.0;
	float freqGreen = texture2D(iChannel0, vec2(0.1,0.25)).x * 2.0;
	
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	color.rgb += blob(uv, vec3(1.0, 0.3 * freqGreen, 0.5 * freqBlue), vec2(1.7, 2.2), vec2(0.4, 0.1), time);
	color.rgb += blob(uv, vec3(1.0, 0.3 * freqGreen, 0.5 * freqBlue), vec2(1.2, 2.3), vec2(0.3, 0.2), time);
	color.rgb += blob(uv, vec3(1.0, 0.3 * freqGreen, 0.5 * freqBlue), vec2(2.3, 2.1), vec2(0.2, 0.3), time);
	color.rgb += blob(uv, vec3(1.0, 0.3 * freqGreen, 0.5 * freqBlue), vec2(2.1, 1.0), vec2(0.1, 0.4), time);

	gl_FragColor = color;
}
