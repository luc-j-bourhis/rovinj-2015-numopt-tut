#pragma once

#include <cctbx/xray/scatterer.h>
#include <cctbx/coordinates.h>
#include <scitbx/array_family/tiny.h>
#include <scitbx/math/orthonormal_basis.h>

namespace rovinj_numopt_tut { 
  
  namespace xray = cctbx::xray;
  namespace uctbx = cctbx::uctbx;
  namespace af = scitbx::af;

  template <typename FloatType>
  class rotating_oh
  {
  public:
    typedef FloatType scalar_t;
    typedef cctbx::cartesian<scalar_t> cart_t;
    typedef cctbx::fractional<scalar_t> frac_t;
    
    frac_t hydrogen_site;
    frac_t hydrogen_site_derivative;
    
    
    rotating_oh(xray::scatterer<> const &pivot,
                xray::scatterer<> const &pivot_neighbour,
                scalar_t azimuth,
                uctbx::unit_cell const &unit_cell)
    {
      cart_t x_p = unit_cell.orthogonalize(pivot.site);
      cart_t x_pn = unit_cell.orthogonalize(pivot_neighbour.site);
      
      // Building orthogonal basis e with x-axis
      // along the direction neighbour --> pivot
      cart_t e_zero_azimuth(1, 0, 0);
      af::tiny<cart_t, 3> e = 
        scitbx::math::orthonormal_basis(x_p - x_pn, e_zero_azimuth);
      
      // Computing direction vector pivot --> hydrogen, denoted by "u"      
      double const cos_tetrahedral_angle = -1./3.;
      double const tetrahedral_angle = std::acos(cos_tetrahedral_angle);
      double const sin_tetrahedral_angle = 
        std::sqrt(1. - cos_tetrahedral_angle*cos_tetrahedral_angle);
        
      double c = std::cos(azimuth), s = std::sin(azimuth);
      cart_t u = sin_tetrahedral_angle*(c*e[1] + s*e[2]) + e[0]/3.;  
        
      // Hydrogen site
      double const bond_length = 0.82; // Angstrom
      hydrogen_site = unit_cell.fractionalize(x_p + bond_length*u);
      
      // Now the derivatives wrt azimuthal angle
      cart_t grad = bond_length*sin_tetrahedral_angle*(-s*e[1] + c*e[2]);
      hydrogen_site_derivative = unit_cell.fractionalize(grad);
    }
  };
}