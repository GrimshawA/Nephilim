#include "Razer.h"

class Model;

mat4 view = mat4::lookAt(vec3(0, 5, 5), vec3(0,0,0), vec3(0,1,0));

class Model
{
public:
	Model()
	{
		m_texture = -1;
	}

	mat4 getTransform()
	{
		return mat4::translate(m_position.x, m_position.y, m_position.z);
	}

	vec3 m_position;
	GeometryData m_data;
	int m_texture;
	String filename;
};


std::vector<Model*> objects;
Model* selected = NULL;


/// First attempt at a scene format
class Scene
{
public:
	std::vector<Texture*> textureobjects;

	bool load(String filename)
	{
		File file(filename, IODevice::BinaryRead);
		DataStream ds(file);

		Int64 textureCount, modelCount;
		ds >> textureCount;
		for(int i = 0; i < textureCount; ++i)
		{
			String textureFilename;
			ds >> textureFilename;
			textures.push_back(textureFilename);

			Texture* texture = new Texture();
			texture->loadFromFile(textureFilename);
			texture->setRepeated(true);
			textureobjects.push_back(texture);

			Log("Loaded texture: %s", textureFilename.c_str());
		}

		ds >> modelCount;
		for(int i = 0; i < modelCount; ++i)
		{
			String modelFilename;
			Int64 textureID;
			ds >> modelFilename >> textureID;

			Model* data = new Model();
			data->m_data.loadFromFile(modelFilename);
			data->m_texture = textureID;

			ds >> data->m_position.x >> data->m_position.y >> data->m_position.z;

			objects.push_back(data);
			models.push_back(data);

			selected = data;

			Log("Loaded model: %s", modelFilename.c_str());
		
		}

		return true;
	}

	bool save(String filename)
	{
		File file(filename, IODevice::BinaryWrite);

		DataStream ds(file);

		ds << static_cast<Int64>(textures.size());
		for(size_t i = 0; i < textures.size(); ++i)
		{
			ds << textures[i];
		}

		ds << static_cast<Int64>(models.size());
		for(size_t i = 0; i < models.size(); ++i)
		{
			ds << models[i]->filename;
			ds << static_cast<Int64>(models[i]->m_texture);
			ds << models[i]->m_position.x << models[i]->m_position.y << models[i]->m_position.z;
		}

		return true;
	}

	std::vector<String> textures;
	std::vector<Model*> models;
};

Scene scene;


void Razer::onCreate()
{
	m_interface.setRect(FloatRect(0,0,1024,768));
	if(!m_interface.getContext().m_defaultFont.loadFromFile("assets/DejaVuSans.ttf"))
	{
		Log("Font not found.");
	}

	UIButton* button = new UIButton("Load model");
	button->setPosition(100,100);
	button->setSize(300,60);
	button->onClick.connect(MAKE_SLOT_LOCAL(Razer, onLoadModel));
	m_interface["top"]->addControl(button);

	UIButton* button2 = new UIButton("Load texture");
	button2->setPosition(100,160);
	button2->setSize(300,60);
	button2->onClick.connect(MAKE_SLOT_LOCAL(Razer, onLoadTexture));
	m_interface["top"]->addControl(button2);

	UIButton* button3 = new UIButton("Save scene");
	button3->setPosition(100,220);
	button3->setSize(300,60);
	button3->onClick.connect(MAKE_SLOT_LOCAL(Razer, onSaveScene));
	m_interface["top"]->addControl(button3);

	UIButton* button4 = new UIButton("Load scene");
	button4->setPosition(100,280);
	button4->setSize(300,60);
	button4->onClick.connect(MAKE_SLOT_LOCAL(Razer, onLoadScene));
	m_interface["top"]->addControl(button4);
}

void Razer::onLoadModel()
{
	FileDialog loadDialog;
	loadDialog.title = "Load your model";
	loadDialog.filter = "Geometry Files (*.ngx)\0*.ngx\0";
	loadDialog.initialPath = "K:/Users/Hellhound/Desktop/NephilimScene2/";
	String modelFile = loadDialog.load();

	if(modelFile.size() > 0)
	{
		Log("Load model %s", modelFile.c_str());

		Model* data = new Model();
		data->m_data.loadFromFile(modelFile);
		data->filename = modelFile;
		objects.push_back(data);

		scene.models.push_back(data);
		selected = data;
	}
}

void Razer::onLoadTexture()
{
	FileDialog loadDialog;
	loadDialog.title = "Load your texture";
	loadDialog.filter = "Image Files (*.png, *.jpg)\0*.png;*.jpg\0";
	loadDialog.initialPath = "K:/Users/Hellhound/Desktop/NephilimScene2/maps/";
	String textureFile = loadDialog.load();

	if(textureFile.size() > 0)
	{
		Log("Load texture %s", textureFile.c_str());

		Texture* texture = new Texture();
		texture->loadFromFile(textureFile);
		texture->setRepeated(true);
		scene.textureobjects.push_back(texture);
		scene.textures.push_back(textureFile);
	}
}

void Razer::onSaveScene()
{
	FileDialog saveDialog;
	saveDialog.title = "Save your scene";
	saveDialog.filter = "Experimental Razer Scene (*.rsx)\0*.rsx\0";
	String sceneFile = saveDialog.save();

	if(!sceneFile.empty())
	{
		if(scene.save(sceneFile))
		{
			Log("Scene stored: %s", sceneFile.c_str());
		}
	}
}

void Razer::onLoadScene()
{
	FileDialog loadDialog;
	loadDialog.title = "Load your scene";
	loadDialog.filter = "Experimental Razer Scene (*.rsx)\0*.rsx\0";
	loadDialog.initialPath = "K:/Users/Hellhound/Desktop/NephilimScene2/";

	String sceneFile = loadDialog.load();

	if(!sceneFile.empty())
	{
		if(scene.load(sceneFile))
		{
			Log("Scene loaded: %s", sceneFile.c_str());
		}
	}
}



bool mousePress = false;
vec2 previousMouse;

void Razer::onEvent(Event &event)
{
	m_interface.pushEvent(event);
	input.update(event);

	if(event.type == Event::MouseButtonPressed)
	{
		mousePress = true;
		previousMouse = vec2(event.mouseButton.x,event.mouseButton.y);
	}
	if(event.type == Event::MouseButtonReleased)
	{
		mousePress = false;
	}
	if(event.type == Event::MouseMoved)
	{
		if(mousePress)
		{
			vec2 currentMouse = vec2(event.mouseMove.x,event.mouseMove.y);

			//Calculate movement
			vec2 mouseMove = currentMouse - previousMouse;

			vec3 point3 = (view * vec4(mouseMove.x, mouseMove.y, 0.f, 1.f)).xyz();

			point3.normalize();
			if(selected) selected->m_position += point3 * 0.3;

			previousMouse = currentMouse;
		}

	}

	if(event.type == Event::KeyPressed)
	{
		if(event.key.code == Keyboard::Up)
		{
			if(selected) selected->m_position.y += 1;
		}
		if(event.key.code == Keyboard::Down)
		{
			if(selected) selected->m_position.y -= 1;
		}
		if(event.key.code == Keyboard::Left)
		{
			if(selected) selected->m_position.x -= 1;
		}
		if(event.key.code == Keyboard::Right)
		{
			if(selected) selected->m_position.x += 1;
		}

		if(event.key.code == Keyboard::RControl)
		{
			if(selected)
			{
				// Cycle texture
				if(selected->m_texture == -1 && scene.textureobjects.size() > 0)
				{
					selected->m_texture = 0;
				}
				else if(scene.textureobjects.size() > 0 && selected->m_texture != -1)
				{
					selected->m_texture++;
					if(selected->m_texture == scene.textureobjects.size()) selected->m_texture = 0;
				}
			}
		}
	}
}

void Razer::onUpdate(Time time)
{
	m_interface.update(time.asSeconds());
}

void Razer::onRender(Renderer* renderer)
{
	// Draw 3D
	renderer->setDepthTestEnabled(true);
	renderer->clearDepthBuffer();
	renderer->setProjectionMatrix(mat4::perspective(80, static_cast<float>(renderer->getSurface().getWidth()) / static_cast<float>(renderer->getSurface().getHeight()), 1.f, 1000.f));
	renderer->setViewMatrix(view);
	renderer->setModelMatrix(mat4::identity);
	renderer->setDefaultTexture();
	

	for(size_t i = 0; i < objects.size(); ++i)
	{
		if(objects[i]->m_texture >= 0) scene.textureobjects[objects[i]->m_texture]->bind();
		else renderer->setDefaultTexture();

		renderer->setModelMatrix(objects[i]->getTransform());
		renderer->draw(objects[i]->m_data);
	}

	// Draw 2D
	renderer->setProjectionMatrix(View(0,0,1024,768).getMatrix());
	renderer->setViewMatrix(mat4::identity);
	renderer->setModelMatrix(mat4::identity);
	renderer->setDefaultTexture();
	renderer->setDepthTestEnabled(false);

	renderer->draw(m_interface);
}
