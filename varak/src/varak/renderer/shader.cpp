#include "vrpch.h"

#include "varak/renderer/shader.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_shader.h"

namespace Varak {

    Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::create(const std::string& filepath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLShader>(filepath);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::add(const Ref<Shader>& shader)
    {
        add(shader->getName(), shader); //
    }

    void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
    {
        VR_CORE_ASSERT_MSG(!exists(name), "Shader '{0}' already exists!", name);
        m_shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string& name)
    {
        VR_CORE_ASSERT_MSG(exists(name), "Shader '{0}' does not exist!", name);
        return m_shaders[name];
    }

    bool ShaderLibrary::exists(const std::string& name)
    {
        return m_shaders.find(name) != m_shaders.end(); //
    }

} // namespace Varak
