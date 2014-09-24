#version 330 core

out vec4 gl_FragColor;
in vec3 position;

// Values that stay constant for the whole mesh.
uniform samplerCube tex;
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

#define iMouse vec4(0)

void main(void)
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy - .5;
	uv.x*=iResolution.x/iResolution.y;
	if (iMouse.z>0.) uv+=(iMouse.xy/iResolution.xy-.5)*2.;
	float t=iGlobalTime*.2;
	float fov=1.5+sin(t);
	vec3 dir=normalize(vec3(uv*fov*mat2(cos(t),sin(t),-sin(t),cos(t)),1.));
	vec3 from=vec3(sin(t*1.28352),0.,t*5.)*.005;
	float dist=-0.015; 
	vec3 vol=vec3(0.);
	for (int v=0; v<300; v++) {
		dist+=.00015;
		vec3 p=from+dist*dir*vec3(vec2(sign(dist)),1.);				
		vec3 disp=texture2D(iChannel0,vec2(length(p.xy),p.z*.3)*2.2568).xyz-.5;
		vol+=pow(length(abs(.5-mod(p+disp*.013,vec3(.01))/.01)),14.)
			*(.7+normalize(disp)*.3)*exp(-500.*dist*dist);
	}
	vol=(vol+.2)*min(1.,t-.05)*vec3(1.,.8,.7);
	gl_FragColor = vec4(pow(vol,vec3(1.3)),1.0);
}
