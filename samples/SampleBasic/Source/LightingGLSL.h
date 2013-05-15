#ifndef LightingGLSL_h__
#define LightingGLSL_h__

static const char ambientPassV[] =
	"#version 120\n"
	"in vec4 vertex;\n"
	"uniform mat4 projection = mat4(1);\n"
	"uniform mat4 model = mat4(1);\n"
	"uniform mat4 view = mat4(1);\n"
	"uniform vec4 incomingColor = vec4(0.5, 0.4, 0.1, 1);"
	"varying vec4 diffuse;\n"
	"void main() {\n"
	"  gl_Position = projection * view * model * vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"  diffuse = incomingColor;\n"
	"}\n";

static const char ambientPassF[] = 
	"#version 120\n"
	"varying vec4 diffuse;\n"
	"uniform vec4 ambient = vec4(1, 1, 1, 1);\n"
	"void main() {\n"
	"   gl_FragColor =  diffuse * ambient;\n"
	"}\n";


static const char directionalPassV[] =
	"#version 120\n"
	"in vec4 vertex;\n"
	"in vec3 normal;\n"
	"uniform vec3 lightDir = vec3(1,0,0);\n"
	"uniform vec4 lightDiffuse = vec4(0.9,0.9,0.9, 1);\n"
	"uniform mat4 projection = mat4(1);\n"
	"uniform mat4 model = mat4(1);\n"
	"uniform mat4 view = mat4(1);\n"
	"varying vec4 diffuse;\n"
	"void main() {\n"
	"  gl_Position = projection * view * model * vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"	vec3 world_normal = vec4(model * vec4(normal, 0)).xyz;\n"
	"  diffuse = lightDiffuse * max(dot(lightDir, world_normal), 0);\n"
	"}\n";

static const char directionalPassF[] = 
	"#version 120\n"
	"varying vec4 diffuse;\n"
	"void main() {\n"
	"   gl_FragColor = diffuse;\n"
	"}\n";

static const char pointPassV[] =
	"#version 120\n"
	"precision highp float;"
	"in vec4 vertex;\n"
	"in vec3 normal;\n"
	"uniform vec4 lightPosition;\n"
	"uniform vec4 lightDiffuse = vec4(0,0,0, 1);\n"
	"uniform mat4 projection = mat4(1);\n"
	"uniform mat4 model = mat4(1);\n"
	"uniform mat4 view = mat4(1);\n"
	"varying vec4 diffuse;\n"
	"varying vec3 fragNormal;\n"
	"varying vec3 outLightDir;"
	"varying float distance;"
	"void main() {\n"
	"	vec3 lightDir = vec4(lightPosition - (model * vec4(vertex.x, vertex.y, vertex.z, 1.f))).xyz;\n"
	"	distance = length(lightDir);"
	"	lightDir = normalize(lightDir);"
	"gl_Position = projection * view * model * vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"	vec3 world_normal = vec4(model * vec4(normal, 0)).xyz;\n"
	"  diffuse = lightDiffuse;\n"
	"	fragNormal = world_normal;outLightDir = lightDir;\n"
	"}\n";

static const char pointPassF[] = 
	"#version 120\n"
	"precision highp float;"
	"varying vec4 diffuse;\n"
	"varying vec3 fragNormal;\n"
	"varying vec3 outLightDir;\n"
	"varying float distance;"
	"void main() {\n"
	"	float attenuation = 1 / distance;\n"
	"   gl_FragColor = diffuse * max(dot(outLightDir, fragNormal), 0) * attenuation;\n"
	"}\n";

static const char spotlightPassV[] =
	"#version 120\n"
	"precision highp float;"
	"in vec4 vertex;\n"
	"in vec3 normal;\n"
	"uniform vec4 lightPosition;\n"
	"uniform vec4 lightDiffuse;\n"
	"uniform mat4 projection = mat4(1);\n"
	"uniform mat4 model = mat4(1);\n"
	"uniform mat4 view = mat4(1);\n"
	"uniform mat4 shadowp = mat4(1);\n"
	"uniform mat4 shadowv = mat4(1);\n"
	"varying vec4 shadowCoord;"
	"varying vec4 diffuse;\n"
	"varying vec3 fragNormal;\n"
	"varying vec3 outLightDir;"
	"varying float distance;"
	"void main() {\n"
	"	vec3 lightDir = vec4(lightPosition - (model * vec4(vertex.x, vertex.y, vertex.z, 1.f))).xyz;\n"
	"	distance = length(lightDir);"
	"	lightDir = normalize(lightDir);"
	"	gl_Position = projection * view * model * vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"	vec3 world_normal = vec4(model * vec4(normal, 0)).xyz;\n"
	"   diffuse = lightDiffuse;\n"
	"	fragNormal = world_normal;outLightDir = lightDir;\n"
	"	mat4 depthBias = mat4(0.5, 0.0, 0.0, 0.0,	0.0, 0.5, 0.0, 0.0,	0.0, 0.0, 0.5, 0.0,	0.5, 0.5, 0.5, 1.0);\n"
	"	shadowCoord =  depthBias * shadowp * shadowv * model * vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"}\n";

static const char spotlightPassF[] = 
	"#version 120\n"
	"precision highp float;"
	"varying vec4 diffuse;\n"
	"varying vec3 fragNormal;\n"
	"varying vec3 outLightDir;\n"
	"varying float distance;"
	"uniform float lightCutoff;"
	"uniform vec3 lightDirection;\n"
	"uniform sampler2D shadowmap;\n"
	"varying vec4 shadowCoord;"
	"void main() {\n"
	"	float attenuation = 1 / distance; float intensity = 0.0;\n"
	"	vec3 ld = normalize(outLightDir);\n"
	"	vec3 sd = normalize(vec3(-lightDirection));\n" 
	"	if(dot(sd, ld) > lightCutoff){\n"
	"		intensity = max(dot(outLightDir, fragNormal), 0);\n"
	"	}\n"
	"	float visibility = 1.0;\n"
	"	if ( texture2D( shadowmap, shadowCoord.xy/shadowCoord.w ).z  <  (shadowCoord.z - 0.005)/shadowCoord.w){\n"
	"		visibility = 0.2;\n"
	"	}\n"
	"	/*visibility = shadow2D( shadowmap, vec3(shadowCoord.xy, (shadowCoord.z)/shadowCoord.w) ).r;*/"
	"	gl_FragColor = visibility * diffuse * intensity;"
	"}\n";


static const char shadowPassV[] =
	"#version 120\n"
	"in vec4 vertex;\n"
	"uniform mat4 projection = mat4(1);\n"
	"uniform mat4 model = mat4(1);\n"
	"uniform mat4 view = mat4(1);\n"
	"void main() {\n"
	"  gl_Position = projection * view * model * vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"}\n";

static const char shadowPassF[] = 
	"#version 120\n"
	"void main() {\n"
	"	/*gl_FragDepth = gl_FragCoord.z;*/"
	"	/*gl_FragColor = vec4(1,0,0,1);*/"
	"}\n";

static const char depthPassV[] =
	"#version 120\n"
	"in vec4 vertex;\n"
	"in vec2 uv;\n"
	"uniform mat4 projection = mat4(1);\n"
	"uniform mat4 model = mat4(1);\n"
	"uniform mat4 view = mat4(1);\n"
	"varying vec2 uv_o;\n"
	"void main() {\n"
	"  gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.f);\n"
	"	uv_o = (vertex.xy+vec2(1,1))/2.0;\n"
	"}\n";

static const char depthPassF[] = 
	"#version 120\n"
	"uniform sampler2D texture;\n"
	"varying vec2 uv_o;\n"
	"void main() {\n"
	"	vec4 raw = texture2D(texture, uv_o);\n"
	"	gl_FragColor = raw/4;"
	"}\n";

#endif // LightingGLSL_h__
