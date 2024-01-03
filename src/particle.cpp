#include "particle.h"

ParticleUPtr Particle::Create(const uint32_t inParticleNum, const uint32_t inTailNum, uint32_t primitiveType)
{
    auto particle = ParticleUPtr(new Particle());
    particle->Init(inParticleNum, inTailNum, primitiveType);
    return std::move(particle);
}

void Particle::Draw(const Program* program) const
{
    m_vertexLayout->Bind();
    glDrawArrays(GL_POINTS, 0, tailLength * particleNum);
}

void Particle::Init(const uint32_t inParticleNum, const uint32_t inTailNum, uint32_t primitiveType)
{
    std::vector<float> particleIndexData = std::vector<float>(inParticleNum);
    std::vector<glm::vec2> particlePositionData = std::vector<glm::vec2>(inParticleNum);
    std::vector<float> particleAgeData = std::vector<float>(inParticleNum);
    std::vector<float> particleLifeData = std::vector<float>(inParticleNum);
    
    std::vector<glm::vec2> tailPositionData = std::vector<glm::vec2>(inTailNum);
    std::vector<glm::vec4> tailColorData = std::vector<glm::vec4>(inTailNum);

    float tailLength = inTailNum / inParticleNum;
    for (int i = 0; i < inParticleNum; i++)
    {
        particleIndexData[i] = (float)i;
        particlePositionData[i] = glm::vec2(0);
        particleAgeData[i] = 0;
        particleLifeData[i] = floor(( (float)rand() / (float)RAND_MAX ) * tailLength);
    }

    for (int i = 0; i < inTailNum; i++)
    {
        tailPositionData[i] = glm::vec2(0);
        tailColorData[i] = glm::vec4(1);
    }

    m_vertexLayout = VertexLayout::Create();

    m_particleIndexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, particleIndexData.data(), sizeof(float), inParticleNum);
    m_particleIndexBuffer->Bind();
    m_vertexLayout->SetAttrib(0, 1, GL_FLOAT, false, 0, 0);

    m_particlePositionBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, particlePositionData.data(), sizeof(glm::vec2), inParticleNum);
    m_particlePositionBuffer->Bind();
    m_vertexLayout->SetAttrib(1, 2, GL_FLOAT, false, 0, 0);

    m_particleAgeBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, particleAgeData.data(), sizeof(float), inParticleNum);
    m_particleAgeBuffer->Bind();
    m_vertexLayout->SetAttrib(2, 1, GL_FLOAT, false, 0, 0);

    m_particleLifeBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, particleLifeData.data(), sizeof(float), inParticleNum);
    m_particleLifeBuffer->Bind();
    m_vertexLayout->SetAttrib(3, 1, GL_FLOAT, false, 0, 0);

    m_tailPositionBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, tailPositionData.data(), sizeof(glm::vec2), inTailNum);
    m_tailPositionBuffer->Bind();
    m_vertexLayout->SetAttrib(4, 2, GL_FLOAT, false, 0, 0);

    m_tailColorBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, tailColorData.data(), sizeof(glm::vec4), inTailNum);
    m_tailColorBuffer->Bind();
    m_vertexLayout->SetAttrib(5, 4, GL_FLOAT, false, 0, 0);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_particleIndexBuffer->Get());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_particlePositionBuffer->Get());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_particleAgeBuffer->Get());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_particleLifeBuffer->Get());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, m_tailPositionBuffer->Get());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, m_tailColorBuffer->Get());
}