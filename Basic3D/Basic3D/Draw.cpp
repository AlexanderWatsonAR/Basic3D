#include "stdafx.h"
#include "Draw.h"

namespace Basic3D
{
	namespace Draw
	{
		void Draw::DrawModel(SceneObject * sceneObject)
		{
			Model* model = sceneObject->model;
			Mesh * mesh = MeshLoader::GetMesh(model->meshID);
			glBindTexture(GL_TEXTURE_2D, *model->tex->GetID());

			glMaterialfv(GL_FRONT, GL_AMBIENT, &model->material.Ambient.x);
			glMaterialfv(GL_FRONT, GL_SPECULAR, &model->material.Specular.x);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &model->material.Diffuse.x);
			glMaterialf(GL_FRONT, GL_SHININESS, model->material.Shininess);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glPushMatrix();

			SceneObject* parent = sceneObject->parent;
			while (parent != nullptr)
			{
				parent->transform->Update();
				parent = parent->parent;
			}

			sceneObject->transform->Update();

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

			for (int i = 0; i < 5; i++)
			{
				if (sceneObject->children[i] != nullptr)
					Draw::DrawModel(sceneObject->children[i]);
			}
		}

		void Draw::DrawString(const char* text, Colour colour, Vector3 position, Vector2 rasterPos)
		{
			glPushMatrix();

			glDisable(GL_TEXTURE);
			glDisable(GL_LIGHTING);
			glEnable(GL_COLOR);
			glColor4f(colour.r, colour.g, colour.b, colour.a);
			glTranslatef(position.x, position.y, position.z);
			glRasterPos2f(rasterPos.x, rasterPos.y);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
			glDisable(GL_COLOR);
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE);

			glPopMatrix();
		}

		void Draw::DrawCube(int size, Colour colour, Vector3 position)
		{
			glPushMatrix();

			glDisable(GL_TEXTURE);
			glEnable(GL_COLOR);
			glColor4f(colour.r, colour.g, colour.b, colour.a);
			glTranslatef(position.x, position.y, position.z);
			glutSolidCube(size);
			glDisable(GL_COLOR);
			glEnable(GL_TEXTURE);

			glPopMatrix();
		}
	}
}