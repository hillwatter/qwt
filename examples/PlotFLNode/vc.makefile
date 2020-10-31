# 
#
#
MAKE=devenv

!IF "$(CFG)" == ""
CFG=debug
!ENDIF


ALL:
	$(MAKE) /build $(CFG) PlotFLNode.sln

CLEAN:
	$(MAKE) /clean $(CFG) PlotFLNode.sln

