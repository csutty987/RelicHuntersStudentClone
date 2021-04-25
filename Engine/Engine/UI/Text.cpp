#include "Text.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"

Text::Text()
	:m_Initialised(false)
{

}

Text::~Text()
{
	
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(&m_Text);
}

void Text::Initialise(const char* filename, std::string text, int size, int posX, int posY, sf::Color color, bool isUIObject)
{
	AssetManager* pAssetManager = C_SysContext::Get<AssetManager>();
	m_Text.setFont(*pAssetManager->GetFont(filename));

	m_Text.setPosition(posX, posY);
	m_Text.setString(text);
	m_Text.setCharacterSize(size); // in pixels, not points!
	m_Text.setFillColor(color);
	//m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	if (isUIObject)
	{
		C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_Text);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->AddRenderObject(&m_Text);
	}

	m_Initialised = true;
}
