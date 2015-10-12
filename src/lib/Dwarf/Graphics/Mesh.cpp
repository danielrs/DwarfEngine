/* #include <Dwarf/Graphics/Mesh.h> */
/* #include <Dwarf/Util/Logger.h> */
/* #include <Dwarf/Util/ResourceManager.h> */

/* #include <assimp/Importer.hpp> */
/* #include <assimp/scene.h> */
/* #include <assimp/postprocess.h> */

/* using namespace Dwarf::Math; */
/* using namespace Dwarf::Util; */

/* using namespace std; */
/* using namespace Assimp; */

/* namespace Dwarf { */
/* 	namespace Graphics { */

/* 		MeshResource::Vertex::Vertex() {} */

/* 		MeshResource::Vertex::Vertex(const VectorN<float, 3> &position) { */
/* 			this->position = position; */
/* 		} */

/* 		MeshResource::Vertex::Vertex(const VectorN<float, 3> &position, const VectorN<float, 2> &tex_coord) { */
/* 			this->position = position; */
/* 			this->tex_coord = tex_coord; */
/* 		} */

/* 		MeshResource::Vertex::Vertex(const VectorN<float, 3> &position, const VectorN<float, 2> &tex_coord, const VectorN<float, 3> &normal) { */
/* 			this->position = position; */
/* 			this->tex_coord = tex_coord; */
/* 			this->normal = normal; */
/* 		} */

/* 		// ------------------ */

/* 		MeshResource::MeshEntry::MeshEntry() {} */

/* 		MeshResource::MeshEntry::~MeshEntry() { */
/* 			free(); */
/* 		} */

/* 		void MeshResource::MeshEntry::free() { */
/* 			if (glIsBuffer(VBO)) glDeleteBuffers(1, &VBO); */
/* 			if (glIsBuffer(IBO)) glDeleteBuffers(1, &IBO); */
/* 			num_indices = 0; */
/* 			material_index = 0; */
/* 		} */

/* 		void MeshResource::MeshEntry::init(const vector<Vertex> &vertices, const vector<int> &indices) { */
/* 			free(); */

/* 			glCreateBuffers(1, &VBO); */
/* 			glCreateBuffers(1, &IBO); */

/* 			glBindBuffer(GL_ARRAY_BUFFER, VBO); */
/* 			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW); */
/* 			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); */
/* 			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW); */
/* 		} */

/* 		// ------------------ */

/* 		MeshResource::MeshResource() {} */

/* 		MeshResource::~MeshResource() { */
/* 			unload(); */
/* 		} */

/* 		void MeshResource::unload() { */
/* 			entries.clear(); */
/* 			textures.clear(); */
/* 		} */

/* 		void MeshResource::load(const string &filename) { */
/* 			unload(); */

/* 			Importer importer; */
/* 			const aiScene *scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs); */

/* 			if (scene) { */
/* 				entries.resize(scene->mNumMeshes); */
/* 				textures.resize(scene->mNumMaterials); */

/* 				// Initialize the meshes in the scene one by one */
/* 				for (unsigned int i = 0; i < entries.size(); ++i) { */
/* 					const aiMesh* mesh = scene->mMeshes[i]; */
/* 					initMesh(i, mesh); */
/* 					initMaterials(scene, filename); */
/* 				} */
/* 			} else { */
/* 				Logger::log(Logger::V_WARNING, "[%s:%d] Error parsing '%s': '%s'\n", __FILE__, __LINE__, filename.c_str(), importer.GetErrorString()); */
/* 			} */
/* 		} // load */

/* 		void MeshResource::initMesh(unsigned int index, const aiMesh *mesh) { */
/* 			entries[index].material_index = mesh->mMaterialIndex; */

/* 			std::vector<Vertex> vertices; */
/* 			std::vector<int> indices; */

/* 			const aiVector3D zero3D(0.0f, 0.0f, 0.0f); */

/* 			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) { */
/* 				const aiVector3D *pos = &(mesh->mVertices[i]); */
/* 				const aiVector3D *normal = &(mesh->mNormals[i]); */
/* 				const aiVector3D *tex_coord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero3D; */

/* 				VectorN<float, 3> vpos; */
/* 				VectorN<float, 2> vtex; */
/* 				VectorN<float, 3> vnor; */

/* 				vpos[0] = pos->x; vpos[1] = pos->y; vpos[2] = pos->z; */
/* 				vtex[0] = tex_coord->x; vtex[1] = tex_coord->y; */
/* 				vnor[0] = normal->x; vnor[1] = normal->y; vnor[2] = normal->z; */

/* 				vertices.push_back(Vertex(vpos, vtex, vnor)); */
/* 			} // for */

/* 			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) { */
/* 				const aiFace &face = mesh->mFaces[i]; */
/* 				indices.push_back(face.mIndices[0]); */
/* 				indices.push_back(face.mIndices[1]); */
/* 				indices.push_back(face.mIndices[2]); */
/* 			} // for */

/* 			entries[index].init(vertices, indices); */

/* 		} // initMesh */

/* 		void MeshResource::initMaterials(const aiScene *scene, const string &filename) { */
/* 			for (unsigned int i = 0; i < scene->mNumMaterials; ++i) { */
/* 				const aiMaterial *material = scene->mMaterials[i]; */
/* 				textures[i] = NULL; */
/* 				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) { */
/* 					aiString path; */
/* 					if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) { */
/* 						string fullpath = /1* DIR *1/ string("/") + path.data; */
/* 						textures[i] = ResourceManager::INSTANCE().load<Texture2D>(fullpath); */
/* 					} */
/* 				} */
/* 			} // for */
/* 		} // Mesh */

/* 		void MeshResource::render() const { */

/* 			glEnableVertexAttribArray(0); */
/* 			glEnableVertexAttribArray(1); */
/* 			glEnableVertexAttribArray(2); */

/* 			for (unsigned int i = 0; i < entries.size(); ++i) { */

/* 				glBindBuffer(GL_ARRAY_BUFFER, entries[i].VBO); */
/* 				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); */
/* 				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(float[3])); */
/* 				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(float[5])); */

/* 				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entries[i].IBO); */

/* 				const unsigned int material_index = entries[i].material_index; */

/* 				glDrawElements(GL_TRIANGLES, entries[i].num_indices, GL_UNSIGNED_INT, 0); */
/* 			} */

/* 			glDisableVertexAttribArray(0); */
/* 			glDisableVertexAttribArray(1); */
/* 			glDisableVertexAttribArray(2); */

/* 		} */

/* 	} // namespace Graphics */
/* } // namespace Dwarf */
