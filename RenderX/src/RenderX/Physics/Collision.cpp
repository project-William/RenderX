#include "pch.h"
#include "Collision.h"

namespace renderx::physics
{
	Collision::Collision()
		:m_RenderersMapRef(Core::RenderScene::Get()->GetBBoxMapRef())
		,m_TransformMapRef(Core::RenderScene::Get()->GetRenderersTransformRef())
	{

	}

	Collision::~Collision()
	{

	}


	void Collision::TestCollision()
	{
		for (auto iter = m_TransformMapRef.begin(); iter != m_TransformMapRef.end(); iter++)
		{
			for (auto it = m_TransformMapRef.begin(); it != m_TransformMapRef.end(); it++)
			{

			}
		}
	}

}