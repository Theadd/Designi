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
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
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
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := Designi
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/ejuce_RegularExpression_b5386072.o \
  $(OBJDIR)/pcre_chartables_e066a44a.o \
  $(OBJDIR)/pcre_compile_dc4bb5ce.o \
  $(OBJDIR)/pcre_config_a52a4591.o \
  $(OBJDIR)/pcre_dfa_exec_30afcc0.o \
  $(OBJDIR)/pcre_exec_9e91d1a0.o \
  $(OBJDIR)/pcre_fullinfo_c84568cc.o \
  $(OBJDIR)/pcre_get_91945131.o \
  $(OBJDIR)/pcre_globals_4732018b.o \
  $(OBJDIR)/pcre_info_a4d8ea7d.o \
  $(OBJDIR)/pcre_maketables_1e7afee2.o \
  $(OBJDIR)/pcre_ord2utf8_7ba82831.o \
  $(OBJDIR)/pcre_refcount_b6b411ab.o \
  $(OBJDIR)/pcre_study_124f3d64.o \
  $(OBJDIR)/pcre_tables_925fc3f4.o \
  $(OBJDIR)/pcre_try_flipped_f8b26cd9.o \
  $(OBJDIR)/pcre_ucp_findchar_7a5574db.o \
  $(OBJDIR)/pcre_valid_utf8_e2121ea3.o \
  $(OBJDIR)/pcre_version_dc336333.o \
  $(OBJDIR)/pcre_xclass_ac2cbecf.o \
  $(OBJDIR)/pcreposix_32a7e1f3.o \
  $(OBJDIR)/ucptable_a3e4d7e0.o \
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
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_devices_a4c8a728.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_cryptography_25c7e826.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \
  $(OBJDIR)/juce_video_184321c8.o \

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

$(OBJDIR)/ejuce_RegularExpression_b5386072.o: ../../Source/Libraries/ejuce_RegularExpression.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ejuce_RegularExpression.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_chartables_e066a44a.o: ../../Source/Libraries/pcre/pcre_chartables.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_chartables.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_compile_dc4bb5ce.o: ../../Source/Libraries/pcre/pcre_compile.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_compile.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_config_a52a4591.o: ../../Source/Libraries/pcre/pcre_config.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_config.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_dfa_exec_30afcc0.o: ../../Source/Libraries/pcre/pcre_dfa_exec.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_dfa_exec.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_exec_9e91d1a0.o: ../../Source/Libraries/pcre/pcre_exec.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_exec.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_fullinfo_c84568cc.o: ../../Source/Libraries/pcre/pcre_fullinfo.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_fullinfo.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_get_91945131.o: ../../Source/Libraries/pcre/pcre_get.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_get.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_globals_4732018b.o: ../../Source/Libraries/pcre/pcre_globals.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_globals.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_info_a4d8ea7d.o: ../../Source/Libraries/pcre/pcre_info.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_info.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_maketables_1e7afee2.o: ../../Source/Libraries/pcre/pcre_maketables.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_maketables.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_ord2utf8_7ba82831.o: ../../Source/Libraries/pcre/pcre_ord2utf8.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_ord2utf8.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_refcount_b6b411ab.o: ../../Source/Libraries/pcre/pcre_refcount.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_refcount.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_study_124f3d64.o: ../../Source/Libraries/pcre/pcre_study.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_study.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_tables_925fc3f4.o: ../../Source/Libraries/pcre/pcre_tables.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_tables.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_try_flipped_f8b26cd9.o: ../../Source/Libraries/pcre/pcre_try_flipped.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_try_flipped.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_ucp_findchar_7a5574db.o: ../../Source/Libraries/pcre/pcre_ucp_findchar.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_ucp_findchar.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_valid_utf8_e2121ea3.o: ../../Source/Libraries/pcre/pcre_valid_utf8.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_valid_utf8.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_version_dc336333.o: ../../Source/Libraries/pcre/pcre_version.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_version.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcre_xclass_ac2cbecf.o: ../../Source/Libraries/pcre/pcre_xclass.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcre_xclass.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcreposix_32a7e1f3.o: ../../Source/Libraries/pcre/pcreposix.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcreposix.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ucptable_a3e4d7e0.o: ../../Source/Libraries/pcre/ucptable.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ucptable.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

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

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: ../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
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

$(OBJDIR)/juce_video_184321c8.o: ../../JuceLibraryCode/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
