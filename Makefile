
# This file constitutes the root Makefile for source code, snippets and programs
# built in the online course: Hands-On Cryptography with C++.
#
# Following commands are available:
#
# - make all
# - make clean
#
TARGET = all
OUTDIR = ./bin

CC = clang++ -arch x86_64
XX_FLAGS = -std=c++11
CXX = $(CC) $(XX_FLAGS)

snippets = confidentiality integrity authenticity nonrepudiation

$(TARGET): clean $(snippets)
	@chmod a+x $(OUTDIR)/*.bin
	@echo ""
	@echo "Snippets built successfully"
	@echo "Compiled assets can be found in $(OUTDIR)"

confidentiality: snippets/01-confidentiality/main.cpp
	@echo "Compiling $<..."; $(CXX) -c $< -o $(OUTDIR)/$@.o
	@echo "Linking $(OUTDIR)/$@.bin..."; $(CXX) $< -o $(OUTDIR)/$@.bin

integrity: snippets/02-integrity/main.cpp
	@echo "Compiling $<..."; $(CXX) -c $< -o $(OUTDIR)/$@.o
	@echo "Linking $(OUTDIR)/$@.bin..."; $(CXX) $< -o $(OUTDIR)/$@.bin

authenticity: snippets/03-authenticity/main.cpp
	@echo "Compiling $<..."; $(CXX) -c $< -o $(OUTDIR)/$@.o
	@echo "Linking $(OUTDIR)/$@.bin..."; $(CXX) $< -o $(OUTDIR)/$@.bin

nonrepudiation: snippets/04-non-repudiation/main.cpp
	@echo "Compiling $<..."; $(CXX) -c $< -o $(OUTDIR)/$@.o
	@echo "Linking $(OUTDIR)/$@.bin..."; $(CXX) $< -o $(OUTDIR)/$@.bin

clean:
	rm -rf $(OUTDIR)/*