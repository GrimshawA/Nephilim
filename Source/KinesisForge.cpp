#include "Nephilim/KinesisForge.h"
#include "Nephilim/MMath.h"

#include "Nephilim/TextStream.h"
#include "Nephilim/Kinesis.h"

#include "Nephilim/StringList.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Builds the forge over a world, it must stay alive while the forge is doing any operations on it
KinesisForge::KinesisForge(KinesisWorld* workWorld) : m_world(workWorld){
	
};

/// Creates a rope in the simulation, not attached to anything unless specified
std::vector<KinesisBodyActor*> KinesisForge::createRope(const Vec2f &position, float angle, float ropeLength, int segmentCount, float segmentWidth){
	std::vector<KinesisBodyActor*> actorList;

	Vec2f pos(position); //store the new positions

	// need to build n segments
	for(int i = 0; i < segmentCount ; i++){
		KinesisBodyActor* body = m_world->CreateQuickBox(pos.x, pos.y, ropeLength/segmentCount, segmentWidth);
		
		//KinesisBodyActor* body = new KinesisBodyActor(m_world->CreateQuickCircle(pos.x, pos.y, ropeLength/segmentCount/2));
		body->setAngle(angle);
		pos.x += cos(angle)*ropeLength/segmentCount;
		pos.y += sin(angle)*ropeLength/segmentCount;
		actorList.push_back(body);

		//attach to previous
		if(i > 0){
			//there is a previous to attach to
			b2RopeJointDef jdef;			
			jdef.bodyA = actorList[i-1]->m_body;
			jdef.bodyB = actorList[i]->m_body;
			jdef.collideConnected = true;
			jdef.localAnchorA = jdef.localAnchorB = b2Vec2(0,0);
			//jdef.localAnchorA = b2Vec2( m_world->ToMeters((cos(angle)*ropeLength/segmentCount/2) - 1) , m_world->ToMeters((sin(angle)*ropeLength/segmentCount/2) - 1));
			//jdef.localAnchorB = b2Vec2(- m_world->ToMeters(cos(angle)*ropeLength/segmentCount/2) ,-m_world->ToMeters(sin(angle)*ropeLength/segmentCount/2));
			//jdef.localAnchorA = b2Vec2(m_world->ToMeters(cos(angle)*ropeLength/segmentCount/2) - 0.05f ,m_world->ToMeters(sin(angle)*ropeLength/segmentCount/2) - 0.05f);
			//jdef.localAnchorB = -jdef.localAnchorA;
			jdef.maxLength = m_world->ToMeters(15);
			m_world->CreateJoint(&jdef);
		}
	}


	b2Body* staticB = m_world->CreateStaticBox(position.x, position.y, 2,2);
	b2RevoluteJointDef def;
	def.Initialize(staticB, actorList[0]->m_body, staticB->GetWorldCenter());
	def.collideConnected = false;
	m_world->CreateJoint(&def);
	

	return actorList;
}



















	KinesisWorldDefinition::KinesisWorldDefinition(){

	};

	bool KinesisWorldDefinition::LoadFromFile(String FileName, KinesisWorld *changeWorld){

		/*TextFileStream in(FileName, StreamMode::ReadOnly);

		if(!in.valid())
			return false;
		
		char c;
		while(!in.Ended()){
			c = in.GetChar();
			
			if(c == '#'){
				in.AdvanceLine();
				continue;
			}
			else if(c == ' ' || c == '\n' || c == '\t'){
				//nothing to do with these things
			}
			else{
				//a comment wasnt found, and this is a valid char, belongs to a name
				
				in.OffsetPosition(-1);
				String blockname = in.ReadWord();
				String block = in.ReadWithin('{', '}');

				//cout<<"Block : "<<blockname<<endl;
				//cout<<"Content: "<<block<<endl;

				LoadBlock(blockname, block, changeWorld);
			}

							

		}*/

		return true;
	};

	bool KinesisWorldDefinition::LoadBlock(String BlockName, String BlockContent, KinesisWorld *changeWorld){

		BlockDefinition Block;
		BlockProperties Properties;

		//Check what kind of block it is, and imediatly analyze it, on the fly.
		BlockName.toLowerCase();
		if(BlockName == "world"){

		}
		else if(BlockName == "script"){

		}
		else{
			//object specification
			StringList objecttype /*= BlockName.split(".", 1)*/;

			if(objecttype[0] == "body"){
				cout<<"Loading body: "<<objecttype[1]<<endl;
				KinesisBodyDefinition BodyDef = ParseBodyDefinition(BlockContent);
				BodyDef.Name = objecttype[1];
				BodyDefinitions[objecttype[1]] = BodyDef;					
				
				SpawnBody(BodyDef, changeWorld);
			}
			else if(objecttype[0] == "joint"){

			}
			else{
				//unkown content
				cout<<"Unkown block: "<<BlockName<<endl;
			}

		}
		
		return true;
	};

	KinesisBodyDefinition KinesisWorldDefinition::ParseBodyDefinition(String content){
		KinesisBodyDefinition def;

		BlockSettings BodySettings = ParseBlockSettings(content);

		//all this block settings are in place, just iterate and store.
		cout<<"Body has "<<BodySettings.Settings.size()<<" properties set."<<endl;

		for(unsigned int i = 0; i < BodySettings.Settings.size(); i++){
			String propertyname = BodySettings.Settings[i].first;
			String propertydef = BodySettings.Settings[i].second;

			propertyname.toLowerCase();
			propertydef.toLowerCase();

			if(propertyname == "spawn"){
				def.Spawn = propertydef.toBoolean();
			}
			else if(propertyname == "position"){
				//def.Origin = propertydef.ToVec2f();
				//pDebug() << def.Origin;
			}
			else if(propertyname == "bodytype"){
				if(propertydef == "dynamic")
					def.BodyType = b2_dynamicBody;
				else if(propertydef == "static")
					def.BodyType = b2_staticBody;
				else if(propertydef == "kinematic")
					def.BodyType = b2_kinematicBody;
				else
					def.BodyType = b2_staticBody;
				
			}
			else{
				cout<<"Unknown property was set: "<<propertyname<<endl;
			}
		}

		//Now process children - for now assume there is only one level depth
		for(unsigned int i = 0; i < BodySettings.ChildSettings.size(); i++){
			String KindOfInnerBlock = BodySettings.ChildSettings[i].first;
			KindOfInnerBlock.toLowerCase();

			if(KindOfInnerBlock == "shape"){
				KinesisShapeDefinition ShapeDef;
			
				for(unsigned int j = 0; j < BodySettings.ChildSettings[i].second.Settings.size(); j++ ){
					String propertyname = BodySettings.ChildSettings[i].second.Settings[j].first;
					String propertydef = BodySettings.ChildSettings[i].second.Settings[j].second;

					propertyname.toLowerCase();
					propertydef.toLowerCase();

					if(propertyname == "shapetype"){
						unsigned int Type;
	
						if(propertydef == "box"){
							Type = KinesisShapeDefinition::BoxShape;
						}
						else if(propertydef == "circle"){
							Type = KinesisShapeDefinition::CircleShape;
						}
						else if(propertydef == "chain"){
							Type = KinesisShapeDefinition::ChainShape;
						}
						else{
							cout<<"Unknown shape type: "<<propertydef<<endl;
						}

						ShapeDef.ShapeType = Type;
					}
					else if(propertyname == "dimensions"){
					//	ShapeDef.Dimensions = propertydef.ToVec2f();
					}
					else if(propertyname == "density"){
						ShapeDef.Density = propertydef.toFloat();
					}
					else if(propertyname == "friction"){
						ShapeDef.Friction = propertydef.toFloat();
					}
					else if(propertyname == "pin"){
						//ShapeDef.Pin = propertydef.ToVec2f();
					}
					else{
						cout<<"Unknown property defined for: "<<KindOfInnerBlock<<"("<<propertyname<<")"<<endl;
					}
				}

				def.Shapes.push_back(ShapeDef);
			}
		}

		return def;
	};

	bool KinesisWorldDefinition::SpawnBody(KinesisBodyDefinition &BodyDef, KinesisWorld *world){
		if(!world)return false; //cant spawn in a null world.

		if(!BodyDef.Spawn){
			cout<<"You can't spawn this body."<<endl;
			return false;
		}

		b2BodyDef bdef;
		bdef.position = b2Vec2(BodyDef.Origin.x/world->getPixelRatio(),BodyDef.Origin.y/world->getPixelRatio() );
		bdef.type = BodyDef.BodyType;

	//	bdef.allowSleep = true; //to set
		//bdef.fixedRotation = false; //to set
		//bdef.gravityScale = 1.f; //to set		

		b2Body *body = world->CreateBody(&bdef);


		//go through the shapes and add them to the body
		for(unsigned int i = 0; i < BodyDef.Shapes.size(); i++){
			b2FixtureDef ShapeFixture;
			b2PolygonShape box;
			b2CircleShape circle;
			b2Shape *shape = 0;

			if(BodyDef.Shapes[i].ShapeType == KinesisShapeDefinition::BoxShape){
				box.SetAsBox(BodyDef.Shapes[i].Dimensions.x/world->getPixelRatio(), BodyDef.Shapes[i].Dimensions.y/world->getPixelRatio(), b2Vec2(BodyDef.Shapes[i].Pin.x/world->getPixelRatio(), BodyDef.Shapes[i].Pin.y/world->getPixelRatio()), 0);
				shape = &box;
				ShapeFixture.shape = &box;
			}
			else if(BodyDef.Shapes[i].ShapeType == KinesisShapeDefinition::CircleShape){
				shape = &circle;
				circle.m_p = b2Vec2(BodyDef.Shapes[i].Pin.x/world->getPixelRatio(), BodyDef.Shapes[i].Pin.y/world->getPixelRatio());
				circle.m_radius = BodyDef.Shapes[i].Dimensions.x/world->getPixelRatio();
					
				ShapeFixture.shape = &circle;
			}

			ShapeFixture.density = BodyDef.Shapes[i].Density;
			ShapeFixture.friction = BodyDef.Shapes[i].Friction;
			ShapeFixture.restitution = 0.5f;
			
			if(BodyDef.BodyType == b2_staticBody){
				ShapeFixture.density = 0.f;

			}else{

				cout<<"Creating dynamic body"<<endl;
				cout<<"Density: "<<ShapeFixture.density<<endl;
				cout<<"Friction: "<<ShapeFixture.friction<<endl;
				cout<<"Restitution: "<<ShapeFixture.restitution<<endl;
							
				
			}
		
			if(shape != 0)
				body->CreateFixture(&ShapeFixture);
		}

		return true;
	};



	KinesisWorldDefinition::BlockSettings KinesisWorldDefinition::ParseBlockSettings(String content){
		BlockSettings settings;
/*
		StringStream in(content);

		while(!in.atEnd()){
			String name = in.ReadWord();
			String def;

			if(name.length() == 0){
				cout<<"No more properties left."<<endl;
				continue;
			}
			else{
				//cout<<"Found: "<<name<<endl;
				name.toLowerCase();

				//If the property found is a block type, nest its content into this setting file.
				//This allows unlimited depth for settings :)
				if(name == "shape"){
					def = in.ReadWithin('{', '}');
					in.OffsetPosition(1);
					BlockSettings childSetting = ParseBlockSettings(def);
					settings.ChildSettings.push_back(std::make_pair<String, BlockSettings>(name, childSetting));
				}
				else{ //single line property
					def = in.ReadUntil(';');
					def.removeCharacter(' ');
					def.removeCharacter(':');
					BlockProperty prop;
					prop.first = name;
					prop.second = def;
					settings.Settings.push_back(prop);
				}


			}
		}*/

		return settings;
	}





	/************************************************************************/
	/* Body                                                                     */
	/************************************************************************/

	KinesisBodyDefinition::KinesisBodyDefinition(){
		
	};

NEPHILIM_NS_END