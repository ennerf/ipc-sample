#pragma once

#include <vector>

// matches data in afm_api::image_grid_specification
class image_grid_specification {
public:
  image_grid_specification(float minX, float maxX, float minZ, float maxZ)
      : startX(minX), startZ(minZ), stepX(0.12f), stepZ(0.12f) {
    numX = (size_t)((maxX - minX) / stepX);
    numZ = (size_t)((maxZ - minZ) / stepZ);
  }

  size_t numX;
  size_t numZ;
  float startX;
  float startZ;
  float stepX;
  float stepZ;
};

// matches data in afm_api::shared_image_result
class shared_image_result {
private:
  image_grid_specification grid_spec;
  size_t sequence{0};
  long enc1{0};
  long enc2{0};
  std::vector<float> data;
  std::vector<float> adaptive_surface;

public:
  shared_image_result(image_grid_specification spec) : grid_spec{spec} {
    data.resize(spec.numX * spec.numZ);
    adaptive_surface.resize(spec.numX);
  }

  void fill_data(float value) {
    sequence++;
    std::fill(data.begin(), data.end(), value);
  }

  // Returns a pointer to image data.
  float* image_data() {
    return data.data();
  }

  // Returns number of elements contained in image_data().
  // *(image_data() + image_data_length()) = access violation
  size_t image_data_length() {
    return data.size();
  }

  // Returns the ID of the sequence. This counts the number of
  // sequences fired since device began pulsing.
  size_t sequence_id() {
    return sequence;
  }

  // number of encoder steps recorded by encoder 1
  long encoder1_count(){
    return enc1;
  }

  // number of encoder steps recorded by encoder 2
  long encoder2_count(){
    return enc2;
  }

  // true if adaptive surface data is included
  bool contains_adaptive_surface() {
    return !adaptive_surface.empty();
  }

  // Adaptive surface data, see TFM Toolbox documentation for details.
  // surface_points_out must point to memory sufficient to store
  // num_surface_points() float values.
  // X0_out returns the x position of the first surface point.
  // DX_out returns the x distance between successive points.
  size_t num_surface_points() {
    return adaptive_surface.size();
  }
  void get_surface(float* surface_points, float& X0_out, float& DX_out) {
    memcpy(surface_points, adaptive_surface.data(), adaptive_surface.size() * sizeof(float));
    X0_out = grid_spec.startX;
    DX_out = grid_spec.stepX;
  }

};

