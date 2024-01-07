#include "context.h"
#include "image.h"
#include <imgui.h>

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

void Context::Reshape(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
    m_framebuffer = Framebuffer::Create( Texture::Create(width, height, GL_RGBA) );
}

bool Context::Init()
{
    // shader
    m_particleProgram = Program::Create("./shader/particle.vs", "./shader/particle.fs");
    if (!m_particleProgram)
      return false;
    SPDLOG_INFO("tail program id: {}", m_particleProgram->Get());

    m_mapProgram = Program::Create("./shader/map.vs", "./shader/map.fs");
    if (!m_mapProgram)
      return false;
    SPDLOG_INFO("quad program id: {}", m_mapProgram->Get());

    m_postProgram = Program::Create("./shader/texture.vs", "./shader/texture.fs");
    if (!m_postProgram)
      return false;
    SPDLOG_INFO("post program id: {}", m_postProgram->Get());

    // compute shader
    m_computeProgram = Program::Create("./shader/compute.cs");
    if (!m_computeProgram)
      return false;
    SPDLOG_INFO("compute program id: {}", m_computeProgram->Get());

    // texture
    m_worldTexture = Texture::CreateFromImage(Image::Load("./images/world.png").get());
    m_windTexture = Texture::CreateFromImage(Image::Load("./images/wind.png").get(), GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

    // quad
    m_worldQuad = Quad::CreateQuad();
    m_screenQuad = Quad::CreateQuad();

    // particle
    int particleNum = 1024 * 32 * 8;
    int tailLength = 256;
    m_particleResolution = ceil(sqrt(particleNum));
    particleNum = m_particleResolution * m_particleResolution;  // sqrt 후 재보정

    // particle state texture
    std::vector<glm::vec4> particleState = std::vector<glm::vec4>((double)particleNum);
    for (int i = 0; i < particleState.size(); i++)
    {
      uint8_t r = floor(((float)rand() / (float)RAND_MAX) * 256);
      uint8_t g = floor(((float)rand() / (float)RAND_MAX) * 256);
      uint8_t b = floor(((float)rand() / (float)RAND_MAX) * 256);
      uint8_t a = floor(((float)rand() / (float)RAND_MAX) * 256);
  
      particleState[i] = glm::vec4(r, g, b, a);
    }
    m_particleStateTexture = Texture::CreateFromImage(Image::CreateWithData(m_particleResolution, m_particleResolution, particleState).get(), GL_NEAREST, GL_NEAREST);

    m_particles = Particle::Create(particleNum, particleNum * tailLength, GL_POINTS);
    m_particles->SetParticleNum(particleNum);
    m_particles->SetTailLength(tailLength);
    m_particles->m_particleMAX = particleNum;
    m_particles->m_tailLengthMAX = tailLength;

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

    return true;
}

void Context::Render()
{
    // begin, end pair -> UI Window #imgui
    if (ImGui::Begin("Wind Params"))
    {
        if(ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_clearColor)))
        {
            glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
        }
        ImGui::Separator();

        int particleNum = m_particles->GetParticleNum();
        if(ImGui::InputInt("Particle Number", &particleNum, 1024, 2048))
        {
          m_particles->SetParticleNum(glm::clamp<int>(particleNum, 0, m_particles->m_particleMAX));
        }
        
        ImGui::Value("Particle Count", m_particles->GetParticleNum());
        ImGui::Value("Tail Length", m_particles->GetTailLength());
        ImGui::Value("Total Vertex Count", m_particles->GetParticleNum() * m_particles->GetTailLength());
        ImGui::Separator();
    }
    ImGui::End();

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    m_framebuffer->GetColorAttachment()->Bind();
    glActiveTexture(GL_TEXTURE1);
    m_windTexture->Bind();
    glActiveTexture(GL_TEXTURE2);
    m_particleStateTexture->Bind();
    glActiveTexture(GL_TEXTURE3);
    m_worldTexture->Bind();

    // active compute shader
    glUseProgram(m_computeProgram->Get());
    m_computeProgram->SetUniform("current_frame", m_currentFrame);
    m_computeProgram->SetUniform("particle_res", m_particleResolution);
    m_computeProgram->SetUniform("tail_length", m_particles->GetTailLength());
    m_computeProgram->SetUniform("wind_texture", 1);
    m_computeProgram->SetUniform("particle_texture", 2);
    glDispatchCompute(m_particles->GetParticleNum() / (m_particles->GetTailLength()), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

    // on the framebuffer
    m_framebuffer->Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // drawm world map
    m_mapProgram->Use();
    m_mapProgram->SetUniform("tex", 3);
    m_worldQuad->Draw(m_mapProgram.get());

    // draw particle
    m_particleProgram->Use();
    m_particles->Draw(m_particleProgram.get());

    // off the framebuffer
    Framebuffer::BindToDefault();

    // rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    m_postProgram->Use();
    m_postProgram->SetUniform("tex", 0);
    m_screenQuad->Draw(m_postProgram.get());
}