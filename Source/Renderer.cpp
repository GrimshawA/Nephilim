#include "Nephilim/Renderer.h"
#include "Nephilim/View.h"

#ifdef PARABOLA_DESKTOP
#include <Nephilim/RendererOpenGL.h>
#elif defined PARABOLA_ANDROID || defined PARABOLA_IPHONE
#include <Nephilim/RendererGLES.h>
#endif

PARABOLA_NAMESPACE_BEGIN
/// Auto detects an appropriate renderer
Renderer* Renderer::createAutomaticRenderer(RenderTarget* target){
	
#ifdef PARABOLA_DESKTOP
	RendererOpenGL* renderer = new RendererOpenGL();
	renderer->m_renderTarget = target;
	return renderer;
#elif defined PARABOLA_ANDROID	|| defined PARABOLA_IPHONE
	RendererGLES* renderer = new RendererGLES();
	renderer->m_renderTarget = target;
	return renderer;
#else
	return NULL;
#endif
};

Renderer::Renderer(){
	m_clearColor.r = 100;
	m_clearColor.g = 10;
};


/// Set the currently active view
void Renderer::setView(const View &view){
	m_currentView = view;
	applyView(m_currentView);
};

/// Activate view and push it to the stack
void Renderer::pushView(const View& view){
	m_viewStack.push(view);
	applyView(view);
};

/// Pop the current active view
void Renderer::popView(){
	m_viewStack.pop();
	if(!m_viewStack.empty()){
		applyView(m_viewStack.top());
	}
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

void Renderer::drawRocketContext(RocketContext* context){

}

void Renderer::drawVertexArray(VertexArray &vertexArray){

}
PARABOLA_NAMESPACE_END