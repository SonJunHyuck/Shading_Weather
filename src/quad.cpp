#include "quad.h"

QuadUPtr Quad::Create(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, uint32_t primitiveType)
{
    auto quad = QuadUPtr(new Quad());
    quad->Init(vertices, indices, primitiveType);
    return std::move(quad);
}

QuadUPtr Quad::CreateQuad() 
{
  std::vector<Vertex> vertices = {
    Vertex { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
    Vertex { glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
    Vertex { glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
    Vertex { glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
  };

  std::vector<uint32_t> indices = { 0,  1,  2,  2,  3,  0, };

  return Create(vertices, indices, GL_TRIANGLES);
}

void Quad::Draw(const Program* program) const
{
    m_vertexLayout->Bind();
    glDrawElements(m_primitiveType, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
}

void Quad::Init(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, uint32_t primitiveType)
{
    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.data(), sizeof(Vertex), vertices.size());
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices.data(), sizeof(uint32_t), indices.size());
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, false, sizeof(Vertex), 0); // pos
    m_vertexLayout->SetAttrib(1, 2, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, texCoord));
}