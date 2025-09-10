EXE = example_glfw_opengl3
IMGUI_DIR = ./incs/imgui
OBJDIR = intermediates

SOURCES = main.cpp \
          $(IMGUI_DIR)/imgui.cpp \
          $(IMGUI_DIR)/imgui_demo.cpp \
          $(IMGUI_DIR)/imgui_draw.cpp \
          $(IMGUI_DIR)/imgui_tables.cpp \
          $(IMGUI_DIR)/imgui_widgets.cpp \
          $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
          $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp \
          $(IMGUI_DIR)/misc/cpp/imgui_stdlib.cpp \
          api.cpp


# OBJS: sadece dosya adını kullanarak intermediates klasörüne koy
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))

CXX = g++
CXXFLAGS = -std=c++17 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMGUI_DIR)/misc/cpp -g -Wall -lcurl
LIBS = -lGL `pkg-config --static --libs glfw3`

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LIBS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lglfw
endif

# Genel rule: tüm kaynaklar için geçerli
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# SOURCES klasörleri için rule
$(OBJDIR)/%.o: $(IMGUI_DIR)/%.cpp | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(IMGUI_DIR)/backends/%.cpp | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(IMGUI_DIR)/misc/cpp/%.cpp | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build exe
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

all: $(EXE)

clean:
	rm -rf $(OBJDIR)/* $(EXE)
