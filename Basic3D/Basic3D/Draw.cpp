#include "stdafx.h"
#include "Draw.h"

namespace Basic3D
{
	namespace Draw
	{
		void DrawSGnodes(SGnode* node)
		{
			SceneObject* sceneObject = node->object;
			Mesh * mesh = MeshLoader::GetMesh(sceneObject->meshID);
			glBindTexture(GL_TEXTURE_2D, *sceneObject->tex->GetID());

			glMaterialfv(GL_FRONT, GL_AMBIENT, &sceneObject->material.Ambient.x);
			glMaterialfv(GL_FRONT, GL_SPECULAR, &sceneObject->material.Specular.x);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &sceneObject->material.Diffuse.x);
			glMaterialf(GL_FRONT, GL_SHININESS, sceneObject->material.Shininess);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glPushMatrix();

			if (node->parent != nullptr)
			{
				glTranslatef(node->parent->object->position.x, node->parent->object->position.y, node->parent->object->position.z);
				glScalef(node->parent->object->scale.x, node->parent->object->scale.y, node->parent->object->scale.z);
				glRotatef(node->parent->object->heading, 0, 1, 0);
				glRotatef(node->parent->object->pitch, 1, 0, 0);
				glRotatef(node->parent->object->roll, 0, 0, 1);
			}

			glTranslatef(sceneObject->position.x, sceneObject->position.y, sceneObject->position.z);
			glScalef(sceneObject->scale.x, sceneObject->scale.y, sceneObject->scale.z);
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

			if (node->child != nullptr)
				Draw::DrawSGnodes(node->child);
		}

		void Draw::DrawModel(GLuint meshID, Texture2D* tex, Material material)
		{
			Draw::DrawModel(new SceneObject(meshID, tex, material));
		}

		void Draw::DrawModel(GLuint meshID, Texture2D* tex, Material material,
					   Vector3 position, Vector3 scale, GLfloat heading,
					   GLfloat pitch, GLfloat roll, BoundingBox* box,
					   bool billboard)
		{
			Draw::DrawModel(new SceneObject(meshID, tex, material, position, scale, heading, pitch, roll, box, billboard));
		}

		void Draw::DrawModel(SceneObject * sceneObject)
		{
			Mesh * mesh = MeshLoader::GetMesh(sceneObject->meshID);
			glBindTexture(GL_TEXTURE_2D, *sceneObject->tex->GetID());

			glMaterialfv(GL_FRONT, GL_AMBIENT, &sceneObject->material.Ambient.x);
			glMaterialfv(GL_FRONT, GL_SPECULAR, &sceneObject->material.Specular.x);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &sceneObject->material.Diffuse.x);
			glMaterialf(GL_FRONT, GL_SHININESS, sceneObject->material.Shininess);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glPushMatrix();

			glTranslatef(sceneObject->position.x, sceneObject->position.y, sceneObject->position.z);
			glScalef(sceneObject->scale.x, sceneObject->scale.y, sceneObject->scale.z);
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