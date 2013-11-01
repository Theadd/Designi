/*
  ==============================================================================

    Default.cpp
    Created: 11 Oct 2013 9:22:22pm
    Author:  admin

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Globals.h"
#include "DuskMap.h"

//================== folder-open.svg ==================
static const unsigned char temp_82949625[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\r\n"
"<!-- Creator: CorelDRAW X6 -->\r\n"
"<svg xmlns=\"http://www.w3.org/2000/svg\" xml:space=\"preserve\" width=\"100%\" height=\"100%\" version=\"1.1\" style=\"shape-rendering:geometricPrecision; text-rendering:geometricPrecision; image-rendering:optimizeQuality; fill-rule:evenodd; clip-ru"
"le:evenodd\"\r\n"
"viewBox=\"0 0 500 500\"\r\n"
" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\r\n"
" <defs>\r\n"
"  <style type=\"text/css\">\r\n"
"   <![CDATA[\r\n"
"    .str1 {stroke:#2B2A29;stroke-width:0.1}\r\n"
"    .str0 {stroke:#434242;stroke-width:10}\r\n"
"    .str2 {stroke:#333333;stroke-width:20;stroke-linecap:round}\r\n"
"    .fil2 {fill:none}\r\n"
"    .fil0 {fill:url(#id0)}\r\n"
"    .fil1 {fill:url(#id1)}\r\n"
"   ]]>\r\n"
"  </style>\r\n"
"  <linearGradient id=\"id0\" gradientUnits=\"userSpaceOnUse\" x1=\"250.05\" y1=\"257.25\" x2=\"250.05\" y2=\"112.852\">\r\n"
"   <stop offset=\"0\" style=\"stop-color:#FCFCFD\"/>\r\n"
"   <stop offset=\"1\" style=\"stop-color:#EDEDED\"/>\r\n"
"  </linearGradient>\r\n"
"  <linearGradient id=\"id1\" gradientUnits=\"userSpaceOnUse\" x1=\"257.779\" y1=\"263.852\" x2=\"257.779\" y2=\"386.252\">\r\n"
"   <stop offset=\"0\" style=\"stop-color:#008BFF\"/>\r\n"
"   <stop offset=\"1\" style=\"stop-color:#00AAFF\"/>\r\n"
"  </linearGradient>\r\n"
" </defs>\r\n"
" <g id=\"Layer_x0020_1\">\r\n"
"  <metadata id=\"CorelCorpID_0Corel-Layer\"/>\r\n"
"  <path class=\"fil0 str0\" d=\"M50 280l0 -180c0,-5 5,-10 10,-10l140 0c20,0 20,30 40,30l200 0c6,0 10,5 10,10l0 150 -400 0z\"/>\r\n"
"  <path class=\"fil1 str0\" d=\"M60 410l380 0c5,0 9,-5 10,-10l25 -150c1,-5 -5,-10 -10,-10l-160 0c-20,0 -20,30 -40,30l-215 0c-5,0 -10,5 -10,10l10 120c1,6 5,10 10,10z\"/>\r\n"
"  <rect class=\"fil2 str1\" width=\"500\" height=\"500\"/>\r\n"
"  <line class=\"fil2 str2\" x1=\"85\" y1=\"120\" x2=\"185\" y2= \"120\" />\r\n"
" </g>\r\n"
"</svg>\r\n";

const char* folderopen_svg = (const char*) temp_82949625;

//================== folder-close.svg ==================
static const unsigned char temp_59b278a9[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\r\n"
"<!-- Creator: CorelDRAW X6 -->\r\n"
"<svg xmlns=\"http://www.w3.org/2000/svg\" xml:space=\"preserve\" width=\"100%\" height=\"100%\" version=\"1.1\" style=\"shape-rendering:geometricPrecision; text-rendering:geometricPrecision; image-rendering:optimizeQuality; fill-rule:evenodd; clip-ru"
"le:evenodd\"\r\n"
"viewBox=\"0 0 500 500\"\r\n"
" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\r\n"
" <defs>\r\n"
"  <style type=\"text/css\">\r\n"
"   <![CDATA[\r\n"
"    .str1 {stroke:#2B2A29;stroke-width:0.1}\r\n"
"    .str0 {stroke:#434242;stroke-width:10}\r\n"
"    .str2 {stroke:#333333;stroke-width:20;stroke-linecap:round}\r\n"
"    .fil2 {fill:none}\r\n"
"    .fil0 {fill:url(#id0)}\r\n"
"    .fil1 {fill:url(#id1)}\r\n"
"   ]]>\r\n"
"  </style>\r\n"
"  <linearGradient id=\"id0\" gradientUnits=\"userSpaceOnUse\" x1=\"250.05\" y1=\"90.052\" x2=\"250.05\" y2=\"195.052\">\r\n"
"   <stop offset=\"0\" style=\"stop-color:#FCFCFD\"/>\r\n"
"   <stop offset=\"1\" style=\"stop-color:#EDEDED\"/>\r\n"
"  </linearGradient>\r\n"
"  <linearGradient id=\"id1\" gradientUnits=\"userSpaceOnUse\" x1=\"250.036\" y1=\"171.55\" x2=\"250.036\" y2=\"383.552\">\r\n"
"   <stop offset=\"0\" style=\"stop-color:#008BFF\"/>\r\n"
"   <stop offset=\"1\" style=\"stop-color:#00AAFF\"/>\r\n"
"  </linearGradient>\r\n"
" </defs>\r\n"
" <g id=\"Layer_x0020_1\">\r\n"
"  <metadata id=\"CorelCorpID_0Corel-Layer\"/>\r\n"
"  <path class=\"fil0 str0\" d=\"M50 195l0 -95c0,-5 5,-10 10,-10l140 0c20,0 20,30 40,30l200 0c6,0 10,5 10,10l0 65 -400 0z\"/>\r\n"
"  <path class=\"fil1 str0\" d=\"M60 410l380 0c6,0 10,-4 10,-10l10 -245c0,-5 -4,-10 -10,-10l-150 0c-20,0 -20,30 -40,30l-210 0c-5,0 -10,5 -10,10l10 215c0,6 5,10 10,10z\"/>\r\n"
"  <rect class=\"fil2 str1\" width=\"500\" height=\"500\"/>\r\n"
"  <line class=\"fil2 str2\" x1=\"85\" y1=\"120\" x2=\"185\" y2= \"120\" />\r\n"
" </g>\r\n"
"</svg>\r\n";

const char* folderclose_svg = (const char*) temp_59b278a9;

//================== file.svg ==================
static const unsigned char temp_3409dacc[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\r\n"
"<svg xmlns=\"http://www.w3.org/2000/svg\" xml:space=\"preserve\" width=\"100%\" height=\"100%\" version=\"1.1\" shape-rendering=\"geometricPrecision\" text-rendering=\"geometricPrecision\" image-rendering=\"optimizeQuality\" fill-rule=\"evenodd\" cli"
"p-rule=\"evenodd\"\r\n"
"viewBox=\"0 0 500 500\"\r\n"
" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\r\n"
" <defs>\r\n"
"  <linearGradient y2=\"0\" x2=\"0\" y1=\"1\" x1=\"1\" id=\"btl\">\r\n"
"   <stop stop-color=\"#008BFF\" offset=\"0\"/>\r\n"
"   <stop stop-color=\"#00AAFF\" offset=\"1\"/>\r\n"
"  </linearGradient>\r\n"
"  <linearGradient y2=\"0\" x2=\"0\" y1=\"1\" x1=\"0\" id=\"wtb\">\r\n"
"   <stop stop-color=\"#FCFCFD\" offset=\"0\"/>\r\n"
"   <stop stop-color=\"#DDDEDE\" offset=\"1\"/>\r\n"
"  </linearGradient>\r\n"
" </defs>\r\n"
" <g id=\"Layer_x0020_1\">\r\n"
"  <path fill=\"url(#wtb)\" stroke=\"#434242\" stroke-width=\"15\" stroke-linecap=\"round\" stroke-linejoin=\"round\" d=\"M250 30l140 0c11,0 20,9 20,20l0 400c0,11 -9,20 -20,20l-280 0c-11,0 -20,-9 -20,-20l0 -260 160 -160z\"/>\r\n"
"  <path fill=\"url(#btl)\" stroke=\"#434242\" stroke-width=\"10\" stroke-linejoin=\"round\" d=\"M220 190l-130 0 160 -160 0 130c0,17 -14,30 -30,30z\"/>\r\n"
" </g>\r\n"
"</svg>\r\n";

const char* file_svg = (const char*) temp_3409dacc;

namespace LookAndFeelHelpers
{
    static Colour createBaseColour (Colour buttonColour,
                                    bool hasKeyboardFocus,
                                    bool isMouseOverButton,
                                    bool isButtonDown) noexcept
    {
        const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
        const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

        if (isButtonDown)      return baseColour.contrasting (0.2f);
        if (isMouseOverButton) return baseColour.contrasting (0.1f);

        return baseColour;
    }
	/*
    static TextLayout layoutTooltipText (const String& text, Colour colour) noexcept
    {
        const float tooltipFontSize = 13.0f;
        const int maxToolTipWidth = 400;

        AttributedString s;
        s.setJustification (Justification::centred);
        s.append (text, Font (tooltipFontSize, Font::bold), colour);

        TextLayout tl;
        tl.createLayoutWithBalancedLineLengths (s, (float) maxToolTipWidth);
        return tl;
    }

    static Typeface::Ptr getTypefaceForFontFromLookAndFeel (const Font& font)
    {
        return LookAndFeel::getDefaultLookAndFeel().getTypefaceForFont (font);
    }
	*/
}

DuskMapLookAndFeel::DuskMapLookAndFeel()
{
    setColour (mainBackgroundColourId, Colour::greyLevel (0.8f));
    setColour (treeviewHighlightColourId, Colour (0x401111ee));
    //setColour (TextButton::buttonColourId, Colour (0xffeeeeff));
	
	setColour (TextButton::buttonColourId,          Colour(Colour((juce::uint8) 83, (juce::uint8) 94, (juce::uint8) 104, (juce::uint8) 255)));
    setColour(TextButton::textColourOffId, Colours::transparentWhite.withAlpha(0.9f));
	setColour(TextButton::textColourOnId, Colours::blue.withAlpha(0.9f));
	setColour (ListBox::outlineColourId,            findColour (ComboBox::outlineColourId));
	//SCROLLBAR
    setColour (ScrollBar::thumbColourId,            Colours::white.withAlpha(0.2f));
    setColour (ScrollBar::backgroundColourId,       Colours::black.withAlpha(0.2f));
    setColour (Slider::thumbColourId,               Colours::yellow);
    setColour (Slider::trackColourId,               Colour (0x7f000000));
    setColour (Slider::textBoxOutlineColourId,      Colours::green);
    setColour (ProgressBar::backgroundColourId,     Colours::white.withAlpha (0.6f));
    setColour (ProgressBar::foregroundColourId,     Colours::green.withAlpha (0.7f));
    setColour (PopupMenu::backgroundColourId,				Colour((juce::uint8) 51, (juce::uint8) 57, (juce::uint8) 61, (juce::uint8) 255));
    setColour (PopupMenu::highlightedBackgroundColourId,	findColour (TextButton::buttonColourId));
    setColour (PopupMenu::highlightedTextColourId,			Colour((juce::uint8) 153, (juce::uint8) 209, (juce::uint8) 248, (juce::uint8) 255));
    setColour (PopupMenu::textColourId,						Colours::white);
	setColour (PopupMenu::headerTextColourId,				Colours::yellow.withAlpha(0.65f));
	setColour (TextEditor::focusedOutlineColourId,  findColour (TextButton::buttonColourId));
	//WINDOW BACKGROUND
	setColour (ResizableWindow::backgroundColourId,		Colour((juce::uint8) 51, (juce::uint8) 57, (juce::uint8) 61, (juce::uint8) 255));
	//TOOLBAR
	/*ColourIds {
	  backgroundColourId = 0x1003200, 
	  separatorColourId = 0x1003210, 
	  buttonMouseOverBackgroundColourId = 0x1003220, 
	  buttonMouseDownBackgroundColourId = 0x1003230,
	  labelTextColourId = 0x1003240, 
	  editingModeOutlineColourId = 0x1003250
	}*/
	setColour (Toolbar::backgroundColourId,	findColour (TextButton::buttonColourId));
	setColour (Toolbar::buttonMouseOverBackgroundColourId,	findColour (TextButton::buttonColourId).interpolatedWith(Colours::white, 0.1f));
	setColour (Toolbar::buttonMouseDownBackgroundColourId,	findColour (TextButton::buttonColourId).interpolatedWith(Colours::blue, 0.1f));
	//TABBED COMPONENT
	setColour (TabbedComponent::outlineColourId, Colours::black);
	setColour (TabbedButtonBar::tabOutlineColourId, Colours::black);
	setColour (TabbedButtonBar::frontOutlineColourId, Colours::black); 
	//LABEL
	setColour (Label::textColourId, Colours::white);
	//TREEVIEW
	//ColourIds { backgroundColourId = 0x1000500, linesColourId = 0x1000501, dragAndDropIndicatorColourId = 0x1000502 }
	setColour (TreeView::linesColourId, Colours::transparentBlack);
	//DirectoryContentsDisplayComponent (inherited by FileTreeComponent)
	//ColourIds { highlightColourId = 0x1000540, textColourId = 0x1000541 }
	setColour (DirectoryContentsDisplayComponent::textColourId, Colours::white);
	setColour (DirectoryContentsDisplayComponent::highlightColourId, Colours::white.withAlpha(0.1f));
}

DuskMapLookAndFeel::~DuskMapLookAndFeel()
{
	//folderImage = nullptr;
}

Colour DuskMapLookAndFeel::getScrollbarColourForBackground (Colour background)
{
    return background.contrasting().withAlpha (0.13f);
}

/*Rectangle<int> DuskMapLookAndFeel::getPropertyComponentContentPosition (PropertyComponent& component)
{
    if (component.findParentComponentOfClass<AppearanceEditor::EditorPanel>() != nullptr)
        return component.getLocalBounds().reduced (1).removeFromRight (component.getWidth() / 2);

    return LookAndFeel::getPropertyComponentContentPosition (component);
}*/

//int DuskMapLookAndFeel::getTabButtonOverlap (int /*tabDepth*/)                      { return -1; }
//int DuskMapLookAndFeel::getTabButtonSpaceAroundImage()                              { return 1; }
//int DuskMapLookAndFeel::getTabButtonBestWidth (TabBarButton&, int /*tabDepth*/)     { return 120; }

/*static void createTabTextLayout (const TabBarButton& button, const Rectangle<int>& textArea,
                                 const Colour colour, TextLayout& textLayout)
{

    Font font (textArea.getHeight() * 0.5f);
    font.setUnderline (button.hasKeyboardFocus (false));

    AttributedString s;
    s.setJustification (Justification::centred);
    s.append (button.getButtonText().trim(), font, colour);

    textLayout.createLayout (s, (float) textArea.getWidth());
}*/

/*Colour DuskMapLookAndFeel::getTabBackgroundColour (TabBarButton& button)
{
    const Colour bkg (button.findColour (mainBackgroundColourId).contrasting (0.15f));

    if (button.isFrontTab())
        return bkg.overlaidWith (Colours::yellow.withAlpha (0.5f));

    return bkg;
}*/

/*void DuskMapLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
	//LookAndFeel::drawTabButton(button, g, isMouseOver, isMouseDown);
	
    const Rectangle<int> activeArea (button.getActiveArea());

    const Colour bkg (getTabBackgroundColour (button));

    g.setGradientFill (ColourGradient (bkg.brighter (0.1f), 0, (float) activeArea.getY(),
                                       bkg.darker (0.1f), 0, (float) activeArea.getBottom(), false));
    g.fillRect (activeArea);

    g.setColour (button.findColour (mainBackgroundColourId).darker (0.3f));
    g.drawRect (activeArea);

    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
    const Colour col (bkg.contrasting().withMultipliedAlpha (alpha));

    TextLayout textLayout;
    createTabTextLayout (button, button.getTextArea(), col, textLayout);

    textLayout.draw (g, button.getTextArea().toFloat());
	
}*/

/*Rectangle<int> DuskMapLookAndFeel::getTabButtonExtraComponentBounds (const TabBarButton& button, Rectangle<int>& textArea, Component& comp)
{
    //return LookAndFeel::getTabButtonExtraComponentBounds(button, textArea, comp);
	TextLayout textLayout;
    createTabTextLayout (button, textArea, Colours::black, textLayout);
    const int textWidth = (int) textLayout.getWidth();
    const int extraSpace = jmax (0, textArea.getWidth() - (textWidth + comp.getWidth())) / 2;

    textArea.removeFromRight (extraSpace);
    textArea.removeFromLeft (extraSpace);
    return textArea.removeFromRight (comp.getWidth());
	
}*/


void DuskMapLookAndFeel::createTabButtonShape (TabBarButton& button, Path& p, bool /*isMouseOver*/, bool /*isMouseDown*/)
{
    const Rectangle<int> activeArea (button.getActiveArea());
    const float w = (float) activeArea.getWidth();
    const float h = (float) activeArea.getHeight();

    float length = w;
    float depth = h;

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

    const float indent = (float) getTabButtonOverlap ((int) depth);
    const float overhang = 4.0f;

    switch (button.getTabbedButtonBar().getOrientation())
    {
        case TabbedButtonBar::TabsAtLeft:
            p.startNewSubPath (w, 0.0f);
            p.lineTo (0.0f, indent);
            p.lineTo (0.0f, h - indent);
            p.lineTo (w, h);
            p.lineTo (w + overhang, h + overhang);
            p.lineTo (w + overhang, -overhang);
            break;

        case TabbedButtonBar::TabsAtRight:
            p.startNewSubPath (0.0f, 0.0f);
            p.lineTo (w, indent);
            p.lineTo (w, h - indent);
            p.lineTo (0.0f, h);
            p.lineTo (-overhang, h + overhang);
            p.lineTo (-overhang, -overhang);
            break;

        case TabbedButtonBar::TabsAtBottom:
            p.startNewSubPath (0.0f, 0.0f);
            p.lineTo (indent, h);
            p.lineTo (w - indent, h);
            p.lineTo (w, 0.0f);
            p.lineTo (w + overhang, -overhang);
            p.lineTo (-overhang, -overhang);
            break;

        default:
            p.startNewSubPath (0.0f, h);
            p.lineTo (indent, 0.0f);
            p.lineTo (w - indent, 0.0f);
            p.lineTo (w, h);
            p.lineTo (w + overhang, h + overhang);
            p.lineTo (-overhang, h + overhang);
            break;
    }

    p.closeSubPath();

    p = p.createPathWithRoundedCorners (3.0f);
}

int DuskMapLookAndFeel::getTabButtonOverlap (int tabDepth)
{
    return 1 + tabDepth / 3;
}

int DuskMapLookAndFeel::getTabButtonSpaceAroundImage()
{
    return 3;	//4
}

void DuskMapLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    Path tabShape;
    createTabButtonShape (button, tabShape, isMouseOver, isMouseDown);

    const Rectangle<int> activeArea (button.getActiveArea());
    tabShape.applyTransform (AffineTransform::translation ((float) activeArea.getX(),
                                                           (float) activeArea.getY()));

    DropShadow (Colours::black.withAlpha (0.5f), 2, Point<int> (0, 1)).drawForPath (g, tabShape);

    fillTabButtonShape (button, g, tabShape, isMouseOver, isMouseDown);
    drawTabButtonText (button, g, isMouseOver, isMouseDown);
}

void DuskMapLookAndFeel::fillTabButtonShape (TabBarButton& button, Graphics& g, const Path& path,  bool /*isMouseOver*/, bool /*isMouseDown*/)
{
    const Colour tabBackground (button.getTabBackgroundColour());
    const bool isFrontTab = button.isFrontTab();

    g.setColour (isFrontTab ? tabBackground
                            : tabBackground.brighter(0.08f));

    g.fillPath (path);

    g.setColour (button.findColour (isFrontTab ? TabbedButtonBar::frontOutlineColourId
                                               : TabbedButtonBar::tabOutlineColourId, false)
                    .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    g.strokePath (path, PathStrokeType (isFrontTab ? 1.0f : 0.5f));
}

void DuskMapLookAndFeel::drawStretchableLayoutResizerBar (Graphics& g, int /*w*/, int /*h*/, bool /*isVerticalBar*/, bool isMouseOver, bool isMouseDragging)
{
    if (isMouseOver || isMouseDragging)
        g.fillAll (Colours::yellow.withAlpha (0.4f));
}

void DuskMapLookAndFeel::drawScrollbar (Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height,
                                           bool isScrollbarVertical, int thumbStartPosition, int thumbSize,
                                           bool isMouseOver, bool isMouseDown)
{
    //Draw scrollbar background
	g.fillAll(scrollbar.findColour (ScrollBar::backgroundColourId));

	//draw scrollbar
	Path thumbPath;
    if (thumbSize > 0)
    {
        /*const float thumbIndent = (isScrollbarVertical ? width : height) * 0.25f;
        const float thumbIndentx2 = thumbIndent * 2.0f;

        if (isScrollbarVertical)
            thumbPath.addRoundedRectangle (x + thumbIndent, thumbStartPosition + thumbIndent,
                                           width - thumbIndentx2, thumbSize - thumbIndentx2, (width - thumbIndentx2) * 0.5f);
        else
            thumbPath.addRoundedRectangle (thumbStartPosition + thumbIndent, y + thumbIndent,
                                           thumbSize - thumbIndentx2, height - thumbIndentx2, (height - thumbIndentx2) * 0.5f);
		*/
		if (isScrollbarVertical)
			thumbPath.addRectangle((float) x, (float) thumbStartPosition, (float) width, (float) thumbSize);
		else
			thumbPath.addRectangle((float) thumbStartPosition, (float) y, (float) thumbSize, (float) height);
	}

    Colour thumbCol (findColour (ScrollBar::thumbColourId));

    if (isMouseOver || isMouseDown)
        thumbCol = thumbCol.withMultipliedAlpha (2.0f);

    g.setColour (thumbCol);
    g.fillPath (thumbPath);

	//draw scrollbar left border
	g.setColour(Colours::black);
	g.drawVerticalLine(x, 0.0f, (float) scrollbar.getHeight());

    //g.setColour (thumbCol.contrasting ((isMouseOver  || isMouseDown) ? 0.2f : 0.1f));
    //g.strokePath (thumbPath, PathStrokeType (1.0f));
}

static Range<float> getBrightnessRange (const Image& im)
{
    float minB = 1.0f, maxB = 0;
    const int w = im.getWidth();
    const int h = im.getHeight();

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            const float b = im.getPixelAt (x, y).getBrightness();
            minB = jmin (minB, b);
            maxB = jmax (maxB, b);
        }
    }

    return Range<float> (minB, maxB);
}

void DuskMapLookAndFeel::fillWithBackgroundTexture (Graphics& g)
{
    const Colour bkg (findColour (mainBackgroundColourId));

    if (backgroundTextureBaseColour != bkg)
    {
        backgroundTextureBaseColour = bkg;

        const Image original (ImageCache::getFromMemory (BinaryData::background_tile_png,
                                                         BinaryData::background_tile_pngSize));
        const int w = original.getWidth();
        const int h = original.getHeight();

        backgroundTexture = Image (Image::RGB, w, h, false);

        const Range<float> brightnessRange (getBrightnessRange (original));
        const float brightnessOffset = (brightnessRange.getStart() + brightnessRange.getEnd()) / 2.0f;
        const float brightnessScale = 0.025f / brightnessRange.getLength();
        const float bkgB = bkg.getBrightness();

        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                const float b = (original.getPixelAt (x, y).getBrightness() - brightnessOffset) * brightnessScale;
                backgroundTexture.setPixelAt (x, y, bkg.withBrightness (jlimit (0.0f, 1.0f, bkgB + b)));
            }
        }
    }

    g.setTiledImageFill (backgroundTexture, 0, 0, 1.0f);
    g.fillAll();
}

void DuskMapLookAndFeel::fillWithBackgroundTexture (Component& c, Graphics& g)
{
    dynamic_cast<DuskMapLookAndFeel&> (c.getLookAndFeel()).fillWithBackgroundTexture (g);
}



void DuskMapLookAndFeel::drawConcertinaPanelHeader (Graphics& g, const Rectangle<int>& area,
                                                       bool isMouseOver, bool ,
                                                       ConcertinaPanel&, Component& panel)
{
    const Colour bkg (findColour (mainBackgroundColourId));

    g.setGradientFill (ColourGradient (Colours::white.withAlpha (isMouseOver ? 0.4f : 0.2f), 0, (float) area.getY(),
                                       Colours::darkgrey.withAlpha (0.2f), 0, (float) area.getBottom(), false));

    g.fillAll();
    g.setColour (bkg.contrasting().withAlpha (0.04f));
    g.fillRect (area.withHeight (1));
    g.fillRect (area.withTop (area.getBottom() - 1));

    g.setColour (bkg.contrasting());
    g.setFont (Font (area.getHeight() * 0.6f).boldened());
    g.drawFittedText (panel.getName(), 4, 0, area.getWidth() - 6, area.getHeight(), Justification::centredLeft, 1);
}


void DuskMapLookAndFeel::drawButtonBackground (Graphics& g,
                                                 Button& button,
                                                 const Colour& backgroundColour,
                                                 bool isMouseOverButton,
                                                 bool isButtonDown)
{

	bool flatOnLeft = button.isConnectedOnLeft();
	bool flatOnRight = button.isConnectedOnRight();
	bool flatOnTop = button.isConnectedOnTop();
	bool flatOnBottom = button.isConnectedOnBottom();
	bool roundedUpperLeft = (!(flatOnLeft || flatOnTop));
	bool roundedUpperRight = (!(flatOnRight || flatOnTop));
	bool roundedBottomLeft = (!(flatOnLeft || flatOnBottom));
	bool roundedBottomRight = (!(flatOnRight || flatOnBottom));

    float width = (float) button.getWidth();
    float height = (float) button.getHeight();

    float cornerSize = 5.0f;	//jmin (roundToInt (width * 0.4f), roundToInt (height * 0.4f));

    Path p;
    p.addRoundedRectangle (0.0f, 0.0f, width, height, cornerSize, cornerSize,
                                 ! (flatOnLeft || flatOnTop),
                                 ! (flatOnRight || flatOnTop),
                                 ! (flatOnLeft || flatOnBottom),
                                 ! (flatOnRight || flatOnBottom));

	Colour colour = (isMouseOverButton) ? backgroundColour.brighter(0.1f) : backgroundColour;
	//if (!isButtonDown) {
        ColourGradient cg (colour, 0, 0,
                           colour.darker (0.7f), 0, 0 + height, false);

        cg.addColour (0.1, colour.brighter(0.1f));
        //cg.addColour (0.4, colour);
        //cg.addColour (0.97, colour.withMultipliedAlpha (0.3f));

        g.setGradientFill (cg);
        g.fillPath (p);
		g.setColour(colour.brighter(0.4f));
		
		g.drawHorizontalLine(1, (roundedUpperLeft) ? 4.0f : 1.0f, (roundedUpperRight) ? ((float) width) - 4.0f : (float) width);
		if (roundedUpperLeft) {
			g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(1, 3, 4);
			//g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(2, 2, 3);
		}
		if (roundedUpperRight) {
			g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(1, width - 4, width - 3);
			//g.setColour(colour.brighter(0.2f));
			g.drawHorizontalLine(2, width - 3, width - 2);
		}

    //}

	if (isButtonDown) {
		g.setColour(Colours::black);
		g.setOpacity(0.5f);
		g.fillPath (p);
	}

	//draw border
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
    g.strokePath (p, PathStrokeType(1.0f));//PathStrokeType ((isMouseOverButton) ? 1.0f : 1.0f));
	//g.strokePath (p, PathStrokeType(1.0f));


	//Draw brighter 1px vertical gradient on the right
	if (!isButtonDown) {
		g.setGradientFill (ColourGradient (colour, width - 1, 0, Colours::grey.withAlpha(0.7f), width - 1, height, false));
		if (!roundedUpperRight && !roundedBottomRight)
			g.fillRect(width - 1.0f, 2.0f, 1.0f, height - 3.0f);
	

		//draw darker 1px vertical line on the left
		if (!roundedUpperLeft && !roundedBottomLeft) {
			g.setColour(Colours::darkgrey.withAlpha(0.3f));
			g.fillRect(0.0f, 2.0f, 1.0f, height - 3.0f);
		}
	}

	//fix pixels
	if (!isButtonDown) {
		if (!roundedUpperRight) {
			g.setColour(colour.brighter(0.4f));
			g.drawHorizontalLine(1, width - 1, width);
		}
		if (!roundedUpperLeft) {
			g.setColour(colour.brighter(0.4f));
			g.drawHorizontalLine(1, 0, 1);
		}
	}

	//Redraw border
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
	g.drawHorizontalLine(0, (roundedUpperLeft) ? 4.0f : 0.0f, (roundedUpperRight) ? width - 4.0f : width);
	g.drawHorizontalLine((int) height, (roundedBottomLeft) ? 4.0f : 0.0f, (roundedBottomRight) ? width - 4.0f : width);
	if (!(!roundedUpperLeft && !roundedBottomLeft))
		g.drawVerticalLine(0, (roundedUpperLeft) ? 4.0f : 0.0f, (roundedBottomLeft) ? height - 4.0f : height);
	if (!(!roundedUpperRight && !roundedBottomRight))
		g.drawVerticalLine((int) width, (roundedUpperRight) ? 4.0f : 0.0f, (roundedBottomRight) ? height - 4.0f : height);

	
}

/*void DuskMapLookAndFeel::drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header)
{
    Rectangle<int> r (header.getLocalBounds());

    g.setColour (Colours::black.withAlpha (0.5f));
    g.fillRect (r.removeFromBottom (1));

    g.setColour (Colours::white.withAlpha (0.6f));
    g.fillRect (r);

    g.setColour (Colours::black.withAlpha (0.5f));

    for (int i = header.getNumColumns (true); --i >= 0;)
        g.fillRect (header.getColumnPosition (i).removeFromRight (1));
}
*/

void DuskMapLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    const Colour background (findColour (PopupMenu::backgroundColourId));

    g.fillAll (background);
    /*g.setColour (background.overlaidWith (Colour (0x2badd8e6)));

    for (int i = 0; i < height; i += 3)
        g.fillRect (0, i, width, 1);
	*/
#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
}

void DuskMapLookAndFeel::drawMenuBarBackground (Graphics& g, int /*width*/, int /*height*/,
                                         bool, MenuBarComponent& menuBar)
{
    const Colour baseColour (LookAndFeelHelpers::createBaseColour (menuBar.findColour (PopupMenu::backgroundColourId), false, false, false));
	const Colour background (findColour (PopupMenu::backgroundColourId));

    if (menuBar.isEnabled())
    {
        g.fillAll (background);
    }
    else
    {
        g.fillAll (baseColour);
    }
}

void DuskMapLookAndFeel::drawTreeviewPlusMinusBox (Graphics& g, const Rectangle< float > &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
{
	drawTreeviewPlusMinusBox (g, area.getX(), area.getY(), area.getWidth(), area.getHeight(), !isOpen, isMouseOver);
}

void DuskMapLookAndFeel::drawTreeviewPlusMinusBox (Graphics& g, int x, int y, int w, int h, bool isPlus, bool isMouseOver)
{
    const int boxSize = ((jmin (16, w, h) << 1) / 3) | 1;

    x += ((w - boxSize) >> 1) + 8;
    y += ((h - boxSize) >> 1) + 2;
	if (isPlus)
	{
		w = 6;
		h = 8;
	}
	else
	{
		w = 8;
		h = 6;
		x -= 1;
		y += 2;
	}

	Path p;

	if (isPlus)
		p.addTriangle((float) x, (float) y, (float) (x + w), (float) (y + (h / 2)), (float) x, (float) (y + h));
	else
		p.addTriangle((float) x, (float) y, (float) (x + w), (float) y, (float) (x + (w / 2)), (float) (y + h));

	if (!isMouseOver)
		g.setColour(Colours::white.withAlpha(0.8f));
	else
		g.setColour(Colours::white);

    g.fillPath (p);
}

int DuskMapLookAndFeel::getDefaultScrollbarWidth ()
{
	return 12;
}


void DuskMapLookAndFeel::drawFileBrowserRow (Graphics& g, int width, int height,
                                      const String& filename, Image* icon,
                                      const String& fileSizeDescription,
                                      const String& fileTimeDescription,
                                      const bool isDirectory,
                                      const bool isItemSelected,
                                      const int itemIndex,
                                      DirectoryContentsDisplayComponent& dcc)
{
	String id;
	if (!isDirectory)
	{
		id = filename.fromLastOccurrenceOf(".", true, true);
		if (id.isEmpty())
			id = "unknown";
	}
	else
	{
		id = "folder";
	}
	//DBG("[drawFileBrowserRow] filename = "+filename+", isItemSelected = "+String(isItemSelected)+", itemIndex = "+String(itemIndex));
	//dcc.getOpennessState()
	
	//bool isOpen = (dynamic_cast <TreeView *> (&dcc))->getItemOnRow(itemIndex)->isOpen();

	//TreeView *tree = dynamic_cast <TreeView *> (&dcc);
	//DBG("\tgetting item from TreeView on index = "+String(itemIndex));
	//TreeViewItem *item = tree->getItemOnRow(itemIndex);
	//DBG("\tisOpen = "+String(item->isOpen())+" Identifier String = #"+String(item->getItemIdentifierString())+"#, unique name = "+item->getUniqueName());
	//bool isOpen = item->isOpen();


	//set icon for file type
	if (!isDirectory)
	{
		if (id.equalsIgnoreCase(".cpp"))
			icon = &ImageCache::getFromMemory (BinaryData::file_cpp_png, BinaryData::file_cpp_pngSize);
		else if (id.equalsIgnoreCase(".h"))
			icon = &ImageCache::getFromMemory (BinaryData::file_h_png, BinaryData::file_h_pngSize);
		else if (id.equalsIgnoreCase(".design"))
			icon = &ImageCache::getFromMemory (BinaryData::penbrush_png, BinaryData::penbrush_pngSize);
		else 
			icon = &ImageCache::getFromMemory (BinaryData::note_png, BinaryData::note_pngSize);
	}
	else
	{
		if (isItemSelected)
			icon = &ImageCache::getFromMemory (BinaryData::folderopen_png, BinaryData::folderopen_pngSize);
		else
			icon = &ImageCache::getFromMemory (BinaryData::folderclose_png, BinaryData::folderclose_pngSize);
	}

	LookAndFeel_V3::drawFileBrowserRow (g, width, height, filename, icon, fileSizeDescription, fileTimeDescription, false /*isDirectory*/, isItemSelected, itemIndex, dcc);

}

