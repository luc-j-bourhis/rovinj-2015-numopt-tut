from rovinj_numopt_tut.constraints import rotating_oh
from cctbx import xray, uctbx

pivot = xray.scatterer(site=(0,0,0), label="C")
pivot_neighbour = xray.scatterer(site=(1,1,1), label="O")
unit_cell = uctbx.unit_cell((1,2,3,90,90,90))
constraint = rotating_oh(pivot, pivot_neighbour, 0, unit_cell)
print constraint.hydrogen_site
print constraint.hydrogen_site_derivative

