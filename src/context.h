#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "quad.h"
#include "particle.h"
#include "framebuffer.h"

CLASS_PTR(Context)
class Context
{
private:
    Context() {}
public:
    ~Context() {}

public:
    static ContextUPtr Create();
    void Render();
    void Reshape(int width, int height);
    void IncrementFrameCount() { m_currentFrame++; }

private:
    bool Init();

    ProgramUPtr m_particleProgram;
    ProgramUPtr m_mapProgram;
    ProgramUPtr m_postProgram;
    ProgramUPtr m_computeProgram;

    TexturePtr m_windowTexture;
    TexturePtr m_worldTexture;
    TexturePtr m_windTexture;
    TexturePtr m_particleStateTexture;

    QuadUPtr m_worldQuad;
    QuadUPtr m_screenQuad;

    ParticleUPtr m_particles;

    // clear color
    glm::vec4 m_clearColor { glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) };

    // framebuffer
    FramebufferUPtr m_framebuffer;

    // window
    int m_width { WINDOW_WIDTH };
    int m_height { WINDOW_HEIGHT };

    // frame
    int m_currentFrame { 0 };
    float m_particleResolution { 0 };
};

#endif // __CONTEXT_H__