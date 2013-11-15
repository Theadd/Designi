/*
  ==============================================================================

    NavigatorTreeBuilder.cpp
    Created: 15 Nov 2013 3:10:48pm
    Author:  admin

  ==============================================================================
*/
#include "../../../JuceLibraryCode/JuceHeader.h"
#include "NavigatorTreeBuilder.h"

#include "../../Application.h"

NavigatorTreeBuilder::NavigatorTreeBuilder () :	thread ("NavigatorTreeBuilder"),
												navigatorTree ("navigator"),
												editor (nullptr)
{
	thread.addTimeSliceClient (this);
	thread.startThread (0);	//low priority thread

}

NavigatorTreeBuilder::~NavigatorTreeBuilder ()
{
	thread.stopThread(300);
	thread.removeTimeSliceClient (this);
}

void NavigatorTreeBuilder::setDocumentEditorComponent (DocumentEditorComponent* editor_)
{
	editor = editor_;
}

int NavigatorTreeBuilder::useTimeSlice()
{
	int nextCallTime = 2000;
	if (editor != nullptr)
	{
		String code = editor->getCodeDocument().getAllContent();
		stripUnsafeCode (code);

		if (isValidSource(code))
		{
			getNavigatorTree(code);
			const MessageManagerLock mmLock;
			if (!editor->navigatorTree.getProperty("hash").equals(navigatorTree.getProperty("hash")) && !thread.threadShouldExit())
			{
				DBG("\tnavigatorTree hash differs!");
				editor->navigatorTree = navigatorTree;
				JUCEDesignerApp::getApp().navigatorTree = navigatorTree;
			}

			nextCallTime = 5000;
		}
		else
		{
			nextCallTime = 1000;
		}
	}
	else
		nextCallTime = 300;

	return nextCallTime;
}


ValueTree NavigatorTreeBuilder::getNavigatorTree (String& code)
{
	//DBG("\tValueTree SourceCodeEditor::getNavigatorTree ()");
	/*CodeDocument& codeDocument = editor->getCodeDocument();
	String code = codeDocument.getAllContent();
	
	stripUnsafeCode (code);*/

	
	navigatorTree = ValueTree("navigator");
	updateNavigatorTree(navigatorTree, code);
	int64 hashCode64 = navigatorTree.toXmlString().hashCode64();
	navigatorTree.setProperty("hash", hashCode64, 0);
	
	/*File temp("C:/multiline.txt");
	temp.create();
	temp.replaceWithText(code);
	File temp2("C:/navigator.txt");
	temp2.create();
	temp2.replaceWithText(navigatorTree.toXmlString());*/

	return navigatorTree;
}

void NavigatorTreeBuilder::stripUnsafeCode (String& code)
{
	//strip text strings ("")
	int start = 0, end = 0, aux = 0;
	while (start != -1)
	{
		if (start != 0)
			start+=2;
		start = code.indexOf(start, "\"");
		aux = code.indexOf(start + 1, "\\\"");
		end = code.indexOf(start + 1, "\"");
		while (aux != -1 && end - aux == 1)
		{
			aux = code.indexOf(end + 1, "\\\"");
			end = code.indexOf(end + 1, "\"");
		}
		if (start != -1 && end > start)
			code = code.replaceSection(start + 1, end - start - 1, "");
	}
	//strip multiline comments
	start = 0;
	end = 0;
	while (start != -1)
	{
		start = code.indexOf(start, "/*");
		end = code.indexOf(start + 1, "*/");
		if (start != -1 && end > start)
		{
			String retainedCode = code.substring (start, end + 2).retainCharacters("\n");
			code = code.replaceSection(start, end - start + 2, retainedCode);
		}
	}
	//strip line comments
	start = 0;
	end = 0;
	while (start != -1)
	{
		if (start != 0)
			++start;
		start = code.indexOf(start, "//");
		end = code.indexOf(start + 1, "\n");
		if (start != -1 && end > start)
			code = code.replaceSection(start, end - start, "");
	}
	//strip preprocessor definitions, empty lines and whitespaces at the start and the end of each line
	StringArray lines = StringArray::fromLines(code);
	//lines.removeEmptyStrings();
	lines.trim();
	for (int i = 0; i < lines.size(); ++i)
	{
		if (lines[i].startsWith("#"))
			lines.getReference(i) = "";	//lines.remove(i);
	}
	code = lines.joinIntoString("\n");
}

bool NavigatorTreeBuilder::isValidSource (String& code)
{
	String temp("{"+code+"}");
	if (getPosOfMatchingBracket(temp, 0, '{', '}') == temp.length() - 1)
		return true;

	return false;
}

int NavigatorTreeBuilder::getLineNumber(String& code, int startPosition, int currentPosition)
{
	jassert (startPosition <= currentPosition);
	int pos = startPosition;
	int len = code.length();
	int numLines = 0;
	while (pos <= currentPosition && pos < len)
	{
		if (code[pos] == '\n')
			++numLines;

		++pos;
	}

	return numLines;
}

int NavigatorTreeBuilder::getPosOfMatchingBracket(const String& code, const int startPosition, juce_wchar openBracket, juce_wchar closeBracket)
{
	int count = 0;	//not closed open brackets count
	int pos = startPosition + 1;
	int len = code.length();
	juce_wchar c;

	while (pos < len)
	{
		c = code[pos];
		if (c == openBracket)
			++count;
		else if (c == closeBracket)
		{
			if (count == 0)
				return pos;	//found at pos
			else
				--count;
		}
		++pos;
	}

	return -1;	//not found!
}

ValueTree NavigatorTreeBuilder::getValueTreeFor(String& code, bool isInsideClass, bool isClassDefinition, int lineNumber)
{
	String memberName, memberClass;
	String memberType = (isClassDefinition) ? "class" : "method";
	ValueTree tree(memberType);

	if (isClassDefinition)
	{
		code = code.fromFirstOccurrenceOf("class ", false, true);
		memberName = code.trimStart();
		memberName = memberName.upToFirstOccurrenceOf(" ", false, false);
	}
	else
	{
		//remove initial line breaks
		while (!CharacterFunctions::isLetter (code[0]))	//code[0] == '\n')
			code = code.substring(1);

		memberName = code.upToFirstOccurrenceOf("(", false, false);
		memberName = memberName.trimEnd();
		String t = memberName.fromLastOccurrenceOf(" ", false, false);
		if (t.length() == memberName.length())
			t = memberName.fromLastOccurrenceOf("\n", false, false);
		memberName = t;
		if (!isInsideClass)
		{
			if (memberName.contains("::"))
			{
				memberClass = memberName.upToFirstOccurrenceOf("::", false, false);
				memberName = memberName.fromFirstOccurrenceOf("::", false, false);
			}
		}
	}

	memberName = memberName.trim();

	tree.setProperty("name", memberName, 0);
	tree.setProperty("class", memberClass, 0);
	tree.setProperty("line", lineNumber, 0);
	DBG("getValueTreeFor "+memberName+" line: "+String(lineNumber));
	//tree.setProperty("raw", code, 0);
	tree.setProperty("isInsideClass", isInsideClass, 0);
	tree.setProperty("isClassDefinition", isClassDefinition, 0);
	return tree;
}

void NavigatorTreeBuilder::updateNavigatorTree (ValueTree& parentTree, String& code, int lineNumber, bool isInsideClass)
{
	//DBG("\t\tvoid SourceCodeEditor::updateNavigatorTree (ValueTree& parentTree, String& code)");
	//DBG("%"+code.substring (0, 10)+"%...%"+code.getLastCharacters(10)+"% parentTreeName: "+parentTree.getType().toString());
	int p = 0, k = 0, kClose = 0;	//p = indexOf("\n"), k = indexOf("{"), kClose = indexOfMatching("}")
	String sub;						//substring from p="\n" to k="{"
	String block;					//substring from "{" to "}"
	int aux;

	while (k != -1 && !thread.threadShouldExit())		//for each code block start "{"
	{
		if (k != 0)			//if we already got matching close block "}"
		{
			k = kClose;			//start looking for the next block "{"
			p = code.indexOf(kClose, "\n");
		}

		k = code.indexOf (k, "{");
		kClose = getPosOfMatchingBracket (code, k, '{', '}');
		//DBG("'{' = "+String (k)+" '}' = "+String (kClose));
		int lineBreaks = 0;
		while (k != -1)		//for each newline "\n" up to code block start "{"
		{
			if (p != -1 && p < k)
			{
				sub = code.substring (p, k);
				if (!sub.containsChar(';'))		//does not contain ';'
				{
					aux = sub.indexOf ("class");
					if (aux != -1)					//check if its a class declaration
					{
						if (aux == 0 || !CharacterFunctions::isLetterOrDigit (sub[aux - 1]))	//check the char before 'class' substring
							if (CharacterFunctions::isWhitespace (sub[aux + 5]))				//check the char after 'class' if its a white space
							{
								//CLASS DECLARATION BLOCK FOUND!
								//DBG("CLASS DECLARATION BLOCK FOUND: #"+sub+"#");
								int lineNumberMod = lineNumber + getLineNumber(code, 0, k) + lineBreaks;
								block = code.substring (k + 1, kClose - 1);
								ValueTree node = getValueTreeFor(sub, isInsideClass, true, lineNumberMod);
								updateNavigatorTree(node, block, lineNumberMod, true);
								parentTree.addChild(node, -1, 0);
								break;
							}
					}
					else
					{								//check if its a method
						if (sub.containsChar ('(') && sub.containsChar (')'))
						{
							//METHOD DECLARATION BLOCK FOUND!
							//DBG("METHOD DECLARATION BLOCK FOUND: #"+sub+"#");
							int lineNumberMod = lineNumber + getLineNumber(code, 0, k) + lineBreaks;
							parentTree.addChild(getValueTreeFor(sub, isInsideClass, false, lineNumberMod), -1, 0);
							break;
						}
						
					}
				}
			}
			else
			{
				//This block is not a class or method, skip
				break;
			}
			p = code.indexOf(p + 1, "\n");	//next newline
			lineBreaks = 1;
		}
	}
}