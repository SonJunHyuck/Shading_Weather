#include "image.h"

// 헤더 구현체도 헤더에 포함돼있어서 구현체 추가
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Image::~Image()
{
    if (m_data)
    {
        stbi_image_free(m_data);
    }
}

ImageUPtr Image::Load(const std::string &filepath)
{
    auto image = ImageUPtr(new Image());

    if (!image->LoadWithStb(filepath))
        return nullptr;

    SPDLOG_INFO("Success Image Loading : {}", filepath);
    return std::move(image);
}

ImageUPtr Image::Create(int width, int height, int channelCount)
{
    auto image = ImageUPtr(new Image());

    // Load가 아니라, Memory 할당받아서 이미지 만들고 싶음
    if (!image->Allocate(width, height, channelCount))
        return nullptr;

    return std::move(image);
}

ImageUPtr Image::CreateSingleColorImage(int width, int height, const glm::vec4 &color)
{
    glm::vec4 clamped = glm::clamp(color * 255.0f, 0.0f, 255.0f);
    uint8_t rgba[4] = {
        (uint8_t)clamped.r,
        (uint8_t)clamped.g,
        (uint8_t)clamped.b,
        (uint8_t)clamped.a,
    };
    auto image = Create(width, height, 4);
    for (int i = 0; i < width * height; i++)
    {
        memcpy(image->m_data + 4 * i, rgba, 4);
    }
    return std::move(image);
}

ImageUPtr Image::CreateWithData(int width, int height, const std::vector<glm::vec4>& data)
{
    auto image = Create(width, height, 4);
    for (int i = 0; i < width * height; i++)
    {
        glm::vec4 color = data[i];
        uint8_t rgba[4] = { (uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a };
        memcpy(image->m_data + i * 4, rgba, sizeof(rgba));
    }

    return std::move(image);
}

bool Image::LoadWithStb(const std::string &filepath)
{
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channelCount, 0);
    if (!m_data)
    {
        SPDLOG_ERROR("failed to load image: {}", filepath);
        return false;
    }
    return true;
}

bool Image::Allocate(int width, int height, int channelCount) {
    m_width = width;
    m_height = height;
    m_channelCount = channelCount;
    m_data = (uint8_t*)malloc(m_width * m_height * m_channelCount);
    return m_data ? true : false;
}

void Image::SetCheckImage(int gridX, int gridY)
{
    for (int j = 0; j < m_height; j++)
    {
        for (int i = 0; i < m_width; i++)
        {
            int pos = (j * m_width + i) * m_channelCount;
            bool even = ((i / gridX) + (j / gridY)) % 2 == 0;
            uint8_t value = even ? 255 : 0;

            for (int k = 0; k < m_channelCount; k++)
                m_data[pos + k] = value;
            
            if (m_channelCount > 3)
                m_data[3] = 255;
        }
    }
}