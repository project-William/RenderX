#include "pch.h"


namespace renderx::Core
{
	struct BoundingBox
	{
		
		//
		glm::vec3 BoxMin = glm::vec3(INT_MIN);
		glm::vec3 BoxMax = glm::vec3(INT_MAX);
		glm::vec3 m_Center = glm::vec3(0.0f);

		float m_Radius;
		bool m_UseRadius;

		BoundingBox() {}
		BoundingBox(glm::vec3 min_, glm::vec3 max_)
		{
			BoxMin = min_;
			BoxMax = max_;
		}

		// Assign from another bounding box.
		BoundingBox& operator =(const BoundingBox& rhs)
		{
			BoxMin = rhs.BoxMin;
			BoxMax = rhs.BoxMax;
			return *this;
		}


		//AABB - AABB collision
		bool Intersect(BoundingBox& target)
		{
			return (BoxMin.x <= target.BoxMax.x && BoxMax.x >= target.BoxMin.x) &&
				(BoxMin.y <= target.BoxMax.y && BoxMax.y >= target.BoxMin.y) &&
				(BoxMin.z <= target.BoxMax.z && BoxMax.z >= target.BoxMin.z);
		}

		// Return center.
		//glm::vec3 Center() const { return (BoxMax + BoxMin) * 0.5f; }
		glm::vec3 Center() const { return m_Center; }
		// Return size.
		glm::vec3 Size() const { return BoxMax - BoxMin; }


		void TransformOfTranslation(const glm::vec3& translation)
		{
			BoxMin += translation;
			BoxMax += translation;
		}

		void ResetCenter(const glm::vec3& translation)
		{
			m_Center = translation;
		}

		BoundingBox Transformed(glm::mat4 transform)
		{
			glm::vec3 newCenter = (glm::mat3)transform * Center();
			glm::vec3 oldEdge = Size() * 0.5f;
			glm::vec3 newEdge = glm::vec3(
				glm::abs(transform[0][0]) * oldEdge.x + glm::abs(transform[0][1]) * oldEdge.y + glm::abs(transform[0][2]) * oldEdge.z,
				glm::abs(transform[1][0]) * oldEdge.x + glm::abs(transform[1][1]) * oldEdge.y + glm::abs(transform[1][2]) * oldEdge.z,
				glm::abs(transform[2][0]) * oldEdge.x + glm::abs(transform[2][1]) * oldEdge.y + glm::abs(transform[2][2]) * oldEdge.z
			);

			return BoundingBox(newCenter - newEdge, newCenter + newEdge);
		}

		void Transform(glm::mat4& tr, glm::vec3& pos)
		{
			glm::mat3 transform = (glm::mat3)tr;
			glm::vec3 newCenter = transform * Center();
			glm::vec3 oldEdge = Size() * 0.5f;
			glm::vec3 newEdge = glm::vec3(
				glm::abs(transform[0][0]) * oldEdge.x + glm::abs(transform[0][1]) * oldEdge.y + glm::abs(transform[0][2]) * oldEdge.z,
				glm::abs(transform[1][0]) * oldEdge.x + glm::abs(transform[1][1]) * oldEdge.y + glm::abs(transform[1][2]) * oldEdge.z,
				glm::abs(transform[2][0]) * oldEdge.x + glm::abs(transform[2][1]) * oldEdge.y + glm::abs(transform[2][2]) * oldEdge.z
			);
			BoxMin = (newCenter - newEdge) + pos;
			BoxMax = (newCenter + newEdge) + pos;
		}



		template<class Archive>
		void Serialize(Archive& ar)
		{
			ar(BoxMin.x, BoxMin.y, BoxMin.z);
			ar(BoxMax.x, BoxMin.y, BoxMax.z);
			ar(m_Radius);
		}

	};
}