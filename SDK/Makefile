# Chemins des répertoires d'en-tête
BUILD=../build
AUXIL=../auxil
SRC=../src

INCLUDE_DIRS := $(BUILD)			\
		$(SRC)/include 				\
		$(AUXIL)/c-ares/include \
		$(AUXIL)/broker/include \
		$(AUXIL)/out_ptr/include \
		$(AUXIL)/paraglob/include \
		$(BUILD)/auxil/broker/include \
		$(BUILD)/auxil/spicy/include \
		$(BUILD)/src \
		$(SRC) \
		$(AUXIL)/broker/libbroker \
		$(SRC)/analyzer/protocol/tcp \

# Options de compilation incluant les répertoires d'en-tête
CXXFLAGS += -Wall -Wno-unused -funsigned-char -O2 -pthread -std=c++17  $(addprefix -I,$(INCLUDE_DIRS)) 

CXX_DEFINES = -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN -DDOCTEST_CONFIG_SUPER_FAST_ASSERTS  -DFIBER_ASM_CHECK_ALIGNMENT=1 -DFIBER_SHARED=1

C_FLAGS = -flto=auto -fno-fat-lto-objects

# Règle pour compiler le programme principal
my_zeek: main.cc ../build/auxil/paraglob/src/libparaglob.a ../build/auxil/c-ares/lib/libcares.a ../build/libzeek_lib.a ../build/auxil/spicy/lib/libhilti.so
	g++ -g  $(CXXFLAGS) $(CXX_DEFINES) $(C_FLAGS) -o my_zeek main.cc -L. -lzeek_lib -lcares -lparaglob -lkqueue \
	-lhilti -lspicy -lbroker -lbinpac -lpthread -lssl -lcrypto -ldl -lz -lgcc -lc -lrt -lpcap


# Règle générique pour compiler les fichiers objets C++
$(BUILD)/%.o: $(SRC)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Obtenir la liste des fichiers sources
SOURCES := $(shell find $(SRC) -name '*.cc')
C_SOURCES := $(shell find $(SRC) -name '*.c')
I_SOURCES := $(shell find $(BUILD)/src -name '*.i')
S_SOURCES := $(shell find $(BUILD)/src -name '*.s')
H_HEADERS := $(shell find $(BUILD)/src -name '*.h')
HH_HEADERS := $(shell find $(BUILD)/src -name '*.hh')
FUNC_H_SOURCES := $(shell find $(BUILD)/src -name '*.func_h')
NET_H_SOURCES := $(shell find $(BUILD)/src -name '*.net_h')

# Convertir les fichiers sources en noms de fichiers objets
OBJECTS := $(shell find $(BUILD)/src -name '*.o')
# Compiler la bibliothèque statique
libstatic.a: $(OBJECTS) $(SOURCES) $(C_SOURCES) $(I_SOURCES) $(S_SOURCES) $(FUNC_H_SOURCES) $(NET_H_SOURCES) $(H_HEADERS) $(HH_HEADERS)
	$(AR) $(ARFLAGS) $@ $^


# Compiler la bibliothèque dynamique
dynamic_lib: $(OBJECTS)
	$(CXX) $(LDFLAGS) -shared -o $(BUILD)/libdynamic.so $(OBJECTS)
