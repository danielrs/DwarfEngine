#include <Dwarf/Graphics/FX/BloomFX.h>
#include <Dwarf/Graphics/Framebuffer.h>
#include <Dwarf/Graphics/Shader.h>
#include <Dwarf/Graphics/Shaders/Shaders.h>

#include <iostream>
using namespace std;

namespace Dwarf {
	namespace Graphics {

		BloomFX::BloomFX() : bloom_factor(0.2)  {}

		void BloomFX::dispose() {
			buffer1.dispose();
			buffer2.dispose();
		}

		float BloomFX::getBloomFactor() const {
			return bloom_factor;
		}

		void BloomFX::setBloomFactor(const float &bloom_factor) {
			this->bloom_factor = bloom_factor;
		}

		void BloomFX::apply(Framebuffer *framebuffer) {

			if (framebuffer->getPixelFormat() != buffer1.getPixelFormat()
				|| framebuffer->getWidth() != buffer1.getWidth()
				|| framebuffer->getHeight() != buffer1.getHeight()) {
				this->gen(framebuffer);
			}

			framebuffer->bind();

			glUseProgram(light_program.getID());
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, buffer1.getID(), 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			framebuffer->getColorBuffer()->bind(GL_TEXTURE0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glUseProgram(blur_program.getID());
			// 2 Passes
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, buffer2.getID(), 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			buffer1.bind(GL_TEXTURE0);
			blur_program.setUniformi(blur_program.getUniformLocation("horizontal"), 1);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, buffer1.getID(), 0);
			buffer2.bind(GL_TEXTURE0);
			blur_program.setUniformi(blur_program.getUniformLocation("horizontal"), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glUseProgram(comb_program.getID());
			comb_program.setUniformf(comb_program.getUniformLocation("bloom_factor"), bloom_factor);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, framebuffer->getColorBuffer()->getID(), 0);
			framebuffer->getColorBuffer()->bind(GL_TEXTURE0);
			buffer1.bind(GL_TEXTURE1);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			framebuffer->unbind();
		}

		void BloomFX::gen(Framebuffer *framebuffer) {
			buffer1.setPixelFormat(framebuffer->getPixelFormat());
			buffer1.setWidth(framebuffer->getWidth());
			buffer1.setHeight(framebuffer->getHeight());
			buffer1.gen();
			buffer2.setPixelFormat(framebuffer->getPixelFormat());
			buffer2.setWidth(framebuffer->getWidth());
			buffer2.setHeight(framebuffer->getHeight());
			buffer2.gen();

			// Program
			if (!glIsProgram(light_program.getID()) || !glIsProgram(blur_program.getID())) {

				Shader vert(Shader::VERTEX, Shaders::fullquad_vert);
				Shader frag(Shader::FRAGMENT, Shaders::bloomfx_frag);

				light_program.clearShaders();
				light_program.attachShader(&vert);
				light_program.attachShader(&frag);
				light_program.link();
				light_program.setUniformi(light_program.getUniformLocation("sampler"), 0);
				light_program.setUniformf(light_program.getUniformLocation("bloom_thresh_min"), 0.5f);
				light_program.setUniformf(light_program.getUniformLocation("bloom_thresh_max"), 0.6f);

				frag.setSource(Shaders::gaussblurfx_frag);

				blur_program.clearShaders();
				blur_program.attachShader(&vert);
				blur_program.attachShader(&frag);
				blur_program.link();

				frag.setSource(Shaders::bloomcombinefx_frag);

				comb_program.clearShaders();
				comb_program.attachShader(&vert);
				comb_program.attachShader(&frag);
				comb_program.link();
				comb_program.setUniformi(comb_program.getUniformLocation("sampler"), 0);
				comb_program.setUniformi(comb_program.getUniformLocation("bloom_sampler"), 1);
				comb_program.setUniformf(comb_program.getUniformLocation("exposure"), 0.9);
				comb_program.setUniformf(comb_program.getUniformLocation("scene_factor"), 1);
			}
		}

	}
}
