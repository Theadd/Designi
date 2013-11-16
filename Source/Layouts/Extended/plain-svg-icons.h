/*
  ==============================================================================

    plain-svg-icons.h
    Created: 10 Nov 2013 7:01:43am
    Author:  admin

  ==============================================================================
*/

#ifndef __PLAINSVGICONS_H_194AE742__
#define __PLAINSVGICONS_H_194AE742__


extern const char* plainsvgicons_zip;
const int plainsvgicons_zipSize = 666697;

class Icons
{
public:

	enum Scheme
	{
		blue = 0,
		yellow = 1,
		lightgray = 2
	};


	static Drawable* get (String name, Scheme colour)
	{
		return getDrawableFromZipFile (name, (int) colour);
	}

private:

	static void HighlightActiveColorFromSVG(XmlElement* xmlSource, bool blackAndWhite = false)
	{
		forEachXmlChildElement (*xmlSource, xmlnode)
		{
			forEachXmlChildElement (*xmlnode, xmlouterdefs)
			{
				forEachXmlChildElement (*xmlouterdefs, xmldefs)
				{
					String style = xmldefs->getStringAttribute("style");
					if (style.isNotEmpty())
					{
						if (!blackAndWhite)	//yellow
						{
							/*style = style.replace("#008bff", "#e8d500", true);
							style = style.replace("#00aaff", "#ffea00", true);
							style = style.replace("#4eafff", "#ffdc00", true);*/
							style = style.replace("#008bff", "#d9d392", true);
							style = style.replace("#00aaff", "#d9d176", true);
							style = style.replace("#4eafff", "#d8d3a4", true);
						}
						else	//light gray
						{
							style = style.replace("#008bff", "#eaeaea", true);
							style = style.replace("#00aaff", "#d3d3d3", true);
							style = style.replace("#4eafff", "#d8d8d8", true);
						}
						
						xmldefs->setAttribute("style", style);
					}
				}
			}
		}
	}

	/** highlight: {0 = blue, 1 = yellow, 2 = light gray} */
	static Drawable* getDrawableFromZipFile(String filename, int highlight = 0)
	{
		MemoryInputStream iconsFileStream (plainsvgicons_zip, plainsvgicons_zipSize, false);
		ZipFile icons (&iconsFileStream, false);

		const ZipFile::ZipEntry* zipEntry = icons.getEntry(filename);
		InputStream* stream = icons.createStreamForEntry(*zipEntry);
		String xmldata = stream->readEntireStreamAsString();
		delete stream;
		ScopedPointer<XmlElement> svg (XmlDocument::parse (xmldata));//(BinaryData::wrench_svg));

		if (highlight == 1)
			HighlightActiveColorFromSVG(svg);
		if (highlight == 2)
			HighlightActiveColorFromSVG(svg, true);

		if (svg != nullptr)
			return Drawable::createFromSVG (*svg);

		return nullptr;
	}
};

#endif  // __PLAINSVGICONS_H_194AE742__
