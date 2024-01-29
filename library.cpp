#include <iostream>
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

  for (size_t i = 0; i < rows_; ++i) {
    res[i] = data_[i * columns_ + index];
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

Matrixf Matrixf::GetEchelonForm() {
  Matrixf copy(*this);
  size_t cur_col = 0;
  size_t cur_row = 0;

  // Top to bottom
  while (cur_row < rows_ && cur_col < columns_) {
    // Find first row >= `cur_row` with non-zero element and swap it with `row`.
    size_t swap_row = cur_row;
    while (swap_row < rows_ && copy.at(swap_row, cur_col) == 0.f) ++swap_row;

    // If there isn't one increment cur_col and continue
    if (swap_row >= rows_) {
      ++cur_col;
      continue;
    }

    copy.SwapRows(cur_row, swap_row);

    // Make this row's entry in cur_col = 1 through multiplying the whole row
    double factor = 1.0f / copy.at(cur_row, cur_col);
    copy.MultiplyRow(cur_row, factor);

    // Make every row below this have 0 in cur_col using this row multiplied
    for (size_t row = cur_row + 1; row < rows_; ++row) {
      factor = copy.at(row, cur_col);
      copy.SubtractRowFromRow(row, cur_row, factor);
    }


    // increment cur_row and cur_col
    ++cur_col;
    ++cur_row;
  }
  return copy;
}

Matrixf Matrixf::GetRREchelonForm() {
  auto copy = GetEchelonForm();
  size_t cur_row = copy.rows_ -1;
  size_t cur_col = 0u;

  // Bottom to top
  while(cur_row > 0) {
    cur_col = 0;

    // Find pivot
    while (cur_col < columns_ && std::abs(copy.at(cur_row, cur_col)) < 0.0001f) {
      ++cur_col;
    }

    if (cur_col == columns_) {
      --cur_row;
      continue;
    }

    // Make every row above this have 0 in cur_col using this row multiplied
    for (int row = cur_row-1; row >= 0; --row) {
      double factor = copy.at(row, cur_col);
      copy.SubtractRowFromRow(row, cur_row, factor);
    }

    // increment cur_row and cur_col
    --cur_row;
  }

  return copy;
}

void Matrixf::Debug() {
  for (size_t r = 0; r < rows_; ++r) {
    for (size_t c = 0; c < columns_; ++c){
      std::cout << at(r, c) << ", ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Matrixf::MultiplyRow(size_t row, double factor) {
  for (size_t i = row * columns_; i < row * columns_ + columns_; ++i) {
    data_[i] *= factor;
  }
}

void Matrixf::SubtractRowFromRow(size_t dest_row, size_t source_row, double factor) {
  for (size_t i = 0; i < columns_; ++i) {
    size_t dest_i = dest_row * columns_ + i;
    size_t source_i = source_row * columns_ + i;
    data_[dest_i] -= data_[source_i] * factor;
  }
}

void Matrixf::SwapRows(size_t row1, size_t row2) {
  for (size_t i = 0; i < columns_; ++i) {
    size_t i1 = row1 * columns_ + i;
    size_t i2 = row2 * columns_ + i;
    double tmp = data_[i1];
    data_[i1] = data_[i2];
    data_[i2] = tmp;
  }
}
