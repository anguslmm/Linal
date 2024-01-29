#ifndef LINAL_LIBRARY_H
#define LINAL_LIBRARY_H

#include <cstddef>
#include <vector>
#include <optional>

class Matrixf {
 public:
  using UnitType = double;
  using VectorType = std::vector<UnitType>;

  Matrixf(size_t rows, size_t columns, UnitType init = 0.f);
  static std::optional<Matrixf> New(VectorType data, size_t rows, size_t columns);

  [[nodiscard]] UnitType operator[](size_t index);

  [[nodiscard]] size_t columns() const { return columns_; }
  [[nodiscard]] size_t rows() const { return rows_; }

  [[nodiscard]] UnitType at(size_t row, size_t column);
  [[nodiscard]] VectorType column(size_t index);
  [[nodiscard]] VectorType data();
  [[nodiscard]] VectorType row(size_t index);

 private:
  Matrixf(VectorType&& data, size_t rows, size_t columns);

  VectorType data_;
  size_t columns_;
  size_t rows_;
};

#endif //LINAL_LIBRARY_H
