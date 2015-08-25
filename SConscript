import libtbx.load_env
import os
Import("env_etc")

env_etc.rovinj_numopt_tut_dist = libtbx.env.dist_path("rovinj_numopt_tut")
env_etc.rovinj_numopt_tut_includes = [
  env_etc.libtbx_include,
  env_etc.cctbx_include,
  env_etc.scitbx_include,
  env_etc.boost_include,
  env_etc.python_include,
  # this last line is only necessary because the rovinj_numopt_tut module
  # leaves outside the directory cctbx_sources or cctbx_project.
  os.path.dirname(env_etc.rovinj_numopt_tut_dist)
]

if (not env_etc.no_boost_python):
  Import("env_no_includes_boost_python_ext")
  env_rovinj_numopt_tut_ext = env_no_includes_boost_python_ext.Clone()
  env_etc.include_registry.append(
    env=env_rovinj_numopt_tut_ext,
    paths=env_etc.rovinj_numopt_tut_includes)
  env_rovinj_numopt_tut_ext.Prepend(LIBS=["cctbx"])
  Export("env_rovinj_numopt_tut_ext")
  
SConscript("constraints/SConscript")


    