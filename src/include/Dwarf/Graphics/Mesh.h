/* // see: http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html */

/* #ifndef DWARF_GRAPHICS_MESH_H */
/* #define DWARF_GRAPHICS_MESH_H */

/* #include "../DwarfSetup.h" */
/* #include GLEW_H */
/* #include "Texture2D.h" */
/* #include "../Math/VectorN.h" */
/* #include "../Util/Resource.h" */

/* #include <memory> */
/* #include <string> */
/* #include <vector> */

/* // Forward declarations */
/* struct aiScene; */
/* struct aiMesh; */

/* namespace Dwarf { */
/* 	namespace Graphics { */

/* 		class DWARFAPI MeshResource : public Util::Resource { */
/* 		public: */
/* 			MeshResource(); */
/* 			~MeshResource(); */

/* 			void unload() override; */
/* 			void load(const std::string &filename) override; */

/* 			void render() const; */

/* 		private: */
/* 			void initFromScene(const aiScene* scene, const std::string &filename); */
/* 			void initMesh(unsigned int index, const aiMesh* paiMesh); */
/* 			void initMaterials(const aiScene* scene, const std::string &filename); */
/* 			void clear(); */

/* 			struct Vertex { */
/* 				Math::VectorN<float, 3> position; */
/* 				Math::VectorN<float, 2> tex_coord; */
/* 				Math::VectorN<float, 3> normal; */

/* 				Vertex(); */
/* 				Vertex(const Math::VectorN<float, 3> &position); */
/* 				Vertex(const Math::VectorN<float, 3> &position, const Math::VectorN<float, 2> &tex_coord); */
/* 				Vertex(const Math::VectorN<float, 3> &position, const Math::VectorN<float, 2> &tex_coord, const Math::VectorN<float, 3> &normal); */
/* 			}; */

/* 			struct MeshEntry { */

/* 				GLuint VBO; */
/* 				GLuint IBO; */

/* 				unsigned int num_indices; */
/* 				unsigned int material_index; */

/* 				MeshEntry(); */
/* 				~MeshEntry(); */

/* 				void free(); */
/* 				void init(const std::vector<Vertex> &vertices, const std::vector<int> &indices); */
/* 			}; */

/* 			std::vector<MeshEntry> entries; */
/* 			std::vector<Texture2D> textures; */
/* 		}; */
/* 		using Mesh = std::shared_ptr<MeshResource>; */
/* 	} */
/* } */
/* #endif */
