#include "chi_lua.h"

#include "ChiMath/dynamic_vector.h"
#include "ChiMath/dynamic_matrix.h"
#include "ChiMath/SparseMatrix/chi_math_sparse_matrix.h"

#include "chi_runtime.h"
#include "chi_log.h"

namespace chi_unit_tests
{

int Test_chi_math(lua_State* L)
{
  //======================================================= Dynamic Vector
  {
    chi::log.Log() << "Testing chi_math::DynamicVector\n";

    chi_math::DynamicVector<double> vec(5, 1.0);

    chi::log.Log() << vec.PrintStr();
  }
  //======================================================= Dynamic Matrix
  {
    chi::log.Log() << "Testing chi_math::DynamicMatrix\n";
    chi_math::DynamicMatrix<double> mat(5, 7, 1.0);

    chi::log.Log() << mat.PrintStr();
  }

  //======================================================= SparseMatrix
  {
    chi_math::SparseMatrix matrix(4,4);
    auto& mat = matrix;
    mat.Insert(0, 0, 1.0); mat.Insert(0, 1, 1.1); mat.Insert(0, 2, 1.2); mat.Insert(0, 3, 1.3);
    mat.Insert(1, 0, 1.9); mat.Insert(1, 1, 2.0); mat.Insert(1, 2, 2.1);
    mat.Insert(2, 1, 2.9); mat.Insert(2, 2, 3.0); mat.Insert(2, 3, 3.1);
    mat.Insert(3, 2, 3.9); mat.Insert(3, 3, 4.0);

    {
      auto &m = mat;
      chi::log.Log() << "----- SparseMatrix::PrintS() -----"
                     << "\n" << m.PrintStr() << "\n";

      chi::log.Log() <<"----- for (const auto& entry : m.Row(2)) -----";
      for (const auto &entry: m.Row(2))
        chi::log.Log() << entry.row_index << " "
                       << entry.column_index << " "
                       << entry.value;

      chi::log.Log() << "----- after value*2 -----";
      for (const auto&[row_index, column_index, value]: m.Row(2))
        value *= 2;

      for (const auto &entry: m.Row(2))
        chi::log.Log() << entry.row_index << " "
                       << entry.column_index << " "
                       << entry.value;
    }

    chi::log.Log() << "----- for (auto entry : matrix) -----";
    for (const auto& entry : matrix)
      chi::log.Log() << entry.row_index << " "
                     << entry.column_index << " "
                     << entry.value;

    matrix.Compress();
    chi::log.Log() << "----- after compress -----";
    for (const auto& entry : matrix)
      chi::log.Log() << entry.row_index << " "
                     << entry.column_index << " "
                     << entry.value;
  }

  return 0;
}

}//namespace chi_unit_tests