/*#include <Nephilim/World/ComponentWater2.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/CGL.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265
#endif

#include "./test/Program.h"
#include "./test/vec4.h"
#include "./test/mat4.h"

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#else
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#endif

#define IRRADIANCE_UNIT 0
#define INSCATTER_UNIT 1
#define TRANSMITTANCE_UNIT 2
#define SKY_UNIT 3
#define WAVE_UNIT 4
#define NOISE_UNIT 5

int width2 = 1000;

int height2 = 500;

Program *render = NULL;

Program *sky = NULL;

Program *skymap = NULL;

Program *clouds = NULL;

unsigned int skyTexSize = 512;

GLuint skyTex;

GLuint noiseTex;

bool cloudLayer = false;

float octaves = 10.0;

float lacunarity = 2.2;

float gain = 0.7;

float norm = 0.5;

float clamp1 = -0.15;

float clamp2 = 0.2;

float cloudColor[4] = { 1.0, 1.0, 1.0, 1.0 };

GLuint fbo;

GLuint vbo;

GLuint vboIndices;

vec4f vboParams;

int vboSize = 0;

float sunTheta = M_PI / 2.0 - 0.05;

float sunPhi = 0.0;

float cameraHeight = 6.0;

float cameraTheta = 0.0;

// RENDERING OPTIONS

float gridSize = 8.0;

float nyquistMin = 1.0;

float nyquistMax = 1.5;

float seaColor[4] = {10.0 / 255.0, 40.0 / 255.0, 120.0 / 255.0, 0.1};

float hdrExposure = 0.4;

bool grid = false;

bool animate = true;

bool seaContrib = true;

bool sunContrib = true;

bool skyContrib = true;

bool manualFilter = false;

// WAVES PARAMETERS (INPUT)

GLuint waveTex;

int nbWaves = 60;

vec4f *waves = NULL;

float lambdaMin = 0.02;

float lambdaMax = 30.0;

float heightMax = 0.32;

float waveDirection = 2.4;

float U0 = 10.0;

float waveDispersion = 1.25f;

// WAVE STATISTICS (OUTPUT)

float sigmaXsq = 0.0;

float sigmaYsq = 0.0;

float meanHeight = 0.0;

float heightVariance = 0.0;

float amplitudeMax = 0.0;

// ----------------------------------------------------------------------------
// CLOUDS
// ----------------------------------------------------------------------------

void drawClouds(const vec4f &sun, const mat4f &mat)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(clouds->program);
	glUniformMatrix4fv(glGetUniformLocation(clouds->program, "worldToScreen"), 1, true, mat.coefficients());
	glUniform3f(glGetUniformLocation(clouds->program, "worldCamera"), 0.0, 0.0, cameraHeight - meanHeight);
	glUniform3f(glGetUniformLocation(clouds->program, "worldSunDir"), sun.x, sun.y, sun.z);
	glUniform1f(glGetUniformLocation(clouds->program, "hdrExposure"), hdrExposure);
	glUniform1f(glGetUniformLocation(clouds->program, "octaves"), octaves);
	glUniform1f(glGetUniformLocation(clouds->program, "lacunarity"), lacunarity);
	glUniform1f(glGetUniformLocation(clouds->program, "gain"), gain);
	glUniform1f(glGetUniformLocation(clouds->program, "norm"), norm);
	glUniform1f(glGetUniformLocation(clouds->program, "clamp1"), clamp1);
	glUniform1f(glGetUniformLocation(clouds->program, "clamp2"), clamp2);
	glUniform4f(glGetUniformLocation(clouds->program, "cloudsColor"), cloudColor[0], cloudColor[1], cloudColor[2], cloudColor[3]);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-1e6, -1e6, 3000.0);
	glVertex3f(1e6, -1e6, 3000.0);
	glVertex3f(-1e6, 1e6, 3000.0);
	glVertex3f(1e6, 1e6, 3000.0);
	glEnd();
	glDisable(GL_BLEND);
}

// ----------------------------------------------------------------------------
// PROGRAM RELOAD
// ----------------------------------------------------------------------------

void loadPrograms(bool all)
{
	char* files[2];
	char options[512];
	files[0] = "ocean/atmosphere.glsl";
	files[1] = "ocean/ocean.glsl";
	sprintf(options, "#define %sSEA_CONTRIB\n#define %sSUN_CONTRIB\n#define %sSKY_CONTRIB\n#define %sCLOUDS\n#define %sHARDWARE_ANISTROPIC_FILTERING\n",
		seaContrib ? "" : "NO_", sunContrib ? "" : "NO_", skyContrib ? "" : "NO_", cloudLayer ? "" : "NO_", manualFilter ? "NO_" : "");

	if (render != NULL) {
		delete render;
	}
	render = new Program(2, files, options);
	glUseProgram(render->program);
	glUniform1i(glGetUniformLocation(render->program, "skyIrradianceSampler"), IRRADIANCE_UNIT);
	glUniform1i(glGetUniformLocation(render->program, "inscatterSampler"), INSCATTER_UNIT);
	glUniform1i(glGetUniformLocation(render->program, "transmittanceSampler"), TRANSMITTANCE_UNIT);
	glUniform1i(glGetUniformLocation(render->program, "skySampler"), SKY_UNIT);
	glUniform1i(glGetUniformLocation(render->program, "wavesSampler"), WAVE_UNIT);

	if (!all) {
		return;
	}

	files[0] = "ocean/atmosphere.glsl";
	files[1] = "ocean/sky.glsl";
	if (sky != NULL) {
		delete sky;
	}
	sky = new Program(2, files, options);
	glUseProgram(sky->program);
	glUniform1i(glGetUniformLocation(sky->program, "skyIrradianceSampler"), IRRADIANCE_UNIT);
	glUniform1i(glGetUniformLocation(sky->program, "inscatterSampler"), INSCATTER_UNIT);
	glUniform1i(glGetUniformLocation(sky->program, "transmittanceSampler"), TRANSMITTANCE_UNIT);
	glUniform1i(glGetUniformLocation(sky->program, "skySampler"), SKY_UNIT);

	files[0] = "ocean/atmosphere.glsl";
	files[1] = "ocean/skymap.glsl";
	if (skymap != NULL) {
		delete skymap;
	}
	skymap = new Program(2, files, options);
	glUseProgram(skymap->program);
	glUniform1i(glGetUniformLocation(skymap->program, "skyIrradianceSampler"), IRRADIANCE_UNIT);
	glUniform1i(glGetUniformLocation(skymap->program, "inscatterSampler"), INSCATTER_UNIT);
	glUniform1i(glGetUniformLocation(skymap->program, "transmittanceSampler"), TRANSMITTANCE_UNIT);
	glUniform1i(glGetUniformLocation(skymap->program, "noiseSampler"), NOISE_UNIT);

	if (clouds == NULL) {
		files[0] = "ocean/atmosphere.glsl";
		files[1] = "ocean/clouds.glsl";
		clouds = new Program(2, files);
		glUseProgram(clouds->program);
		glUniform1i(glGetUniformLocation(clouds->program, "skyIrradianceSampler"), IRRADIANCE_UNIT);
		glUniform1i(glGetUniformLocation(clouds->program, "inscatterSampler"), INSCATTER_UNIT);
		glUniform1i(glGetUniformLocation(clouds->program, "transmittanceSampler"), TRANSMITTANCE_UNIT);
		glUniform1i(glGetUniformLocation(clouds->program, "noiseSampler"), NOISE_UNIT);
	}
}

// ----------------------------------------------------------------------------
// MESH GENERATION
// ----------------------------------------------------------------------------

void generateMesh()
{
	if (vboSize != 0) {
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &vboIndices);
	}
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float horizon = tan(cameraTheta);
	float s = min(1.1f, 0.5f + horizon * 0.5f);

	float vmargin = 0.1;
	float hmargin = 0.1;

	vboParams = vec4f(width2, height2, gridSize, cameraTheta);
	vec4f *data = new vec4f[int(ceil(height2 * (s + vmargin) / gridSize) + 5) * int(ceil(width2 * (1.0 + 2.0 * hmargin) / gridSize) + 5)];

	int n = 0;
	int nx = 0;
	for (float j = height2 * s - 0.1; j > -height2 * vmargin - gridSize; j -= gridSize) {
		nx = 0;
		for (float i = -width2 * hmargin; i < width2 * (1.0 + hmargin) + gridSize; i += gridSize) {
			data[n++] = vec4f(-1.0 + 2.0 * i / width2, -1.0 + 2.0 * j / height2, 0.0, 1.0);
			nx++;
		}
	}

	glBufferData(GL_ARRAY_BUFFER, n * 16, data, GL_STATIC_DRAW);
	delete[] data;

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ARRAY_BUFFER, vboIndices);

	vboSize = 0;
	GLuint *indices = new GLuint[6 * int(ceil(height2 * (s + vmargin) / gridSize) + 4) * int(ceil(width2 * (1.0 + 2.0 * hmargin) / gridSize) + 4)];

	int nj = 0;
	for (float j = height2 * s - 0.1; j > -height2 * vmargin; j -= gridSize) {
		int ni = 0;
		for (float i = -width2 * hmargin; i < width2 * (1.0 + hmargin); i += gridSize) {
			indices[vboSize++] = ni + (nj + 1) * nx;
			indices[vboSize++] = (ni + 1) + (nj + 1) * nx;
			indices[vboSize++] = (ni + 1) + nj * nx;
			indices[vboSize++] = (ni + 1) + nj * nx;
			indices[vboSize++] = ni + (nj + 1) * nx;
			indices[vboSize++] = ni + nj * nx;
			ni++;
		}
		nj++;
	}

	glBufferData(GL_ARRAY_BUFFER, vboSize * 4, indices, GL_STATIC_DRAW);
	delete[] indices;
}

// ----------------------------------------------------------------------------
// WAVES GENERATION
// ----------------------------------------------------------------------------

long lrandom(long *seed)
{
	*seed = (*seed * 1103515245 + 12345) & 0x7FFFFFFF;
	return *seed;
}

float frandom(long *seed)
{
	long r = lrandom(seed) >> (31 - 24);
	return r / (float)(1 << 24);
}

inline float grandom(float mean, float stdDeviation, long *seed)
{
	float x1, x2, w, y1;
	static float y2;
	static int use_last = 0;

	if (use_last) {
		y1 = y2;
		use_last = 0;
	} else {
		do {
			x1 = 2.0f * frandom(seed) - 1.0f;
			x2 = 2.0f * frandom(seed) - 1.0f;
			w  = x1 * x1 + x2 * x2;
		} while (w >= 1.0f);
		w  = sqrt((-2.0f * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}
	return mean + y1 * stdDeviation;
}

#define srnd() (2*frandom(&seed) - 1)

void generateWaves()
{
	long seed = 1234567;
	float min = log(lambdaMin) / log(2.0f);
	float max = log(lambdaMax) / log(2.0f);

	sigmaXsq = 0.0;
	sigmaYsq = 0.0;
	meanHeight = 0.0;
	heightVariance = 0.0;
	amplitudeMax = 0.0;

	if (waves != NULL) {
		delete[] waves;
	}
	waves = new vec4f[nbWaves];

#define nbAngles 5 // even
#define angle(i) (1.5*(((i)%nbAngles)/(float)(nbAngles/2)-1))
#define dangle() (1.5/(float)(nbAngles/2))

	float Wa[nbAngles]; // normalised gaussian samples
	int index[nbAngles]; // to hash angle order
	float s=0;
	for (int i = 0; i < nbAngles; i++) {
		index[i] = i;
		float a = angle(i);
		s += Wa[i] = exp(-0.5*a*a);
	}
	for (int i = 0; i < nbAngles; i++) {
		Wa[i] /= s;
	}

	for (int i = 0; i < nbWaves; ++i) {
		float x = i / (nbWaves - 1.0f);

		float lambda = pow(2.0f, (1.0f - x) * min + x * max);
		float ktheta = grandom(0.0f, 1.0f, &seed) * waveDispersion;
		float knorm = 2.0f * M_PI / lambda;
		float omega = sqrt(9.81f * knorm);
		float amplitude;

		float step = (max-min) / (nbWaves-1); // dlambda/di
		float omega0 = 9.81 / U0;
		if ((i%(nbAngles)) == 0) { // scramble angle ordre
			for (int k = 0; k < nbAngles; k++) {   // do N swap in indices
				int n1 = lrandom(&seed)%nbAngles, n2 = lrandom(&seed)%nbAngles, n;
				n = index[n1];
				index[n1] = index[n2];
				index[n2] = n;
			}
		}
		ktheta = waveDispersion * (angle(index[(i)%nbAngles]) + 0.4*srnd()*dangle());
		ktheta *= 1.0 / (1.0 + 40.0*pow(omega0/omega,4));
		amplitude = (8.1e-3*9.81*9.81) / pow(omega,5) * exp(-0.74*pow(omega0/omega,4));
		amplitude *= 0.5*sqrt(2*M_PI*9.81/lambda)*nbAngles*step;
		amplitude = 3*heightMax*sqrt(amplitude);

		if (amplitude > 1.0f / knorm) {
			amplitude = 1.0f / knorm;
		} else if (amplitude < -1.0f / knorm) {
			amplitude = -1.0f / knorm;
		}

		waves[i].x = amplitude;
		waves[i].y = omega;
		waves[i].z = knorm * cos(ktheta);
		waves[i].w = knorm * sin(ktheta);
		sigmaXsq += pow(cos(ktheta), 2.0f) * (1.0 - sqrt(1.0 - knorm * knorm * amplitude * amplitude));
		sigmaYsq += pow(sin(ktheta), 2.0f) * (1.0 - sqrt(1.0 - knorm * knorm * amplitude * amplitude));
		meanHeight -= knorm * amplitude * amplitude * 0.5f;
		heightVariance += amplitude * amplitude * (2.0f - knorm * knorm * amplitude * amplitude) * 0.25f;
		amplitudeMax += fabs(amplitude);
	}

	float var = 4.0f;
	amplitudeMax = 2.0f * var * sqrt(heightVariance);

	glActiveTexture(GL_TEXTURE0 + WAVE_UNIT);
	glBindTexture(GL_TEXTURE_1D, waveTex);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F_ARB, nbWaves, 0, GL_RGBA, GL_FLOAT, waves);
}


void save(int id)
{
	char buf[256];
	sprintf(buf, "data/scene%d.dat", id);
	std::ofstream out;
	out.open(buf);
	out << sunTheta << std::endl;
	out << sunPhi << std::endl;
	out << cameraHeight << std::endl;
	out << cameraTheta << std::endl;
	out << gridSize << std::endl;
	out << nyquistMin << std::endl;
	out << nyquistMax << std::endl;
	out << seaColor[0] << std::endl;
	out << seaColor[1] << std::endl;
	out << seaColor[2] << std::endl;
	out << seaColor[3] << std::endl;
	out << hdrExposure << std::endl;
	out << grid << std::endl;
	out << animate << std::endl;
	out << seaContrib << std::endl;
	out << sunContrib << std::endl;
	out << skyContrib << std::endl;
	out << nbWaves << std::endl;
	out << lambdaMin << std::endl;
	out << lambdaMax << std::endl;
	out << heightMax << std::endl;
	out << waveDirection << std::endl;
	out << waveDispersion << std::endl;
	out << cloudLayer << std::endl;
	out << octaves << std::endl;
	out << lacunarity << std::endl;
	out << gain << std::endl;
	out << norm << std::endl;
	out << clamp1 << std::endl;
	out << clamp2 << std::endl;
	out << cloudColor[0] << std::endl;
	out << cloudColor[1] << std::endl;
	out << cloudColor[2] << std::endl;
	out << cloudColor[3] << std::endl;
	out.close();
}

void load(int id)
{
	char buf[256];
	sprintf(buf, "data/scene%d.dat", id);
	std::ifstream in;
	in.open(buf);
	in >> sunTheta;
	in >> sunPhi;
	in >> cameraHeight;
	in >> cameraTheta;
	in >> gridSize;
	in >> nyquistMin;
	in >> nyquistMax;
	in >> seaColor[0];
	in >> seaColor[1];
	in >> seaColor[2];
	in >> seaColor[3];
	in >> hdrExposure;
	in >> grid;
	in >> animate;
	in >> seaContrib;
	in >> sunContrib;
	in >> skyContrib;
	in >> nbWaves;
	in >> lambdaMin;
	in >> lambdaMax;
	in >> heightMax;
	in >> waveDirection;
	in >> waveDispersion;
	in >> cloudLayer;
	in >> octaves;
	in >> lacunarity;
	in >> gain;
	in >> norm;
	in >> clamp1;
	in >> clamp2;
	in >> cloudColor[0];
	in >> cloudColor[1];
	in >> cloudColor[2];
	in >> cloudColor[3];
	in.close();
	generateMesh();
	generateWaves();
	loadPrograms(true);
	//TwRefreshBar(bar);
}

// ----------------------------------------------------------------------------

double time()
{
#ifdef _WIN32
	__int64 time;
	__int64 cpuFrequency;
	QueryPerformanceCounter((LARGE_INTEGER*) &time);
	QueryPerformanceFrequency((LARGE_INTEGER*) &cpuFrequency);
	return time / double(cpuFrequency);
#else
	static double t0 = 0;
	timeval tv;
	gettimeofday(&tv, NULL);
	if (!t0) {
		t0 = tv.tv_sec;
	}
	return double(tv.tv_sec-t0) + double(tv.tv_usec) / 1e6;
#endif
}

void redisplayFunc()
{
	if (vboParams.x != width2 || vboParams.y != height2 || vboParams.z != gridSize || vboParams.w != cameraTheta) {
		generateMesh();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec4f sun = vec4f(sin(sunTheta) * cos(sunPhi), sin(sunTheta) * sin(sunPhi), cos(sunTheta), 0.0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, skyTex, 0);
	glViewport(0, 0, skyTexSize, skyTexSize);
	glUseProgram(skymap->program);
	glUniform3f(glGetUniformLocation(skymap->program, "sunDir"), sun.x, sun.y, sun.z);
	glUniform1f(glGetUniformLocation(skymap->program, "octaves"), octaves);
	glUniform1f(glGetUniformLocation(skymap->program, "lacunarity"), lacunarity);
	glUniform1f(glGetUniformLocation(skymap->program, "gain"), gain);
	glUniform1f(glGetUniformLocation(skymap->program, "norm"), norm);
	glUniform1f(glGetUniformLocation(skymap->program, "clamp1"), clamp1);
	glUniform1f(glGetUniformLocation(skymap->program, "clamp2"), clamp2);
	glUniform4f(glGetUniformLocation(skymap->program, "cloudsColor"), cloudColor[0], cloudColor[1], cloudColor[2], cloudColor[3]);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glEnd();
	glActiveTexture(GL_TEXTURE0 + SKY_UNIT);
	glGenerateMipmapEXT(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glViewport(0, 0, width2, height2);

	float ch = cameraHeight - meanHeight;

	mat4f view = mat4f(
		0.0, -1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, -ch,
		-1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		);
	view = mat4f::rotatex(cameraTheta / M_PI * 180.0) * view;

	mat4f proj = mat4f::perspectiveProjection(90.0, float(width2) / float(height2), 0.1 * ch, 1000000.0 * ch);

	float worldToWind[4];
	worldToWind[0] = cos(waveDirection);
	worldToWind[1] = sin(waveDirection);
	worldToWind[2] = -sin(waveDirection);
	worldToWind[3] = cos(waveDirection);

	float windToWorld[4];
	windToWorld[0] = cos(waveDirection);
	windToWorld[1] = -sin(waveDirection);
	windToWorld[2] = sin(waveDirection);
	windToWorld[3] = cos(waveDirection);

	glUseProgram(sky->program);
	glUniformMatrix4fv(glGetUniformLocation(sky->program, "screenToCamera"), 1, true, proj.inverse().coefficients());
	glUniformMatrix4fv(glGetUniformLocation(sky->program, "cameraToWorld"), 1, true, view.inverse().coefficients());
	glUniform3f(glGetUniformLocation(sky->program, "worldCamera"), 0.0, 0.0, ch);
	glUniform3f(glGetUniformLocation(sky->program, "worldSunDir"), sun.x, sun.y, sun.z);
	glUniform1f(glGetUniformLocation(sky->program, "hdrExposure"), hdrExposure);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glEnd();

	if (cloudLayer && ch < 3000.0) {
		drawClouds(sun, proj * view);
	}

	glUseProgram(render->program);
	glUniformMatrix4fv(glGetUniformLocation(render->program, "screenToCamera"), 1, true, proj.inverse().coefficients());
	glUniformMatrix4fv(glGetUniformLocation(render->program, "cameraToWorld"), 1, true, view.inverse().coefficients());
	glUniformMatrix4fv(glGetUniformLocation(render->program, "worldToScreen"), 1, true, (proj * view).coefficients());
	glUniformMatrix2fv(glGetUniformLocation(render->program, "worldToWind"), 1, true, worldToWind);
	glUniformMatrix2fv(glGetUniformLocation(render->program, "windToWorld"), 1, true, windToWorld);
	glUniform3f(glGetUniformLocation(render->program, "worldCamera"), 0.0, 0.0, ch);
	glUniform3f(glGetUniformLocation(render->program, "worldSunDir"), sun.x, sun.y, sun.z);
	glUniform1f(glGetUniformLocation(render->program, "hdrExposure"), hdrExposure);

	glUniform1f(glGetUniformLocation(render->program, "nbWaves"), nbWaves);
	glUniform1f(glGetUniformLocation(render->program, "heightOffset"), -meanHeight);
	glUniform2f(glGetUniformLocation(render->program, "sigmaSqTotal"), sigmaXsq, sigmaYsq);
	if (animate) {
		glUniform1f(glGetUniformLocation(render->program, "time"), time());
	}

	glUniform4f(glGetUniformLocation(render->program, "lods"),
		gridSize,
		atan(2.0 / height2) * gridSize, // angle under which a screen pixel is viewed from the camera * gridSize
		log(lambdaMin) / log(2.0f),
		(nbWaves - 1.0f) / (log(lambdaMax) / log(2.0f) -  log(lambdaMin) / log(2.0f)));
	glUniform1f(glGetUniformLocation(render->program, "nyquistMin"), nyquistMin);
	glUniform1f(glGetUniformLocation(render->program, "nyquistMax"), nyquistMax);

	glUniform3f(glGetUniformLocation(render->program, "seaColor"), seaColor[0] * seaColor[3], seaColor[1] * seaColor[3], seaColor[2] * seaColor[3]);

	if (grid) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glVertexPointer(4, GL_FLOAT, 16, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, vboSize, GL_UNSIGNED_INT, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (cloudLayer && ch > 3000.0) {
		drawClouds(sun, proj * view);
	}

	//TwDraw();
	//glutSwapBuffers();
}


NEPHILIM_NS_BEGIN

namespace rzr
{
	


ComponentWater2::ComponentWater2()
{
	ready = false;
}

GLuint transmittanceTex;
GLuint irradianceTex;
GLuint inscatterTex;

void ComponentWater2::init()
{
	Log("Component Water2 Instanced");

	float *data = new float[16*64*3];
	FILE *f = fopen("data/irradiance.raw", "rb");
	if(f) Log("Loading: irradiance.raw");
	fread(data, 1, 16*64*3*sizeof(float), f);
	fclose(f);
	glActiveTexture(GL_TEXTURE0 + IRRADIANCE_UNIT);
	glGenTextures(1, &irradianceTex);
	glBindTexture(GL_TEXTURE_2D, irradianceTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F_ARB, 64, 16, 0, GL_RGB, GL_FLOAT, data);
	delete[] data;

	int res = 64;
	int nr = res / 2;
	int nv = res * 2;
	int nb = res / 2;
	int na = 8;
	f = fopen("data/inscatter.raw", "rb");
	data = new float[nr*nv*nb*na*4];
	fread(data, 1, nr*nv*nb*na*4*sizeof(float), f);
	fclose(f);
	glActiveTexture(GL_TEXTURE0 + INSCATTER_UNIT);
	glGenTextures(1, &inscatterTex);
	glBindTexture(GL_TEXTURE_3D, inscatterTex);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA16F_ARB, na*nb, nv, nr, 0, GL_RGBA, GL_FLOAT, data);
	delete[] data;

	data = new float[256*64*3];
	f = fopen("data/transmittance.raw", "rb");
	fread(data, 1, 256*64*3*sizeof(float), f);
	fclose(f);
	glActiveTexture(GL_TEXTURE0 + TRANSMITTANCE_UNIT);
	glGenTextures(1, &transmittanceTex);
	glBindTexture(GL_TEXTURE_2D, transmittanceTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F_ARB, 256, 64, 0, GL_RGB, GL_FLOAT, data);
	delete[] data;

	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);

	unsigned char* img = new unsigned char[512 * 512 + 38];
	f = fopen("data/noise.pgm", "rb");
	fread(img, 1, 512 * 512 + 38, f);
	fclose(f);
	glActiveTexture(GL_TEXTURE0 + NOISE_UNIT);
	glGenTextures(1, &noiseTex);
	glBindTexture(GL_TEXTURE_2D, noiseTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 512, 512, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, img + 38);
	glGenerateMipmapEXT(GL_TEXTURE_2D);
	delete[] img;

	glActiveTexture(GL_TEXTURE0 + SKY_UNIT);
	glGenTextures(1, &skyTex);
	glBindTexture(GL_TEXTURE_2D, skyTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, skyTexSize, skyTexSize, 0, GL_RGBA, GL_FLOAT, NULL);
	glGenerateMipmapEXT(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0 + WAVE_UNIT);
	glGenTextures(1, &waveTex);
	glBindTexture(GL_TEXTURE_1D, waveTex);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	generateWaves();

	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	generateMesh();

	loadPrograms(true);

	ready = true;
}

void ComponentWater2::render(Renderer* mRenderer)
{
	if(ready)
	{
		redisplayFunc();
	}
}

};

NEPHILIM_NS_END
	*/