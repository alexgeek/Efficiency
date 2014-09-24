varying vec2 uv;
uniform sampler2D textureId;

void main()
{
	gl_FragColor = texture2D(textureId, uv);
}
