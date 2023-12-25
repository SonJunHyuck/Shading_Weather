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
    // ========== Create & Attach & Link ========= (create shader func has covered program clas)
    // m_program = Program::Create("./shader/lighting.vs", "./shader/lighting.fs");
    // if (!m_program)
    //     return false;
    // SPDLOG_INFO("program id: {}", m_program->Get());

    // m_textureProgram = Program::Create("./shader/map.vs", "./shader/map.fs");
    // if (!m_textureProgram)
    //   return false;
    // SPDLOG_INFO("program id: {}", m_textureProgram->Get());

    // shader
    m_quadProgram = Program::Create("./shader/texture.vs", "./shader/texture.fs");
    if (!m_quadProgram)
      return false;
    SPDLOG_INFO("program id: {}", m_quadProgram->Get());

    // texture
    m_worldTexture = Texture::CreateFromImage(Image::Load("./images/world.png").get());

    m_worldQuad = Quad::CreateQuad();

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

    return true;
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // begin, end pair -> UI Window #imgui
    if (ImGui::Begin("Wind Params"))
    {
        if(ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_clearColor)))
        {
            glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
        }
        ImGui::Separator();
    }
    ImGui::End();

    //m_framebuffer->Bind();
    m_quadProgram->Use();
    m_worldTexture->Bind();
    m_quadProgram->SetUniform("tex", 0);
    m_worldQuad->Draw(m_quadProgram.get());
}