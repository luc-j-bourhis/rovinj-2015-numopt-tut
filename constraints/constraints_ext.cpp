#include <smtbx/boost_python/flex_fwd.h>

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/args.hpp>
#include <boost/python/return_by_value.hpp>

#include <rovinj_numopt_tut/constraints/constraints.h>

namespace rovinj_numopt_tut { namespace boost_python {
  template <typename FloatType>
  struct rotating_oh_wrapper
  {
    typedef rotating_oh<FloatType> wt;
    typedef typename wt::scalar_t scalar_t;
    
    static void wrap() {
      using namespace boost::python;
      return_value_policy<return_by_value> rbv;
      class_<wt>("rotating_oh", no_init)
        .def(init<xray::scatterer<> const &,
                  xray::scatterer<> const &,
                  scalar_t,
                  uctbx::unit_cell const &>
            ((arg("pivot"), arg("pivot_neighbour"), arg("azimuth"),
             (arg("unit_cell")))))
        .add_property("hydrogen_site", 
                      make_getter(&wt::hydrogen_site, rbv))
        .add_property("hydrogen_site_derivative",
                      make_getter(&wt::hydrogen_site_derivative, rbv))
      ;
    }
  };
  
  void init_module() {
    rotating_oh_wrapper<double>::wrap();    
  }
}}

BOOST_PYTHON_MODULE(rovinj_numopt_tut_constraints_ext)
{
  rovinj_numopt_tut::boost_python::init_module();
}