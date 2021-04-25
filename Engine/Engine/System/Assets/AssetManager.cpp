#include "AssetManager.h"
#include "../../Core/Types.h"

AssetManager::AssetManager()
{
	InitialiseDefaultTexture();
	InitialiseDefaultSoundBuffer();
}

AssetManager::~AssetManager()
{
}

void AssetManager::InitialiseDefaultTexture()
{
	//initialise the default textrue to bright green
	for (int i = 0; i < (DEFAULT_TEXTURE_WIDTH*DEFAULT_TEXTURE_HEIGHT*4); i+=4)
	{
		m_DefaultTexturePixels[i]	= 0;//red value
		m_DefaultTexturePixels[i+1] = 255;//green value
		m_DefaultTexturePixels[i+2] = 0;//blue value
		m_DefaultTexturePixels[i+3] = 255;//alpha value
	}
	
	m_DefaultTexture.create(DEFAULT_TEXTURE_WIDTH, DEFAULT_TEXTURE_HEIGHT);
	m_DefaultTexture.update(m_DefaultTexturePixels);
	m_DefaultTexture.setRepeated(true);
}

void AssetManager::InitialiseDefaultSoundBuffer()
{
	
	const unsigned SAMPLE_RATE = 44100;
	const unsigned AMPLITUDE = 30000;

	

	const double TWO_PI = 6.28318;
	const double increment = 440.0 / 44100.0;
	double x = 0;

	for (unsigned i = 0; i < NUM_SAMPLES; i++) 
	{
		defaultSoundBufferSamples[i] = (sf::Int16) ((double)AMPLITUDE * sin(x*TWO_PI));
		x += increment;
	}

	m_DefaultSoundBuffer.loadFromSamples(defaultSoundBufferSamples, NUM_SAMPLES, 1, SAMPLE_RATE);

}

sf::Texture& AssetManager::GetTexture(const char* filename)
{
	// look to see if we have already loaded the file

	C_Hash32 filenameHash(filename);

	std::map<unsigned int, sf::Texture>::iterator iter = m_Textures.find(filenameHash.GetHashValue());

	if (iter != m_Textures.end())
	{
		//file is already loaded, return a reference
		return iter->second;
	}

	//file is not loaded.. let's load it now
	if (LoadTextureFromFile(filename))
	{
		return GetTexture(filename);
	}

	//no texture found and could not load from a file.. return default texture
	return m_DefaultTexture;
}

bool AssetManager::LoadTextureFromFile(const char* filename)
{
	sf::Texture texture;
	C_Hash32 filenameHash(filename);

	if (texture.loadFromFile(filename))
	{
		m_Textures[filenameHash.GetHashValue()] = texture;
		return true;
	}

	return false;
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(const char* filename)
{
	// look to see if we have already loaded the file
	C_Hash32 filenameHash(filename);

	std::map<unsigned int, sf::SoundBuffer>::iterator iter = m_SoundBuffers.find(filenameHash.GetHashValue());

	if (iter != m_SoundBuffers.end())
	{
		//file is already loaded, return a reference
		return iter->second;
	}

	//file is not loaded.. let's load it now
	if (LoadSoundBufferFromFile(filename))
	{
		return GetSoundBuffer(filename);
	}

	//no sound found and could not load from a file.. return default sound
	return m_DefaultSoundBuffer;
}

bool AssetManager::LoadSoundBufferFromFile(const char* filename)
{
	sf::SoundBuffer soundBuffer;
	C_Hash32 filenameHash(filename);

	if (soundBuffer.loadFromFile(filename))
	{
		m_SoundBuffers[filenameHash.GetHashValue()] = soundBuffer;
		return true;
	}

	return false;
}

sf::Font* AssetManager::GetFont(const char* filename)
{
	// look to see if we have already loaded the file
	C_Hash32 filenameHash(filename);

	std::map<unsigned int, sf::Font>::iterator iter = m_Fonts.find(filenameHash.GetHashValue());

	if (iter != m_Fonts.end())
	{
		//file is already loaded, return a reference
		return &(iter->second);
	}

	//file is not loaded.. let's load it now
	if (LoadFontFromFile(filename))
	{
		return GetFont(filename);
	}

	//no font found and could not load from a file.. return NULL
	return NULL;
}

bool AssetManager::LoadFontFromFile(const char* filename)
{
	sf::Font font;
	C_Hash32 filenameHash(filename);

	if (font.loadFromFile(filename))
	{
		m_Fonts[filenameHash.GetHashValue()] = font;
		return true;
	}

	return false;
}

