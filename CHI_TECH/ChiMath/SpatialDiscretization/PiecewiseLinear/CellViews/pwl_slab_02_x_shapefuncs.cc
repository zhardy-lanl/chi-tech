#include "pwl_slab.h"

/**Shape function i evaluated at given point for the slab.*/
double SlabPWLFEView::ShapeValue(const int i, const chi_mesh::Vector3& xyz)
{
  chi_mesh::Vector3& p0 = *grid->vertices[v0i];
  chi_mesh::Vector3& p1 = *grid->vertices[v1i];
  chi_mesh::Vector3 xyz_ref = xyz - p0;

  chi_mesh::Vector3 v01 = p1 - p0;

  double xi   = v01.Dot(xyz_ref)/v01.Norm()/h;

  if ((xi>=-1.0e-6) and (xi<=1.0+1.0e-6))
  {
    if (i==0)
      return 1.0 - xi;
    else
      return xi;
  }//if in cell

  return 0.0;
}

//#################################################################
/**Populates shape_values with the value of each shape function's
 * value evaluate at the supplied point.*/
void SlabPWLFEView::ShapeValues(const chi_mesh::Vector3& xyz,
                 std::vector<double>& shape_values)
{
  shape_values.resize(dofs,0.0);
  chi_mesh::Vector3& p0 = *grid->vertices[v0i];
  chi_mesh::Vector3& p1 = *grid->vertices[v1i];
  chi_mesh::Vector3 xyz_ref = xyz - p0;

  chi_mesh::Vector3 v01 = p1 - p0;

  double xi   = v01.Dot(xyz_ref)/v01.Norm()/h;

  if ((xi>=-1.0e-6) and (xi<=1.0+1.0e-6))
  {
    for (int i=0; i<dofs; i++)
    {
      if (i==0)
        shape_values[i] = 1.0 - xi;
      else
        shape_values[i] = xi;
    }//for dof

    return;
  }//if in cell

}

//###################################################################
/**Returns the evaluation of grad-shape function i at the supplied point.*/
chi_mesh::Vector3 SlabPWLFEView::GradShapeValue(const int i, const chi_mesh::Vector3& xyz)
{
  if (i==0)
    return chi_mesh::Vector3(0.0, 0.0, -1.0 / h);
  else
    return chi_mesh::Vector3(0.0, 0.0, 1.0 / h);
}

//###################################################################
/**Populates shape_values with the value of each shape function's
 * value evaluate at the supplied point.*/
void SlabPWLFEView::GradShapeValues(const chi_mesh::Vector3& xyz,
                     std::vector<chi_mesh::Vector3>& gradshape_values)
{
  gradshape_values.clear();
  gradshape_values.emplace_back(GradShapeValue(0,xyz));
  gradshape_values.emplace_back(GradShapeValue(1,xyz));
}