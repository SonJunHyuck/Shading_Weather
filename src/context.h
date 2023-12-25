#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "quad.h"
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

private:
    // particle
    struct Particle
    {
        glm::vec2 position;
        glm::vec2 tail;
        glm::vec4 tail_color;
        int m_tail_length;
        float life;
        float age;
    };

    bool Init();

    //ProgramUPtr m_program;
    //ProgramUPtr m_textureProgram;
    ProgramUPtr m_quadProgram; 

    // ModelUPtr m_model; // Backpack
    TexturePtr m_windowTexture;
    TexturePtr m_worldTexture;

    QuadUPtr m_worldQuad;

    // clear color
    glm::vec4 m_clearColor { glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) };

    // framebuffer
    FramebufferUPtr m_framebuffer;

    // window
    int m_width { WINDOW_WIDTH };
    int m_height { WINDOW_HEIGHT };

    // frame
    int m_currentFrame;
};

#endif // __CONTEXT_H__