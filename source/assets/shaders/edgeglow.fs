#version 330 core

out vec4 color;
in vec3 position;

// Values that stay constant for the whole mesh.
uniform samplerCube tex;
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

#define iMouse vec4(0)

float d = sin(iGlobalTime * 5.0)*0.5 + 1.5; // kernel offset

float lookup(vec2 p, float dx, float dy)
{
    vec2 uv = (p.xy + vec2(dx * d, dy * d)) / iResolution.xy;
    vec4 c = texture2D(iChannel0, uv.xy);
	
	// return as luma
    return 0.2126*c.r + 0.7152*c.g + 0.0722*c.b;
}

void main(void)
{
    vec2 p = gl_FragCoord.xy;
    
	// simple sobel edge detection
    float gx = 0.0;
    gx += -1.0 * lookup(p, -1.0, -1.0);
    gx += -2.0 * lookup(p, -1.0,  0.0);
    gx += -1.0 * lookup(p, -1.0,  1.0);
    gx +=  1.0 * lookup(p,  1.0, -1.0);
    gx +=  2.0 * lookup(p,  1.0,  0.0);
    gx +=  1.0 * lookup(p,  1.0,  1.0);
    
    float gy = 0.0;
    gy += -1.0 * lookup(p, -1.0, -1.0);
    gy += -2.0 * lookup(p,  0.0, -1.0);
    gy += -1.0 * lookup(p,  1.0, -1.0);
    gy +=  1.0 * lookup(p, -1.0,  1.0);
    gy +=  2.0 * lookup(p,  0.0,  1.0);
    gy +=  1.0 * lookup(p,  1.0,  1.0);
    
	// hack: use g^2 to conceal noise in the video
    float g = gx*gx + gy*gy;
    float g2 = g * (sin(iGlobalTime) / 2.0 + 0.5);
    
    vec4 col = texture2D(iChannel0, p / iResolution.xy);
    col += vec4(0.0, g, g2, 1.0);
    
    gl_FragColor = col;
}
