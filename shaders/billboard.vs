#version 400

layout (location = 0) in vec3 vPos;

uniform vec3 uCameraPos;
uniform float uSize;
uniform vec3 uOffset;
uniform vec4 uColor;
uniform mat4 uVP;

out vec4 color;
out vec2 uv;

void main()
{
   color = uColor;
   uv = vPos.xy;
   vec3 newPos = vPos - vec3(0.5f, 0.5f, 0.0f);
   mat4 scale = mat4 (uSize, 0.0f, 0.0f, 0.0f,
					0.0f, uSize, 0.0f, 0.0f,
					0.0f, 0.0f, uSize, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

   mat4 trans = mat4 (1.0f, 0.0f, 0.0f, 0.0f, 
				     0.0f, 1.0f, 0.0f, 0.0f,
				     0.0f, 0.0f, 1.0f, 0.0f, 
				     uOffset, 1.0f);

   vec3 cenz = normalize(uCameraPos - uOffset);
   vec3 cenx = cross(vec3(0,1,0), normalize(cenz));
   vec3 ceny = cross(normalize(cenz), normalize(cenx));

   mat4 rotate = mat4 (vec4(cenx, 0), vec4(ceny, 0), vec4(cenz, 0), vec4(0,0,0,1));
   mat4 transformation = trans * scale * rotate;
   gl_Position = uVP * transformation * vec4(newPos, 1.0);
}
