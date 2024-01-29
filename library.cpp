#include "library.h"

Matrixf::Matrixf(size_t rows, size_t columns, Matrixf::UnitType init) : columns_(columns), rows_(rows) {
  data_ = VectorType(rows * columns, init);
}

std::optional<Matrixf> Matrixf::New(Matrixf::VectorType data, size_t rows, size_t columns) {
  if (data.size() != rows * columns) {
    return std::nullopt;
  }
  auto res = Matrixf(std::move(data), rows, columns);
  return res;
}

Matrixf::Matrixf(Matrixf::VectorType &&data, size_t rows, size_t columns)
    : data_(data), columns_(columns), rows_(rows) {
}

Matrixf::UnitType Matrixf::operator[](size_t index) {
  return data_[index];
}

Matrixf::UnitType Matrixf::at(size_t row, size_t column) {
  return data_.at(row * columns_ + column);
}

Matrixf::VectorType Matrixf::column(size_t index) {
  VectorType res(rows_);
  for (size_t i = index; i < data_.size(); i += columns_) {
    res.push_back(data_[i]);
  }
  return res;
}

Matrixf::VectorType Matrixf::data() {
  return data_;
}

Matrixf::VectorType Matrixf::row(size_t index) {
  VectorType res(columns_);

  std::copy(data_.begin() + index * columns_, data_.begin() + index * columns_ + columns_, res.begin());

  return res;
}
