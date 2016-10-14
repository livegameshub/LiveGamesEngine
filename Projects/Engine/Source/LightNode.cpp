#include "LightNode.h"

namespace ai
{
	LightNode::LightNode(glm::u32 id, glm::i32 type)
		: BasicNode(id, LIGHT_NODE)
		, mSpecularColor(1.0f)
		, mDiffuseColor(1.0f)
		, mLightType(type)
	{
	}

	LightNode::LightNode(glm::u32 id, glm::i32 type, const glm::vec3& diffuse)
		: BasicNode(id, LIGHT_NODE)
		, mSpecularColor(1.0f)
		, mDiffuseColor(diffuse)
		, mLightType(type)
	{
	}

	LightNode::LightNode(glm::u32 id, glm::i32 type, const glm::vec3& diffuse, const glm::vec3& specular)
		: BasicNode(id, LIGHT_NODE)
		, mSpecularColor(specular)
		, mDiffuseColor(diffuse)
		, mLightType(type)
	{
	}

	LightNode::~LightNode()
	{
	}

	void LightNode::setLightType(glm::i32 type)
	{
		mLightType = type;
	}

	void LightNode::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void LightNode::setSpecularColor(const glm::vec3& color)
	{
		mSpecularColor = color;
	}

	const glm::vec3& LightNode::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	const glm::vec3& LightNode::getSpecularColor() const
	{
		return mSpecularColor;
	}

	glm::i32 LightNode::getLightType() const
	{
		return mLightType;
	}
}
