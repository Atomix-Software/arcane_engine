#include <arcpch.h>

#include "Arcane/Render/SubTexture.h"

namespace Arcane
{
	SubTexture2D::SubTexture2D(const Shared<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) :
		m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}
	Shared<SubTexture2D> SubTexture2D::CreateFromCoords(const Shared<Texture2D>& texture, const glm::vec2& cellPos, const glm::vec2& cellSize)
	{
		glm::vec2 min = { (cellPos.x * cellSize.x) / texture->GetWidth(), (cellPos.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((cellPos.x + 1) * cellSize.x) / texture->GetWidth(), ((cellPos.y + 1) * cellSize.y) / texture->GetHeight() };

		return CreateShared<SubTexture2D>(texture, min, max);
	}
}