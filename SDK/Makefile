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
		$(AUXIL)/broker/include \
		$(SRC)/analyzer/protocol/tcp \

# Options de compilation incluant les répertoires d'en-tête
CXXFLAGS += -Wall -Wno-unused -funsigned-char -O2 -pthread -std=c++17  $(addprefix -I,$(INCLUDE_DIRS))

# Règle pour compiler le programme principal
mon_programme: main.cc libparaglob.a libcares.a libstatic.a
	g++ $(CXXFLAGS) -o mon_programme main.cc -L. -lstatic -lcares -lparaglob -lkqueue \
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
