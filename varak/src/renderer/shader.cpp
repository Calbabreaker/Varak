#include "varak/renderer/shader.h"
#include "varak/renderer/renderer.h"

#include "opengl/opengl_shader.h"

#include <filesystem>
#include <fstream>

namespace Varak {

    const char* shaderTypeName(ShaderType shaderType)
    {
        switch (shaderType)
        {
        case ShaderType::Vertex: return "vertex";
        case ShaderType::Fragment: return "fragment";
        case ShaderType::None: return "none";
        default: VR_CORE_ASSERT_MSG(false, "Unknown shader type!"); return "";
        }
    }

    static void parseShaderFile(const std::string& filepath, ShaderSourcesMap& outShaderSources)
    {
        std::ifstream inFile(filepath);
        VR_CORE_ASSERT_RELEASE(inFile, "File does not exist at {0}!", filepath);

        std::string line;
        ShaderType currentType = ShaderType::None;

        while (std::getline(inFile, line))
        {
            // is a shader type declaration
            if (line.find("#type") != std::string::npos)
            {
                // get the type
                if (line.find("vertex") != std::string::npos)
                    currentType = ShaderType::Vertex;
                else if (line.find("fragment") != std::string::npos)
                    currentType = ShaderType::Fragment;
                else
                    VR_CORE_ASSERT_MSG(false, "Invalid shader type specified!");
            }
            else if (currentType != ShaderType::None)
            {
                std::string& source = outShaderSources[currentType];
                source += line;
                source += '\n';
            }
        }
    }

    std::shared_ptr<Shader> Shader::create(const std::string& filepath)
    {
        ShaderSourcesMap shaderSources;
        parseShaderFile(filepath, shaderSources);

        std::filesystem::path path = filepath;
        std::string name = path.stem().string();

        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLShader>(name, shaderSources);

        default: VR_CORE_ASSERT_MSG(false, "Shader unimplemented for api!"); return nullptr;
        }
    }

    void ShaderLibrary::add(const std::shared_ptr<Shader>& shader)
    {
        add(shader->getName(), shader); //
    }

    void ShaderLibrary::add(const std::string& name, const std::shared_ptr<Shader>& shader)
    {
        VR_CORE_ASSERT_MSG(!exists(name), "Shader '{}' already exists!", name);
        m_shaders[name] = shader;
    }

    std::shared_ptr<Shader> ShaderLibrary::load(const std::string& name,
                                                const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    std::shared_ptr<Shader> ShaderLibrary::load(const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    std::shared_ptr<Shader> ShaderLibrary::get(const std::string& name)
    {
        VR_CORE_ASSERT_MSG(exists(name), "Shader '{}' does not exist!", name);
        return m_shaders[name];
    }

    bool ShaderLibrary::exists(const std::string& name)
    {
        return m_shaders.find(name) != m_shaders.end(); //
    }

} // namespace Varak
