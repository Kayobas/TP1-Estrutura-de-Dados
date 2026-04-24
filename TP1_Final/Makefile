# Variáveis de Compilação
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11
LDFLAGS := 
TARGET := tp1.out

# Diretórios
SRCDIR := src
INCDIR := include
OBJDIR := obj
BINDIR := bin

# Lista explícita de arquivos
SRCS := $(SRCDIR)/main.cpp $(SRCDIR)/cena.cpp $(SRCDIR)/objeto.cpp
OBJS := $(OBJDIR)/main.o $(OBJDIR)/cena.o $(OBJDIR)/objeto.o
INCLUDES := -I$(INCDIR)

.PHONY: all clean

# Alvo principal
all: $(BINDIR)/$(TARGET) $(TARGET)

# Cria o executável em bin/
$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	@echo "Linking executable..."
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Cria cópia do executável na raiz (caso o VPL procure lá)
$(TARGET): $(BINDIR)/$(TARGET)
	@echo "Creating copy in root directory..."
	@cp $(BINDIR)/$(TARGET) $(TARGET)

# Regras específicas para cada arquivo objeto
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp | $(OBJDIR)
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/cena.o: $(SRCDIR)/cena.cpp | $(OBJDIR)
	@echo "Compiling cena.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/objeto.o: $(SRCDIR)/objeto.cpp | $(OBJDIR)
	@echo "Compiling objeto.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Cria diretório bin
$(BINDIR):
	@mkdir -p $(BINDIR)

# Cria diretório obj
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Limpeza geral
clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJDIR) $(BINDIR) $(TARGET)
