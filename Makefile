#Compiler and Linker
#CC          := g++-mp-4.7
CC          := g++ -std=c++11
#CC          := g++-6 -std=c++11

#The Target Binary Program
TARGET      := fp

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o


#Flags, Libraries and Includes w/o openmp
# use these flags by default
CFLAGS := -Xpreprocessor -fopenmp -Wall -O3 -DNDEBUG -ffast-math
LIB := -lomp -lm -O3

# find the OS type
UNAME_S := $(shell uname -s)
# if the OS type is MacOS
ifeq ($(UNAME_S),Darwin)
	# if you have the OpenMP libraries, compile with them
	ifeq (,$(wildcard /usr/local/lib/libomp.a))
		CFLAGS := -Wall -O3 -DNDEBUG -ffast-math
		LIB := -lm -O3
	# otherwise don't
	else
		CFLAGS := -Xpreprocessor -fopenmp -Wall -O3 -DNDEBUG -ffast-math
		LIB := -lomp -lm -O3
	endif
endif


INC         := -I$(INCDIR) -I/usr/local/include 
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt Make
all: resources $(TARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
#	@cp $(RESDIR)/* $(TARGETDIR)/

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Debug
#debug: CFLAGS := -fopenmp -Wall -O3 -g -ggdb -ffast-math
debug: CFLAGS := -Wall -O0 -g -ggdb -ffast-math
debug: LIB := -ggdb
#debug: LIB := -fopenmp -ggdb
debug: cleaner all
 
#Non-File Targets
.PHONY: all remake clean cleaner resources
