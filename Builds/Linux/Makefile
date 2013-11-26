# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := Designi
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := Designi
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/MainWindow_f4cdd931.o \
  $(OBJDIR)/MainLayout_4de6c98b.o \
  $(OBJDIR)/Toolbars_3bf305e0.o \
  $(OBJDIR)/ExtendedFileTreeComponent_f94a5bfb.o \
  $(OBJDIR)/KeyMappingsPanel_48f9caa3.o \
  $(OBJDIR)/JucerTreeViewBase_80b6c139.o \
  $(OBJDIR)/ProjectExplorerPanel_18f9c08f.o \
  $(OBJDIR)/InnerPanels_4958efec.o \
  $(OBJDIR)/SourceCodeEditor_d7215ee5.o \
  $(OBJDIR)/DocumentEditorComponent_582dd592.o \
  $(OBJDIR)/InnerPanel_5073d21b.o \
  $(OBJDIR)/InnerPanelContainers_8f6901cd.o \
  $(OBJDIR)/ExtendedLookAndFeel_8c7c4334.o \
  $(OBJDIR)/plain-svg-icons_b414307d.o \
  $(OBJDIR)/DuskMap_5723f766.o \
  $(OBJDIR)/BaseOnly_f3ecfd1e.o \
  $(OBJDIR)/NavigatorTreeBuilder_6f3593c.o \
  $(OBJDIR)/CodeHelpers_2b8707d1.o \
  $(OBJDIR)/FileHelpers_61fec0e2.o \
  $(OBJDIR)/Globals_61599329.o \
  $(OBJDIR)/MiscUtilities_3f9b06ec.o \
  $(OBJDIR)/Module_a8092c33.o \
  $(OBJDIR)/ProjectExporter_f4e7a7d.o \
  $(OBJDIR)/ProjectType_5b72fd56.o \
  $(OBJDIR)/ResourceFile_34d717f1.o \
  $(OBJDIR)/StoredSettings_68a600d7.o \
  $(OBJDIR)/DocumentManager_ab56030b.o \
  $(OBJDIR)/Project_4328492.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_cryptography_25c7e826.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \

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

$(OBJDIR)/MainWindow_f4cdd931.o: ../../Source/UI/Windows/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainLayout_4de6c98b.o: ../../Source/UI/Windows/MainWindow/MainLayout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainLayout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Toolbars_3bf305e0.o: ../../Source/UI/Windows/MainWindow/Toolbars.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Toolbars.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ExtendedFileTreeComponent_f94a5bfb.o: ../../Source/UI/Components/Extended/ExtendedFileTreeComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ExtendedFileTreeComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/KeyMappingsPanel_48f9caa3.o: ../../Source/UI/Components/Panels/KeyMappingsPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling KeyMappingsPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/JucerTreeViewBase_80b6c139.o: ../../Source/UI/Components/Panels/ProjectExplorerPanel/JucerTreeViewBase.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling JucerTreeViewBase.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ProjectExplorerPanel_18f9c08f.o: ../../Source/UI/Components/Panels/ProjectExplorerPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ProjectExplorerPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InnerPanels_4958efec.o: ../../Source/UI/Components/Panels/InnerPanels.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InnerPanels.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SourceCodeEditor_d7215ee5.o: ../../Source/UI/Components/Editors/SourceCodeEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SourceCodeEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DocumentEditorComponent_582dd592.o: ../../Source/UI/Components/Basics/DocumentEditorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DocumentEditorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InnerPanel_5073d21b.o: ../../Source/UI/Components/Basics/InnerPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InnerPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InnerPanelContainers_8f6901cd.o: ../../Source/UI/Components/Basics/InnerPanelContainers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InnerPanelContainers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ExtendedLookAndFeel_8c7c4334.o: ../../Source/UI/Styles/ExtendedLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ExtendedLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/plain-svg-icons_b414307d.o: ../../Source/UI/Styles/plain-svg-icons.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling plain-svg-icons.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DuskMap_5723f766.o: ../../Source/UI/Styles/DuskMap/DuskMap.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DuskMap.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BaseOnly_f3ecfd1e.o: ../../Source/UI/Styles/BaseOnly/BaseOnly.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BaseOnly.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NavigatorTreeBuilder_6f3593c.o: ../../Source/UI/Workers/NavigatorTreeBuilder.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NavigatorTreeBuilder.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CodeHelpers_2b8707d1.o: ../../Source/UI/Misc/CodeHelpers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CodeHelpers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileHelpers_61fec0e2.o: ../../Source/UI/Misc/FileHelpers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileHelpers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Globals_61599329.o: ../../Source/UI/Misc/Globals.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Globals.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MiscUtilities_3f9b06ec.o: ../../Source/Core/Misc/MiscUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MiscUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Module_a8092c33.o: ../../Source/Core/Project/Module.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Module.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ProjectExporter_f4e7a7d.o: ../../Source/Core/Project/ProjectExporter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ProjectExporter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ProjectType_5b72fd56.o: ../../Source/Core/Project/ProjectType.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ProjectType.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ResourceFile_34d717f1.o: ../../Source/Core/Project/ResourceFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ResourceFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StoredSettings_68a600d7.o: ../../Source/Core/StoredSettings.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StoredSettings.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DocumentManager_ab56030b.o: ../../Source/Core/DocumentManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DocumentManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Project_4328492.o: ../../Source/Core/Project.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Project.cpp"
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

$(OBJDIR)/juce_opengl_c7e3506c.o: ../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
