#include "fv.h"

#include "chi_log.h"
extern ChiLog& chi_log;

#include "chi_runtime.h"
#include "ChiTimer/chi_timer.h"




//###################################################################
/**Only constructor for this method.*/
SpatialDiscretization_FV::
  SpatialDiscretization_FV(chi_mesh::MeshContinuumPtr& in_grid,
                           chi_math::CoordinateSystemType in_cs_type)
  : SpatialDiscretization(0, in_grid, in_cs_type, SDMType::FINITE_VOLUME)
{
  chi_log.Log() << chi::program_timer.GetTimeString()
                << " Creating Finite Volume spatial discretizaiton.";
  mapping_initialized = false;
  PreComputeCellSDValues();
  PreComputeNeighborCellSDValues();
  OrderNodes();
  chi_log.Log() << chi::program_timer.GetTimeString()
                << " Done creating Finite Volume spatial discretizaiton.";
}