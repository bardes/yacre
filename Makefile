# Compilador de C++
CXX = g++

# Nome do executavel
EXEC = yacre

WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
	   -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self \
	   -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs \
	   -Wnoexcept -Woverloaded-virtual -Wredundant-decls \
	   -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
	   -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused -Winvalid-pch

# Flags usadas durante a compilacao
CXXFLAGS = $(WARNINGS) -std=c++11 -march=native -O2 -fopenmp

# Flags de preprocessamento
CPPFLAGS = -DGLM_FORCE_CXX11 $(shell pkg-config --cflags sfml-graphics)

# Flags usado durante a linkagem
LDFLAGS = $(shell pkg-config --libs sfml-graphics)

# Arquivos com codigo fonte
SRCS = $(shell find src -name '*.cc')
HDRS = $(shell find src -name '*.hh')
RES  =

# Lista de arquivos objeto gerada a partir dos arquivos de implementacao
OBJS = $(SRCS:=.o)

# Lista de arquivos de dependencia
DEPS = $(SRCS:=.dep)

# Alvos que nao devem ser representados por arquivos
.PHONY: clean all run zip debug

# Alvo padrao do make
all: $(EXEC)

noopdebug: CXXFLAGS += -g -O0
noopdebug: CPPFLAGS += -DDEBUG
noopdebug: all
debug: CXXFLAGS += -g -Og
debug: CPPFLAGS += -DDEBUG
debug: all

# Faz a linkagem e cria o executavel
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

# Regra geral para compilar os arquivos fontes
$(OBJS):
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(@:.o=) -o $@

# Gera arquivo de dependencia de cada ".cc"
%.dep: %
	$(CXX) $(CXXFLAGS) -MM -MT $(@:.dep=.o) $(CPPFLAGS) $< -MF $@

zip:
	zip -r $(EXEC).zip $(SRCS) $(HDRS) $(RES) Makefile

clean:
	rm -f $(OBJS) $(DEPS)

# Insere as dependencias no makefile
-include $(DEPS)
