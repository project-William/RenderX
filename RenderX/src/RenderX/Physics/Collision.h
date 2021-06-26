#pragma once
#include "pch.h"
#include "../Core/RenderScene.h"

namespace renderx::physics
{
	class Collision
	{
	public:
		Collision();
		~Collision();


		void TestCollision();

	private:

		std::unordered_map<std::string, Core::BoundingBox>& m_RenderersMapRef;
		std::unordered_map<std::string, Core::Transform>& m_TransformMapRef;
		
	};
}