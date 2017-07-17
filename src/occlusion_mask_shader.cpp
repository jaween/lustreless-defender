#include "SDL_gpu.h"

#include "occlusion_mask_shader.h"

const std::string OcclusionMaskShader::kVertexFile =
    "src/shaders/transform.vert";
const std::string OcclusionMaskShader::kFragmentFile =
    "src/shaders/occlusion_mask.frag";

OcclusionMaskShader::OcclusionMaskShader()
 : Shader(kVertexFile, kFragmentFile) {
}
