#pragma once
 
// Skydome, czyli oteksturowana pó³kula imituj¹ca niebo.
class CSkydome  
{
public:
	struct vec3 {
		float x, y, z;
	};
	vec3 Position; // Pozycja obiektu na scenie.
	vec3 Rotation;
	CSkydome(void);
	~CSkydome(void);
	void Initialize(GLuint tex);
	void Update(void);
	void Render(void);
	void Set_texture(GLuint tex);
protected:
	GLuint _displayListId;
	GLuint skyTexture;
};