#include "Nephilim/Renderer.h"
#include "Nephilim/View.h"

#ifdef NEPHILIM_DESKTOP
#include <Nephilim/RendererOpenGL.h>
#elif defined PARABOLA_ANDROID || defined PARABOLA_IPHONE
#include <Nephilim/RendererGLES.h>
#endif

NEPHILIM_NS_BEGIN
/// Auto detects an appropriate renderer
Renderer* Renderer::createAutomaticRenderer(RenderTarget* target){

#ifdef NEPHILIM_DESKTOP
	RendererOpenGL* renderer = new RendererOpenGL();
	renderer->m_renderTarget = target;
//	printf("OpenGL Renderer\n");
	return renderer;
#elif defined PARABOLA_ANDROID	|| defined PARABOLA_IPHONE
	RendererGLES* renderer = new RendererGLES();
	renderer->m_renderTarget = target;
	return renderer;
#else
    TESTLOG("Warning: Tried to create a renderer and failed.\n");
	return NULL;
#endif
};

Renderer::Renderer(){
	m_clearColor.r = 100;
	m_clearColor.g = 10;
};


/// Set the currently active view
void Renderer::setView(const View &view){
/*	m_currentView = view;
	applyView(m_currentView);*/
};

/// Activate view and push it to the stack
void Renderer::pushView(const View& view){
	/*m_viewStack.push(view);
	applyView(view);*/
};

/// Pop the current active view
void Renderer::popView(){
	/*m_viewStack.pop();
	if(!m_viewStack.empty()){
		applyView(m_viewStack.top());
	}*/
};

void Renderer::drawCube(float x, float y, float z, float len, Color color){

};

void Renderer::setDefaultViewRect(float x, float y){
	View v;
	v.setRect(0,0,x,y);
	setView(v);
};


/// Clear the bound buffer
void Renderer::clear(){

};

void Renderer::drawVertexArray(VertexArray &vertexArray){

}
NEPHILIM_NS_END
