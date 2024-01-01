#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "common.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "program.h"

struct ParticleAttribute
{
    float index;
    glm::vec2 position;
    float age;
    float life;
};

struct TailAttribute
{
    glm::vec2 positions;
    glm::vec4 tailColors;
};


CLASS_PTR(Particle);
class Particle
{
public:
    static ParticleUPtr Create(const uint32_t inParticleNum, const uint32_t inTailLength, uint32_t primitiveType);

    const VertexLayout *GetVertexLayout() const { return m_vertexLayout.get(); }
    const uint32_t GetParticleNum() const { return particleNum; }
    const float GetTailLength() const { return tailLength; }
    
    void SetParticleNum(uint32_t inParticleNum) { particleNum = inParticleNum; }
    void SetTailLength(float inTailLength) { tailLength = inTailLength; }

    void Draw(const Program* program) const;

private:
    Particle() {}
    void Init(const uint32_t inParticleNum, const uint32_t inTailLength, uint32_t primitiveType);

    uint32_t m_primitiveType{GL_POINTS};
    VertexLayoutUPtr m_vertexLayout;
    
    BufferPtr m_particleIndexBuffer;
    BufferPtr m_particlePositionBuffer;
    BufferPtr m_particleAgeBuffer;
    BufferPtr m_particleLifeBuffer;
    BufferPtr m_tailPositionBuffer;
    BufferPtr m_tailColorBuffer;

    uint32_t particleNum { 1024 * 32 };
    float tailLength { 256 };
};

#endif // __PARTICLE_H__