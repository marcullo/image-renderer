.PHONY: clean
.PHONY: debug
.PHONY: default
.PHONY: memcheck
.PHONY: release
.PHONY: .build
.PHONY: .configure

# ----- Paths -----------------------------------------------------------------
OUTPUT_DIR ?= $(CURDIR)/_build
CMAKE_DIR ?= $(OUTPUT_DIR)/cmake

# ----- Params ----------------------------------------------------------------
CMAKE_BUILD_TYPE ?= Release
CMAKE_SIZE ?= size
SAMPLE ?= $(CURDIR)/samples/crop_extend.txt

# ----- Flags -----------------------------------------------------------------
ifeq ($(VERBOSE), 1)
cmakeflags += -DCMAKE_VERBOSE_MAKEFILE=TRUE
ctestflags += -VV
else
MAKEFLAGS += --silent
ctestflags += --output-on-failure
endif

NPROC = $(shell grep -c processor /proc/cpuinfo)

CMAKEFLAGS ?=
cmakecommonflags += ${CMAKEFLAGS}
cmakecommonflags += -GNinja

cmakeflags += ${cmakecommonflags}
cmakeflags += -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(OUTPUT_DIR)
cmakeflags += -DCMAKE_SIZE=$(CMAKE_SIZE)
cmakeflags += $(if $(value CMAKE_BUILD_TYPE),-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE))
cmakebuild += nice cmake --build
cmakebuildflags += --parallel $(NPROC)

valgrindflags += --tool=memcheck --leak-check=full --show-leak-kinds=all -s
# ----- Targets ---------------------------------------------------------------
default: debug

release: .build

debug: CMAKE_BUILD_TYPE = Debug
debug: .build

clean:
	rm -rf $(OUTPUT_DIR)

.build: | .configure .build_all

.configure:
	cmake -S $(CURDIR) -B $(CMAKE_DIR) $(cmakeflags)

.build_%:
	${cmakebuild} $(CMAKE_DIR) --target $* ${cmakebuildflags}

# ----- Tests & checks --------------------------------------------------------
memcheck:
	echo
	echo "Sample: $(SAMPLE)"
	echo
	cd ${OUTPUT_DIR} && valgrind $(valgrindflags) ./commander $(SAMPLE)
