/*
  ==============================================================================

    Default.cpp
    Created: 11 Oct 2013 9:22:22pm
    Author:  admin

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "DuskMap.h"


DuskMapLookAndFeel::DuskMapLookAndFeel()
{
    setColour (mainBackgroundColourId, Colour::greyLevel (0.8f));
    setColour (treeviewHighlightColourId, Colour (0x401111ee));
    setColour (TextButton::buttonColourId, Colour (0xffeeeeff));

    setColour (ScrollBar::thumbColourId,
               getScrollbarColourForBackground (findColour (mainBackgroundColourId)));
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

int DuskMapLookAndFeel::getTabButtonOverlap (int /*tabDepth*/)                      { return -1; }
int DuskMapLookAndFeel::getTabButtonSpaceAroundImage()                              { return 1; }
int DuskMapLookAndFeel::getTabButtonBestWidth (TabBarButton&, int /*tabDepth*/)     { return 120; }

static void createTabTextLayout (const TabBarButton& button, const Rectangle<int>& textArea,
                                 const Colour colour, TextLayout& textLayout)
{
    Font font (textArea.getHeight() * 0.5f);
    font.setUnderline (button.hasKeyboardFocus (false));

    AttributedString s;
    s.setJustification (Justification::centred);
    s.append (button.getButtonText().trim(), font, colour);

    textLayout.createLayout (s, (float) textArea.getWidth());
}

Colour DuskMapLookAndFeel::getTabBackgroundColour (TabBarButton& button)
{
    const Colour bkg (button.findColour (mainBackgroundColourId).contrasting (0.15f));

    if (button.isFrontTab())
        return bkg.overlaidWith (Colours::yellow.withAlpha (0.5f));

    return bkg;
}

void DuskMapLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
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
}

Rectangle<int> DuskMapLookAndFeel::getTabButtonExtraComponentBounds (const TabBarButton& button, Rectangle<int>& textArea, Component& comp)
{
    TextLayout textLayout;
    createTabTextLayout (button, textArea, Colours::black, textLayout);
    const int textWidth = (int) textLayout.getWidth();
    const int extraSpace = jmax (0, textArea.getWidth() - (textWidth + comp.getWidth())) / 2;

    textArea.removeFromRight (extraSpace);
    textArea.removeFromLeft (extraSpace);
    return textArea.removeFromRight (comp.getWidth());
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
    Path thumbPath;

    if (thumbSize > 0)
    {
        const float thumbIndent = (isScrollbarVertical ? width : height) * 0.25f;
        const float thumbIndentx2 = thumbIndent * 2.0f;

        if (isScrollbarVertical)
            thumbPath.addRoundedRectangle (x + thumbIndent, thumbStartPosition + thumbIndent,
                                           width - thumbIndentx2, thumbSize - thumbIndentx2, (width - thumbIndentx2) * 0.5f);
        else
            thumbPath.addRoundedRectangle (thumbStartPosition + thumbIndent, y + thumbIndent,
                                           thumbSize - thumbIndentx2, height - thumbIndentx2, (height - thumbIndentx2) * 0.5f);
    }

    Colour thumbCol (scrollbar.findColour (ScrollBar::thumbColourId, true));

    if (isMouseOver || isMouseDown)
        thumbCol = thumbCol.withMultipliedAlpha (2.0f);

    g.setColour (thumbCol);
    g.fillPath (thumbPath);

    g.setColour (thumbCol.contrasting ((isMouseOver  || isMouseDown) ? 0.2f : 0.1f));
    g.strokePath (thumbPath, PathStrokeType (1.0f));
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
                                                       bool isMouseOver, bool /*isMouseDown*/,
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
    const bool flatOnLeft   = button.isConnectedOnLeft();
    const bool flatOnRight  = button.isConnectedOnRight();
    const bool flatOnTop    = button.isConnectedOnTop();
    const bool flatOnBottom = button.isConnectedOnBottom();

    const float width  = (float) button.getWidth();
    const float height = (float) button.getHeight();

    const float x = 0.5f;
    const float y = 0.5f;
    const float w = width  - 1.0f;
    const float h = height - 1.0f;
    const float cornerSize = 4.0f;

    Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true)
                                                                      ? 1.3f : 0.9f)
                                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

    if (isButtonDown)           baseColour = baseColour.contrasting (0.2f);
    else if (isMouseOverButton) baseColour = baseColour.contrasting (0.1f);

    const float mainBrightness = baseColour.getBrightness();
    const float mainAlpha = baseColour.getFloatAlpha();

    Path outline;
    outline.addRoundedRectangle (x, y, w, h, cornerSize, cornerSize,
                                 ! (flatOnLeft  || flatOnTop),
                                 ! (flatOnRight || flatOnTop),
                                 ! (flatOnLeft  || flatOnBottom),
                                 ! (flatOnRight || flatOnBottom));

    g.setGradientFill (ColourGradient (baseColour.brighter (0.2f), 0.0f, 0.0f,
                                       baseColour.darker (0.25f), 0.0f, height, false));
    g.fillPath (outline);

    g.setColour (Colours::white.withAlpha (0.4f * mainAlpha * mainBrightness * mainBrightness));
    g.strokePath (outline, PathStrokeType (1.0f), AffineTransform::translation (0.0f, 1.0f)
                                                        .scaled (1.0f, (h - 1.6f) / h));

    g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
    g.strokePath (outline, PathStrokeType (1.0f));
}

void DuskMapLookAndFeel::drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header)
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
