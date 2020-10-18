######################################################################
# Makefile for building Pythia's ROOT examples.
# Axel Naumann, 2011-03-03
######################################################################

PYTHIA8      := $(ALICE_ROOT)
# Need this to get SHAREDSUFFIX (e.g. dylib or so)
SHAREDSUFFIX=so
#-include $(PYTHIA8)/config.mk

# A few variables used in this Makefile:
EX           := pythia_chic2
EXE          := $(addsuffix .exe,$(EX))
STATICLIB    := $(PYTHIA8)/lib/archive/libpythia8.a
SHAREDLIB    := $(PYTHIA8)/lib/libpythia8210.$(SHAREDSUFFIX)
DICTCXXFLAGS := -I$(HOME)/chi_c2/PYTHIA8/pythia8210/include
ROOTCXXFLAGS := $(DICTCXXFLAGS) $(shell root-config --cflags)
CXXFLAGS     := -Wall

# Libraries to include if GZIP support is enabled
ifeq (x$(ENABLEGZIP),xyes)
LIBGZIP=-L$(BOOSTLIBLOCATION) -lboost_iostreams -L$(ZLIBLOCATION) -lz
endif

# LDFLAGS1 for static library, LDFLAGS2 for shared library
LDFLAGS1 := $(shell root-config --ldflags --glibs) \
  -L$(PYTHIA8)/lib -lpythia8210 -llhapdf $(LIBGZIP)
LDFLAGS2 := $(shell root-config --ldflags --glibs) \
  -L$(PYTHIA8)/lib -lpythia8210 -llhapdf $(LIBGZIP)

FILES_SRC =   pythia_chic2.cc smearE.cc smearP.cc smearX.cc sigmaX.cc resolutionPhoton.cc resolutionElectron.cc IsElectronDetectedInCTS.cc IsPhotonDetectedInPHOS.cc IsPhotonDetectedInEMCAL.cc IsTriggeredByPHOS.cc Init.cc Invariant_mass_spectr_creator.cc
FILES_OBJ =  $(FILES_SRC:%.cc=%.o)

# Default target; make examples (but not shared dictionary)
all: $(EX)

# Rule to build hist example. Needs static PYTHIA 8 library
$(EX): $(SHAREDLIB) $(FILES_OBJ)
	$(CXX) $(ROOTCXXFLAGS) $(FILES_OBJ) -o $@.exe $(LDFLAGS1)

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(ROOTCXXFLAGS) 

# Rule to build full dictionary
dict: $(SHAREDLIB)
	rootcint -f pythiaDict.cc -c $(DICTCXXFLAGS) \
           -DPYTHIA8_COMPLETE_ROOT_DICTIONARY \
           pythiaROOT.h pythiaLinkdef.h
	$(CXX) -shared -fPIC -o pythiaDict.$(SHAREDSUFFIX) pythiaDict.cc \
         -DPYTHIA8_COMPLETE_ROOT_DICTIONARY \
         $(ROOTCXXFLAGS) $(LDFLAGS2)


# Error messages if PYTHIA libraries don't exist
$(STATICLIB):
	@echo "Error: PYTHIA 8 archive library must be built"
	@false
$(SHAREDLIB):
	@echo "Error: PYTHIA 8 shared library must be built"
	@false

# Clean up
clean:
	rm -f $(EXE) $(FILES_OBJ) pythia_chic2.root pythiaDict.*
