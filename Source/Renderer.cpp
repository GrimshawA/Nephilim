#include <Nephilim/Renderer.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Drawable.h>

NEPHILIM_NS_BEGIN

Renderer::Renderer()
: m_shader(NULL)
{
	m_clearColor.r = 100;
	m_clearColor.g = 10;

	m_primitiveTable[Render::Primitive::Triangles] = static_cast<int>(GL_TRIANGLES);
	m_primitiveTable[Render::Primitive::TriangleFan] = static_cast<int>(GL_TRIANGLE_FAN);
};

void Renderer::drawArrays(Render::Primitive::Type primitiveType, int start, int count)
{
	glDrawArrays(static_cast<GLenum>(m_primitiveTable[primitiveType]), static_cast<GLint>(start), static_cast<GLsizei>(count));
}

void Renderer::enableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(static_cast<GLuint>(index));
}

void Renderer::disableVertexAttribArray(unsigned int index)
{
	glDisableVertexAttribArray(static_cast<GLuint>(index));
}

void Renderer::setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr)
{
	glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(numComponents), static_cast<GLenum>(componentType), static_cast<GLboolean>(normalized), static_cast<GLsizei>(stride), static_cast<const GLvoid*>(ptr));
}

/// Draw a vertex array
void Renderer::draw(const VertexArray& varray)
{
	TESTLOG("Why are you calling draw on an abstract base class?\n")
}

/// Allows a drawable to draw itself
void Renderer::draw(Drawable &drawable)
{
	drawable.onDraw(this);
}


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
	glClear(GL_COLOR_BUFFER_BIT);
};

void Renderer::drawVertexArray(VertexArray &vertexArray){

}
NEPHILIM_NS_END
