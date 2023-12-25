#ifndef __QUAD_H__
#define __QUAD_H__

#include "common.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "program.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
};

CLASS_PTR(Quad);
class Quad
{
public:
    static QuadUPtr Create(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, uint32_t primitiveType);
    static QuadUPtr CreateQuad();

    const VertexLayout *GetVertexLayout() const { return m_vertexLayout.get(); }
    BufferPtr GetVertexBuffer() const { return m_vertexBuffer; }
    BufferPtr GetIndexBuffer() const { return m_indexBuffer; }

    void Draw(const Program* program) const;

private:
    Quad() {}
    void Init(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, uint32_t primitiveType);

    uint32_t m_primitiveType{GL_TRIANGLES};
    VertexLayoutUPtr m_vertexLayout;
    BufferPtr m_vertexBuffer;
    BufferPtr m_indexBuffer;
};

#endif // __QUAD_H__