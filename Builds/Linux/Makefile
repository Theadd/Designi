# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := Designi
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := Designi
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/DocumentManager_ab56030b.o \
  $(OBJDIR)/Project_4328492.o \
  $(OBJDIR)/DuskMap_9b56ba2f.o \
  $(OBJDIR)/NavigatorTreeBuilder_5453e5b7.o \
  $(OBJDIR)/CodeHelpers_da0e0051.o \
  $(OBJDIR)/FileHelpers_1085b962.o \
  $(OBJDIR)/SourceCodeEditor_2a28b126.o \
  $(OBJDIR)/DocumentEditorComponent_da903b6e.o \
  $(OBJDIR)/plain-svg-icons_b76931c7.o \
  $(OBJDIR)/ExtendedFileTreeComponent_138def23.o \
  $(OBJDIR)/ExtendedLookAndFeel_eebc17c0.o \
  $(OBJDIR)/MainWindow_d6f61478.o \
  $(OBJDIR)/InnerPanel_b294a6f5.o \
  $(OBJDIR)/InnerPanels_a3b44568.o \
  $(OBJDIR)/InnerPanelContainers_f8510e27.o \
  $(OBJDIR)/Toolbars_9776797f.o \
  $(OBJDIR)/MainLayout_d65bd16a.o \
  $(OBJDIR)/Globals_d339a991.o \
  $(OBJDIR)/StoredSettings_dfdf196f.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_cryptography_25c7e826.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking Designi
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning Designi
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping Designi
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/DocumentManager_ab56030b.o: ../../Source/Core/DocumentManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DocumentManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Project_4328492.o: ../../Source/Core/Project.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Project.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DuskMap_9b56ba2f.o: ../../Source/Styles/DuskMap.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DuskMap.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NavigatorTreeBuilder_5453e5b7.o: ../../Source/Layouts/Extended/NavigatorTreeBuilder.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NavigatorTreeBuilder.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CodeHelpers_da0e0051.o: ../../Source/Layouts/Extended/CodeHelpers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CodeHelpers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileHelpers_1085b962.o: ../../Source/Layouts/Extended/FileHelpers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileHelpers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SourceCodeEditor_2a28b126.o: ../../Source/Layouts/Extended/SourceCodeEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SourceCodeEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DocumentEditorComponent_da903b6e.o: ../../Source/Layouts/Extended/DocumentEditorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DocumentEditorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/plain-svg-icons_b76931c7.o: ../../Source/Layouts/Extended/plain-svg-icons.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling plain-svg-icons.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ExtendedFileTreeComponent_138def23.o: ../../Source/Layouts/Extended/ExtendedFileTreeComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ExtendedFileTreeComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ExtendedLookAndFeel_eebc17c0.o: ../../Source/Layouts/ExtendedLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ExtendedLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_d6f61478.o: ../../Source/Layouts/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InnerPanel_b294a6f5.o: ../../Source/Layouts/MainLayout/InnerPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InnerPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InnerPanels_a3b44568.o: ../../Source/Layouts/MainLayout/InnerPanels.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InnerPanels.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InnerPanelContainers_f8510e27.o: ../../Source/Layouts/MainLayout/InnerPanelContainers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InnerPanelContainers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Toolbars_9776797f.o: ../../Source/Layouts/MainLayout/Toolbars.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Toolbars.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainLayout_d65bd16a.o: ../../Source/Layouts/MainLayout/MainLayout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainLayout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Globals_d339a991.o: ../../Source/Globals.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Globals.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StoredSettings_dfdf196f.o: ../../Source/StoredSettings.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StoredSettings.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_25c7e826.o: ../../JuceLibraryCode/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
