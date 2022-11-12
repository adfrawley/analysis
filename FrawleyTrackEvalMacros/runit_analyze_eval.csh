#!/bin/csh

set baseDir=`pwd`

setenv HOME /phenix/u/$LOGNAME
source /etc/csh.login
foreach i (/etc/profile.d/*.csh)
source $i
end
#source $HOME/.login
#source /opt/sphenix/core/bin/sphenix_setup.csh
source ~/setup_sphenix_environment
#printenv

# input parameter is process number
echo "input parameter: " $1

set runno = $1
set nfiles = $2

echo "proc number: " $runno
echo "nfiles " $nfiles

set strin="/sphenix/sim/sim01/sphnxpro/MDC1/sHijing_HepMC/data/sHijing_0_20fm-0000000001-0"
echo $strin

echo "running..."
cd ${baseDir}
pwd

root -b -q  'analyze_evaluator_tracks_condor.C('$runno', '$nfiles')'
 


