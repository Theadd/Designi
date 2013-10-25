/*
  ==============================================================================

    Toolbars.h
    Created: 15 Oct 2013 1:23:41am
    Author:  admin

  ==============================================================================
*/

#ifndef __TOOLBARS_H_51B0CF0E__
#define __TOOLBARS_H_51B0CF0E__


class ToolbarComponent   : public Component
{
public:
    ToolbarComponent(int _toolbarThickness);

    void resized();

	void setVertical (bool shouldBeVertical);
	bool isVertical ();

	void showCustomisationDialog ();

	int getToolbarThickness();
	void setToolbarThickness(int newThickness);

private:
	int toolbarThickness;
    Toolbar toolbar;
	bool _isVertical;

    //==============================================================================
    class ToolbarComponentItemFactory   : public ToolbarItemFactory
    {
    public:
        ToolbarComponentItemFactory();

        //==============================================================================
        // Each type of item a toolbar can contain must be given a unique ID. These
        // are the ones we'll use in this demo.
        enum ToolbarItemIds
        {
            doc_new         = 1,
            doc_open        = 2,
            doc_save        = 3,
            doc_saveAs      = 4,
            edit_copy       = 5,
            edit_cut        = 6,
            edit_paste      = 7
        };

        void getAllToolbarItemIds (Array <int>& ids);

        void getDefaultItemSet (Array <int>& ids);

        ToolbarItemComponent* createItem (int itemId);

    private:
        StringArray iconNames;
        OwnedArray <Drawable> iconsFromZipFile;

        // This is a little utility to create a button with one of the SVG images in
        // our embedded ZIP file "icons.zip"
        ToolbarButton* createButtonFromZipFileSVG (const int itemId, const String& text, const String& filename);

    };

    ToolbarComponentItemFactory factory;
};


#endif  // __TOOLBARS_H_51B0CF0E__
