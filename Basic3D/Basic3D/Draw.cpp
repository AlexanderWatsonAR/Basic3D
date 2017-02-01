#include "stdafx.h"
#include <iostream>
#include "Draw.h"

namespace Basic3D
{
	namespace Draw
	{
		void Draw::DrawModel(const SceneObject * sceneObject)
		{
			Mesh * mesh = MeshLoader::GetMesh(sceneObject->meshID);
			glBindTexture(GL_TEXTURE_2D, *sceneObject->texID);

			glMaterialfv(GL_FRONT, GL_AMBIENT, &sceneObject->material.Ambient.x);
			glMaterialfv(GL_FRONT, GL_SPECULAR, &sceneObject->material.Specular.x);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &sceneObject->material.Diffuse.x);
			glMaterialf(GL_FRONT, GL_SHININESS, sceneObject->material.Shininess);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glPushMatrix();

			glScalef(sceneObject->scale.x, sceneObject->scale.y, sceneObject->scale.z);
			glTranslatef(sceneObject->position.x, sceneObject->position.y, sceneObject->position.z);
			glRotatef(sceneObject->heading, 0, 1, 0);
			glRotatef(sceneObject->pitch, 1, 0, 0);
			glRotatef(sceneObject->roll, 0, 0, 1);

			for (unsigned int i = 0; i < mesh->indices.size(); i++)
			{
				glVertexPointer(3, GL_FLOAT, 0, &mesh->vertices[0]);
				glNormalPointer(GL_FLOAT, 0, &mesh->normals[0]);
				glTexCoordPointer(2, GL_FLOAT, 0, &mesh->texCoords[0]);

				glDrawElements(GL_TRIANGLES, mesh->indices[i].size(), GL_UNSIGNED_SHORT, &mesh->indices[i][0]);
			}

			glPopMatrix();

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		void Draw::DrawString(const char* text, Vector3 position)
		{
			glPushMatrix();

			glDisable(GL_TEXTURE);
			glDisable(GL_LIGHTING);
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(position.x, position.y, position.z);
			glRasterPos2f(0.0f, 0.0f);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE);

			glPopMatrix();
		}
	}
}