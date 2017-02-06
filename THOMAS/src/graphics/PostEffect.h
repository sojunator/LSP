#pragma once
#include "Shader.h"
#include "Texture.h"
#include <map>
namespace thomas
{
	namespace graphics
	{
		class PostEffect
		{
		private:
			virtual PostEffect* CreateInstance(std::string name, Shader* shader) { return NULL; }

		public:

			PostEffect(std::string shader);
			PostEffect(std::string name, Shader* shader);
			~PostEffect();


			static bool Init();
			static PostEffect* CreatePostEffect(std::string name, std::string postEffectType);
			static bool RegisterNewPostEffectType(std::string type, PostEffect* postFX);

			static PostEffect* GetPostEffectByName(std::string name);

			static std::vector<PostEffect*> GetLoadedPostEffects();
			static std::vector<PostEffect*> GetPostEffectByShader(Shader* shader);

			static void Render(ID3D11ShaderResourceView* prePostFXRender, ID3D11RenderTargetView* backBuffer);
			static void Clear();
			static void Destroy();

			bool RenderPostEffect(ID3D11ShaderResourceView* prevRender, ID3D11RenderTargetView* backBuffer=NULL);
			bool Bind();
			bool Unbind();

			virtual void Update(){};

			std::string GetName();
			Shader* GetShader();

			ID3D11ShaderResourceView* GetShaderResource();
			ID3D11RenderTargetView* GetRenderTarget();

		private:
			static std::vector<PostEffect*> s_loadedEffects;
			static std::map<std::string, PostEffect*> s_postEffectTypes;
			static ID3D11Buffer* s_quadVertexBuffer;
			static PostEffect* s_renderToBackBuffer;
		protected:
			Shader* m_shader;
			std::string m_name;
			ID3D11Buffer* m_effectProperties;
			std::vector<Texture*> m_textures;
			ID3D11RenderTargetView* m_renderTarget;
			ID3D11ShaderResourceView* m_shaderResource;

		};
	}
}