// Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DALI_AUX_OPTICAL_FLOW_OPTICAL_FLOW_ADAPTER_H_
#define DALI_AUX_OPTICAL_FLOW_OPTICAL_FLOW_ADAPTER_H_

#include <dali/pipeline/data/backend.h>
#include "dali/kernels/tensor_view.h"

namespace dali {
namespace optical_flow {

enum VectorGridSize {
  UNDEF,
  SIZE_4,  /// 4x4 grid
  MAX,
};

struct OpticalFlowParams {
  float perf_quality_factor = .0f;  /// 0..1, where 0 is best quality, lowest performance
  VectorGridSize grid_size = UNDEF;
  bool enable_hints = false;
};

template <typename Backend, typename DataType, int ndim>
using TV = dali::kernels::TensorView<Backend, DataType, ndim>;

class DLL_PUBLIC OpticalFlowAdapter {
 public:
  explicit OpticalFlowAdapter(OpticalFlowParams params) {}


  virtual void CalcOpticalFlow(TV<GPUBackend, const uint8_t, 3> reference_image,
                               TV<GPUBackend, const uint8_t, 3> input_image,
                               TV<GPUBackend, float, 3> output_image,
                               TV<GPUBackend, const float, 3> external_hints
                                  = TV<GPUBackend, const float, 3>()) = 0;


  virtual ~OpticalFlowAdapter() = default;
};

}  // namespace optical_flow
}  // namespace dali

#endif  // DALI_AUX_OPTICAL_FLOW_OPTICAL_FLOW_ADAPTER_H_
