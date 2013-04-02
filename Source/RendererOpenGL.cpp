#include <Nephilim/Platform.h>
#ifdef NEPHILIM_DESKTOP
#include <Nephilim/RendererOpenGL.h>
#include "Nephilim/View.h"
#include "Nephilim/MMath.h"

#include <Nephilim/Engine.h>
#include <Nephilim/Window.h>

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif
#include <GL/gl.h>

NEPHILIM_NS_BEGIN

RendererOpenGL::RendererOpenGL() : Renderer(){

};


void RendererOpenGL::applyView(const View &view){
	if(!m_renderTarget) return;


	IntRect viewport = ((Window*)m_renderTarget)->getViewport(view);
	int top = m_renderTarget->getSize().y - (viewport.top + viewport.height);
	glViewport(viewport.left, top, viewport.width, viewport.height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)width / height, 0.5f, 150);
	FloatRect rect = view.getRect();
	//glOrtho(rect.left, rect.width , rect.height ,rect.top, -0.1f , 0.1f);
	glLoadMatrixf(view.getTransform().getMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TESTLOG("Changed camera.")

};

void RendererOpenGL::enableClipping(FloatRect rect)
{
	FloatRect current;
	if(m_clipRegionStack.empty())
	{
		glEnable(GL_SCISSOR_TEST);

		// full window test
		current = FloatRect(0,0,m_renderTarget->getSize().x, m_renderTarget->getSize().y);
	}
	else
	{
		current = m_clipRegionStack.top();
	}

	// Crop rect if needed and push
	if(rect.left < current.left)
	{
		rect.width = rect.width - current.left - rect.left;
		rect.left = current.left;
	}
	if(rect.top < current.top)
	{
		rect.height = rect.height - current.top - rect.top;
		rect.top = current.top;
	}
	if(rect.left + rect.width > current.left + current.width)
	{
		rect.width = current.left + current.width - rect.left;
	}
	if(rect.top + rect.height > current.top + current.height)
	{
		rect.height = current.top + current.height - rect.top;
	}

	m_clipRegionStack.push(rect);

	activateClipRegion(m_clipRegionStack.top());
}

void RendererOpenGL::activateClipRegion(FloatRect rect)
{
	glScissor(rect.left, m_renderTarget->getSize().y - (rect.top + rect.height), rect.width, rect.height);
}

void RendererOpenGL::disableClipping()
{
	m_clipRegionStack.pop();
	if(m_clipRegionStack.empty())glDisable(GL_SCISSOR_TEST);
	else
	{
		//activate next
		activateClipRegion(m_clipRegionStack.top());
	}
};

/// Clear the bound buffer
void RendererOpenGL::clear(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(m_clearColor.r/255,m_clearColor.g/255,m_clearColor.b/255,1.f);
};


void RendererOpenGL::prepare(int w, int h){
	glViewport(0, 0, w, h);


	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f,0.f,0.3f,0.3f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)width / height, 0.5f, 150);
	glOrtho(0.f,w,h,0.f, -0.1f , 0.1f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
};

void RendererOpenGL::drawCube(float x, float y, float z, float len, Color color){
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, z);

//	srand(2);

	static GLfloat colors[4 * 36];
	static bool colorsAssigned = false;
	if(!colorsAssigned){
		int k = 0;
		for(int i = 0 ; i < 4*36; i++){
			colors[i] = Math::random(0,1);
		}
		colorsAssigned = true;
	}


	//glRotatef( angle * (180.f/3.14159), 0 ,0, 1);
	//glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);
	float dim = len/2;
	GLfloat vertices[] = {len/2,-len/2,-len/2, -len/2,len/2,-len/2, -len/2,-len/2,-len/2,  len/2,-len/2,-len/2,  len/2,len/2,-len/2, -len/2, len/2,-len/2, //front face

						len/2,-len/2,len/2, -len/2,len/2,len/2, -len/2,-len/2,len/2,  len/2,-len/2,len/2,  len/2,len/2,len/2, -len/2, len/2,len/2, //back face

						dim,-dim,-dim,    dim,dim,-dim    , dim,dim,dim    ,  dim,dim,dim,  dim,-dim,dim    , 	dim,-dim,-dim, //right face

						-dim,-dim,-dim,   - dim,dim,-dim    ,- dim,dim,dim    ,  -dim,dim,dim, - dim,-dim,dim    , -	dim,-dim,-dim, //left face

						dim,-dim,-dim,   dim,-dim,dim    , -dim, -dim, dim   ,  -dim, -dim, dim, - dim,-dim,-dim    , dim,-dim,-dim, //top

						dim,dim,-dim,   dim,dim,dim    , -dim, dim, dim   ,  -dim, dim, dim, - dim,dim,-dim    , dim,dim,-dim //bottom


	};



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(4,GL_FLOAT, 0, colors);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
};


void RendererOpenGL::drawDebugQuad(float x, float y, float angle, float width, float height, Color color){
  /*  if(color.a < 255)
        printf("Debugging quad: %f %f     %f      %f %f,    %u %u %u %u\n", x,y,angle,width,height,color.r,color.g,color.b,color.a);*/

//color.a = 255;
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.f);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRotatef( angle * (180.f/3.14159), 0 ,0, 1);
	glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);
	GLfloat vertices[] = {width/2,-height/2,0, -width/2,height/2,0, -width/2,-height/2,0,  width/2,-height/2,0,  width/2,height/2,0, -width/2, height/2,0 };

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void RendererOpenGL::drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color){
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0.5f * color.r , 0.5f * color.g , 0.5f * color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < vcount; ++i)
	{
		glVertex2f(vlist[i].x, vlist[i].y);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vcount; ++i)
	{
		glVertex2f(vlist[i].x, vlist[i].y);
	}
	glEnd();
	glPopMatrix();
}

void RendererOpenGL::drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color){
	const float k_segments = 16.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, color.a);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	glBlendFunc (GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = center + Vec2f(cosf(theta), sinf(theta)) * radius;
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();

	/*Vec2f p = center + radius * axis;
	glBegin(GL_LINES);
	glVertex2f(center.x, center.y);
	glVertex2f(p.x, p.y);
	glEnd();*/
};

void RendererOpenGL::drawVertexArray(VertexArray &vertexArray){

	if(vertexArray.m_vertices.size() == 0)return;

	const char* data = reinterpret_cast<const char*>(&vertexArray.m_vertices[0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), data + 0);
	glColorPointer(4, GL_UNSIGNED_BYTE,sizeof(Vertex), data + 8);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), data + 12);

 	if(vertexArray.geometryType == Triangles)
 		glDrawArrays(GL_TRIANGLES, 0, vertexArray.m_vertices.size());
 	else if(vertexArray.geometryType == TriangleFan )
 		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexArray.m_vertices.size());

	//glDrawArrays(GL_QUADS, 0, vertexArray.m_vertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
};

/// Anything that inherits Drawable can be drawn using a renderer
void RendererOpenGL::draw(Drawable &drawable){
	drawable.onDraw(this);
};

void RendererOpenGL::drawDebugLine(Vec2f begin, Vec2f end, Color color){
	glLoadIdentity();
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	/*glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);*/

	glLineWidth(1);

	glColor4f(color.r / 255.f, color.g / 255.f ,color.b / 255.f,color.a / 255.f);
	GLfloat vertices[] = {begin.x,begin.y,0, end.x,end.y,0};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopAttrib();
	glPopMatrix();
};

void RendererOpenGL::display(){
	//Engine::instance()->getWindow().swapBuffers();
};

NEPHILIM_NS_END
#endif
