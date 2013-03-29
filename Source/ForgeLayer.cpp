#include <Nephilim/ForgeLayer.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Constructs the layer
ForgeWorldLayer::ForgeWorldLayer() : m_hidden(false), m_name("null"){

};

/// Construct directly with a name
ForgeWorldLayer::ForgeWorldLayer(const String &name) : m_hidden(false), m_name(name){

};

/// Attach a node as a child
void ForgeWorldLayer::attachNode(ForgeWorldNode* node){
	m_nodes.push_back(node);
};

/// Destroy a child node
void ForgeWorldLayer::destroyNode(ForgeWorldNode* node){
	for(std::list<ForgeWorldNode*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++){
		if((*it) == node){
			it = m_nodes.erase(it);
			return ;
		}
	}
};

/// Get the name of this layer
String ForgeWorldLayer::getName(){
	return m_name;
};

/// Render the layer of the world
void ForgeWorldLayer::draw(Renderer* renderer){
	//if(!m_hidden) return; // no rendering

	//cout<<"drawing "<<m_nodes.size()<< " nodes"<<endl;

	//render graph
	for(std::list<ForgeWorldNode*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++){
		(*it)->draw(renderer);
	}
};

NEPHILIM_NS_END