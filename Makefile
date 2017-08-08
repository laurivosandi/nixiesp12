# This makefile:
# * Converts KiCad exported Gerber files to G-code files usable with LinuxCNC
# * Merges drill toolpaths to one 1mm drill toolpath
# * Reset coordinate system
# * Use resulting bla_front.ngc, bla_drill.ngc, bla_back.ngc files

PROJECT=nixiesp
MILL_FEED=70
DRILL_FEED=70
SPINDLE_SPEED=6000
FINISH_HEIGHT=40
DRILL_DEPTH=8

# Tiling
TILING_X=1
TILING_Y=1

all: ${PROJECT}_drill.ngc

%_drill.ngc: %.drl %-F.Cu.gtl %-B.Cu.gbl
	pcb2gcode \
		--zero-start \
		--software linuxcnc \
		--tile-x ${TILING_X} \
		--tile-y ${TILING_Y} \
		--front $*-F.Cu.gtl \
		--back $*-B.Cu.gbl \
		--drill $*.drl \
		--front-output $*_front.ngc \
		--back-output $*_back.ngc \
		--drill-output $*_drill.ngc \
		--metric \
		--metricoutput \
		--zsafe 1 --zchange ${FINISH_HEIGHT} --zcut 0 \
		--cutter-diameter 5 --cut-feed ${MILL_FEED} --cut-speed ${SPINDLE_SPEED} --cut-infeed ${MILL_FEED} \
		--zwork -0.2 --offset 0.1 --mill-feed ${MILL_FEED} --mill-speed ${SPINDLE_SPEED} \
		--zdrill -${DRILL_DEPTH} --drill-feed ${DRILL_FEED} --drill-speed ${SPINDLE_SPEED}

clean:
	rm -fv *.ngc

purge: clean
	rm -fv *.g* *.drl *.dsn *.ses *.bak *.kicad_pcb-bak *.png *.svg *.net
