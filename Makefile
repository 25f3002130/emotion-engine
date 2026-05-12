CXX = g++
CXXFLAGS = -std=c++17 -I./include -Wall -pthread `pkg-config --cflags Qt6Widgets`
LIBS = `pkg-config --libs Qt6Widgets`
MOC = /usr/lib/qt6/libexec/moc

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
MOC_DIR = $(BUILD_DIR)/moc

# Core Sources
CORE_SOURCES = src/training/TrainingManager.cpp \
               src/models/SENTI9.cpp \
               src/emotions/EmotionProcessor.cpp \
               src/core/Logger.cpp \
               src/core/Config.cpp \
               src/core/DataManager.cpp \
               src/core/HardwareMonitor.cpp \
               src/core/SystemAudit.cpp

# UI Headers that need MOC
UI_HEADERS = include/ui/MainWindow.h \
             include/ui/DashboardPanel.h \
             include/ui/TrainingRoomPanel.h \
             include/ui/LogsMatrixPanels.h \
             include/ui/SplashScreen.h \
             include/ui/EmotionSelectorDialog.h

# UI Sources
UI_SOURCES = src/ui/MainWindow.cpp \
             src/ui/DashboardPanel.cpp \
             src/ui/TrainingRoomPanel.cpp \
             src/ui/SplashScreen.cpp \
             src/ui/EmotionSelectorDialog.cpp \
             src/main.cpp

# MOC Generated Sources
MOC_SOURCES = $(patsubst include/ui/%.h,$(MOC_DIR)/moc_%.cpp,$(UI_HEADERS))

# All Objects
CORE_OBJECTS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(CORE_SOURCES))
UI_OBJECTS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(UI_SOURCES))
MOC_OBJECTS = $(patsubst $(MOC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MOC_SOURCES))

OBJECTS = $(CORE_OBJECTS) $(UI_OBJECTS) $(MOC_OBJECTS)
TARGET = emotion_engine

all: prepare $(TARGET)

prepare:
	@mkdir -p $(OBJ_DIR)/training $(OBJ_DIR)/models $(OBJ_DIR)/emotions $(OBJ_DIR)/core $(OBJ_DIR)/ui $(MOC_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Rule for MOC files
$(MOC_DIR)/moc_%.cpp: include/ui/%.h
	$(MOC) $< -o $@

# Rule for Object files from src/
$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for Object files from MOC/
$(OBJ_DIR)/%.o: $(MOC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)
