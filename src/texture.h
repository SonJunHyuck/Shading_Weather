#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "image.h"

CLASS_PTR(Texture)
class Texture
{
private:
    Texture() {}

public:
    ~Texture();

public:
    static TextureUPtr Create(int width, int height, uint32_t format);
    static TextureUPtr CreateFromImage(const Image *image);    
    static TextureUPtr CreateFromImage(const Image *image, uint32_t minFilter, uint32_t magFilter);
    static TextureUPtr CreateFromImage(const Image *image, uint32_t minFilter, uint32_t magFilter, uint32_t sWrap, uint32_t tWrap);

    const uint32_t Get() const { return m_texture; }
    void Bind() const;
    void SetFilter(uint32_t minFilter, uint32_t magFilter) const;
    void SetWrap(uint32_t sWrap, uint32_t tWrap) const;

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    uint32_t GetFormat() const { return m_format; }

private:
    void CreateTexture();  // bool이 아니라 void -> 무조건 성공을 가정
    void CreateTexture(uint32_t minFilter, uint32_t magFilter);
    void CreateTexture(uint32_t minFilter, uint32_t magFilter, uint32_t sWrap, uint32_t tWrap);
    void SetTextureFromImage(const Image *image);
    void SetTextureFormat(int width, int height, uint32_t format);

    uint32_t m_texture{0};
    int m_width{0};
    int m_height{0};
    uint32_t m_format{GL_RGBA};
};

#endif // __TEXTURE_H__