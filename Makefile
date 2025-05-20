CXX = clang++
CXXFLAGS = -std=c++20 -Iinclude
SRC = $(wildcard src/*.cpp)
OUT = out/sat_solver_ai

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(OUT)
	@echo "Kullanım: make run CNF=dosya"
	@./$(OUT) $(CNF)

test: $(OUT)
	@for file in test/*.cnf; do \
		echo "==================================="; \
		echo "Test ediliyor: $$file"; \
		./$(OUT) $$file; \
		echo ""; \
	done

clean:
	rm -f $(OUT)
