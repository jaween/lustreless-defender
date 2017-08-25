#include "SDL_gpu.h"

#include "occlusion_mask_shader.h"

const std::string OcclusionMaskShader::kVertexFile =
    "main/src/shaders/transform.vert";
const std::string OcclusionMaskShader::kFragmentFile =
    "main/src/shaders/occlusion_mask.frag";

OcclusionMaskShader::OcclusionMaskShader()
 : Shader(kVertexFile, kFragmentFile) {
}
