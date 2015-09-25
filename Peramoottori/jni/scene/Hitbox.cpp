#include <scene\Hitbox.h>

bool pm::Hitbox::CheckCollision(glm::vec2 touchCoordinates)
{
	std::vector<GLfloat> tempVertices = parent->GetComponent<Rectangle>()->GetVertices();
	
	GLfloat left, top, right, bot;

	glm::mat4 invMat = glm::inverse(parent->GetComponent<Transformable>()->GetTransformMatrix());
	glm::mat4 invCamMat = CameraSystem::GetInstance()->GetActiveCamera()->GetInverseCameraMatrix();

	glm::vec2 tempTouch = glm::vec2(invCamMat * glm::vec4(touchCoordinates, 1, 1));
	tempTouch = glm::vec2(invMat* glm::vec4(touchCoordinates, 1, 1));

	left = tempVertices[0];
	top = tempVertices[1];
	right = tempVertices[6];
	bot = tempVertices[7];

	if ((tempTouch.x > left) && (tempTouch.x < right) && (tempTouch.y < top) && (tempTouch.y < bot))
		return true;
	else
		return false;

}