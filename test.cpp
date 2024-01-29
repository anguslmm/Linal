//
// Created by angus on 1/25/2024.
//

#include "library.h"

#include "gtest/gtest.h"

namespace {
const double kErrorRange = 0.0001f;
}

TEST(MatrixfTest, Constructor) {
  const size_t kHeight = 6u;
  const size_t kWidth = 5u;
  const float kFillValue = 0.75f;

  Matrixf mat(kHeight, kWidth, kFillValue);

  for (size_t row = 0; row < kHeight; ++row) {
    for (size_t x = 0; x < kWidth; ++x) {
      EXPECT_EQ(mat[row * kWidth + x], kFillValue);
    }
  }
}

TEST(MatrixfTest, Factory) {
  // Matrices with dimensions that don't match the data will return `std::nullopt`.
  auto mat = Matrixf::New({0.f, 1.f,
                           0.f, 1.f,
                           0.f}, 3, 2);
  EXPECT_EQ(mat, std::nullopt);

  // Empty matrices are possible (for now).
  mat = Matrixf::New({}, 0, 0);
  EXPECT_TRUE(mat.has_value());

  // Properly formed matrices should succeed.
  mat = Matrixf::New({0.f, 1.f,
                      2.f, 3.f,
                      4.f, 5.f}, 2, 3);
  EXPECT_TRUE(mat.has_value());
  EXPECT_EQ(mat.value()[5], 5.f);
}

TEST(MatrixfTest, ColumnFetch) {
  auto maybe_mat = Matrixf::New({0.f, 1.f, 2.f,
                                 3.f, 4.f, 5.f,
                                 6.f, 7.f, 8.f}, /*rows=*/3u, /*columns=*/3u);

  ASSERT_TRUE(maybe_mat.has_value());

  auto &mat = maybe_mat.value();
  for (size_t i = 0; i < mat.columns(); ++i) {
    auto row = mat.column(i);
    for (size_t j = 0; j < mat.rows(); ++j) {
      EXPECT_EQ(row[j], static_cast<double>(j * mat.columns() + i));
    }
  }
}

TEST(MatrixfTest, RowFetch) {
  auto maybe_mat = Matrixf::New({0.f, 1.f, 2.f,
                                 3.f, 4.f, 5.f,
                                 6.f, 7.f, 8.f}, /*rows=*/3u, /*columns=*/3u);

  ASSERT_TRUE(maybe_mat.has_value());

  auto &mat = maybe_mat.value();
  for (size_t i = 0; i < mat.rows(); ++i) {
    auto row = mat.row(i);
    for (size_t j = 0; j < mat.columns(); ++j) {
      EXPECT_EQ(row[j], static_cast<double>(i * mat.columns() + j));
    }
  }
}

TEST(MatrixfTest, Echelon) {
  auto mat = Matrixf::New({0.f, 1.f, 2.f,
                           3.f, 4.f, 5.f,
                           6.f, 7.f, 8.f},
                          3u, 3u).value().GetEchelonForm();

  auto expected = Matrixf::New({1.f, 4.f / 3.f, 5.f / 3.f,
                                0.f,       1.f,       2.f,
                                0.f,       0.f,       0.f},
                               3u, 3u).value();

  for (size_t row = 0; row < 3u; ++row) {
    for (size_t col = 0; col < 3u; ++col) {
      EXPECT_NEAR(mat.at(row, col), expected.at(row, col), kErrorRange);
    }
  }
}

TEST(MatrixfTest, RREchelon) {
  auto rrech = Matrixf::New({0.f, 1.f, 2.f,
                             3.f, 4.f, 5.f,
                             6.f, 7.f, 8.f},
                            3u, 3u).value().GetRREchelonForm();

  auto expected = Matrixf::New({1.f, 0.f, -1.f,
                                0.f, 1.f,  2.f,
                                0.f, 0.f,  0.f},
                               3u, 3u).value();

  for (size_t row = 0; row < 3u; ++row) {
    for (size_t col = 0; col < 3u; ++col) {
      EXPECT_NEAR(rrech.at(row, col), expected.at(row, col), kErrorRange);
    }
  }
}
