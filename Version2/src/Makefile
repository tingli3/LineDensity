GCC ?= g++

# Gdal
GDALLIB := -L/data/keeling/a/tingli3/gdal/lib -lgdal   #gdal-config --libs
GDALFLAG := -I/data/keeling/a/tingli3/gdal/include	#gdal-config --cflag
# Target rules
all: LineDensity
LineDensity.o: LineDensity.c
        $(GCC) -o $@ -c $<
density.o: density.c
        $(GCC) -o $@ -c $<
io.o: io.c
        $(GCC) -I. $(GDALFLAG) -o $@ -c $<
LineDensity: LineDensity.o io.o density.o
        $(GCC) -o ../$@ $+ $(GDALLIB)
clean:
        rm -f *.o ../LineDensity


